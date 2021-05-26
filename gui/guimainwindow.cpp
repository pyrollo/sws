#include "guimainwindow.h"
#include "core/coreschema.h"
#include "core/coremachine.h"
#include "draw/drawnmodule.h"
#include "draw/drawnschema.h"
#include "draw/drawninput.h"
#include "draw/drawnoutput.h"
#include "draw/drawnwire.h"
#include "file/fileserializer.h"
#include "ui_guimainwindow.h"
#include "guischemascene.h"
#include "guimodulelibraryview.h"
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
      mSchema(nullptr), mCoreMachine(),
      mAudioOutputBuffer(nullptr), mAudioOutput(nullptr),
      mCurrentFilePath("")
{
    // Workscheet view
    ui->setupUi(this);
    ui->schemaView->setProbeWidget(ui->probeLabel);

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
    mCoreMachine.setStepTime(1.0f/float(format.sampleRate()));
    ui->speakerOutputComboBox->setAudioBuffer(mAudioOutputBuffer);

    // Menu actions
    connect(ui->actionNew,    &QAction::triggered, this, &GuiMainWindow::handleFileNew);
    connect(ui->actionOpen,   &QAction::triggered, this, &GuiMainWindow::handleFileOpen);
    connect(ui->actionSave,   &QAction::triggered, this, &GuiMainWindow::handleFileSave);
    connect(ui->actionSaveAs, &QAction::triggered, this, &GuiMainWindow::handleFileSaveAs);
    connect(ui->actionQuit,   &QAction::triggered, this, &GuiMainWindow::handleFileQuit);

    // Start with a new file
    handleFileNew();
}

GuiMainWindow::~GuiMainWindow()
{
    mAudioOutput->stop();
    mCoreMachine.stop();
    if (mSchema)
        delete mSchema;

    delete mAudioOutputBuffer;
    delete mAudioOutput;
    delete ui;
}

void GuiMainWindow::handleFileNew()
{
    // Stop machine before any operation
    mCoreMachine.stop();

    // Delete old schemas
    if (mSchema) {
        ui->speakerOutputComboBox->setSchema(nullptr); // TODO: ComboBox should be connected to view rather than schema
        ui->schemaView->setSchema(nullptr);
        ui->modulesLibraryView->setFactory(nullptr);
        delete mSchema;
    }

    // New schemas
    mSchema = new DrawnSchema();

    ui->modulesLibraryView->setFactory(mSchema->getModuleFactory());
    ui->speakerOutputComboBox->setSchema(mSchema); // TODO: ComboBox should be connected to view rather than schema
    ui->schemaView->setSchema(mSchema);
    ui->schemaView->setTransform(QTransform());
    ui->schemaView->scale(ui->modulesLibraryView->getScale(), ui->modulesLibraryView->getScale());

    // Restart machine
    mCoreMachine.setSchema(mSchema->core());
    mCoreMachine.start();
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
