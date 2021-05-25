#include "guimainwindow.h"
#include "core/coreschema.h"
#include "core/coremachine.h"
#include "draw/drawnmodule.h"
#include "draw/drawnschema.h"
#include "draw/drawninput.h"
#include "draw/drawnoutput.h"
#include "draw/drawnwire.h"
#include "draw/drawnmodulefactory.h"
#include "file/fileserializer.h"
#include "ui_guimainwindow.h"
#include "guischemascene.h"
#include "guistyle.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "audio/audiofifobuffer.h"
#include <QAudioFormat>
#include <QAudioOutput>
#include <QAudioDeviceInfo>
#include <stdexcept>

GuiMainWindow::GuiMainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::GuiMainWindow),
      mSchema(nullptr), mCoreSchema(nullptr), mCoreMachine(nullptr),
      mAudioOutputBuffer(nullptr), mAudioOutput(nullptr),
      mCurrentFilePath("")
{
    ui->setupUi(this);

    // Workscheet view
    mCoreSchema = new CoreSchema();
    mSchema = new DrawnSchema(mCoreSchema);
    GuiSchemaScene* scene = new GuiSchemaScene();
    scene->setSchema(mSchema);
    scene->setProbeWidget(ui->probeLabel);
    ui->schemaView->setScene(scene);

    // Modules library view
    QGraphicsScene* moduleLibraryScene = new QGraphicsScene();
    moduleLibraryScene->setBackgroundBrush(GuiStyle::bBackground());

    DrawnModuleFactory *factory = mSchema->getModuleFactory();
    float y = 1.0f;
    for (auto moduletype: factory->listModules()) {
        DrawnModule *module = factory->newModule(moduletype);
        QRectF rect = module->boundingRect();
        module->moveBy(-0.5 * rect.width(), y);
        y += rect.height() + 1.0f;
        moduleLibraryScene->addItem(module);
    }

    QRectF sceneRect = moduleLibraryScene->sceneRect();
    sceneRect = sceneRect.marginsAdded(QMarginsF(.5f, .5f, .5f, .5f));
    moduleLibraryScene->setSceneRect(sceneRect);
    float scale = ui->modulesLibraryView->rect().width() / sceneRect.width();

    ui->modulesLibraryView->setScene(moduleLibraryScene);
    ui->modulesLibraryView->setTransform(QTransform().scale(scale, scale));
    ui->schemaView->scale(scale, scale);

    // Prepare audio device & buffer
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format = device.preferredFormat();
    format.setChannelCount(1);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    mAudioOutput = new QAudioOutput(device, format);
    mAudioOutputBuffer = new AudioFifoBuffer(format.byteOrder());
    mAudioOutputBuffer->open(QIODevice::ReadOnly);
    mAudioOutput->start(mAudioOutputBuffer);
    mAudioOutputBuffer->fill(0, mAudioOutput->periodSize()/2);
    ui->speakerOutputComboBox->setSchema(mSchema);
    ui->speakerOutputComboBox->setAudioBuffer(mAudioOutputBuffer);

    // Prepare machine
    mCoreMachine = new CoreMachine(mCoreSchema, 1.0f/float(format.sampleRate()));
    mCoreMachine->start();

    // Other UI stuff
    ui->pushButtonStartStop->setText("Stop");
    connect(ui->pushButtonStartStop, &QPushButton::released, this, &GuiMainWindow::handleButtonStartStop);

    // Menu actions
    connect(ui->actionNew,    &QAction::triggered, this, &GuiMainWindow::handleFileNew);
    connect(ui->actionOpen,   &QAction::triggered, this, &GuiMainWindow::handleFileOpen);
    connect(ui->actionSave,   &QAction::triggered, this, &GuiMainWindow::handleFileSave);
    connect(ui->actionSaveAs, &QAction::triggered, this, &GuiMainWindow::handleFileSaveAs);
    connect(ui->actionQuit,   &QAction::triggered, this, &GuiMainWindow::handleFileQuit);
}

GuiMainWindow::~GuiMainWindow()
{
    mAudioOutput->stop();
    mCoreMachine->stop();
    delete mCoreSchema;
    delete mCoreMachine;
    delete mAudioOutputBuffer;
    delete mAudioOutput;
    delete ui;
}

void GuiMainWindow::handleButtonStartStop()
{
    if (mCoreMachine->isRunning()) {
        mCoreMachine->stop();
        ui->pushButtonStartStop->setText("Start");
    } else {
        mCoreMachine->start();
        ui->pushButtonStartStop->setText("Stop");
    }
}

void GuiMainWindow::handleFileNew()
{
}

void GuiMainWindow::handleFileOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), QString(), tr("SWS files (*.sws)"));

    if (fileName == "")
        return;
}

void GuiMainWindow::handleFileSave()
{
    if (mCurrentFilePath == "") {
        handleFileSaveAs();
        return;
    }

    QFile file(mCurrentFilePath);
    FileSerializer fs(mSchema);

    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream stream(&file);
        stream << fs.serialize();
        file.close();
    }
}

void GuiMainWindow::handleFileSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save file"), QString(), tr("SWS files (*.sws)"));

    if (fileName != "") {
        mCurrentFilePath = fileName;
        handleFileSave();
     }
}

void GuiMainWindow::handleFileQuit()
{
    QApplication::quit();
}
