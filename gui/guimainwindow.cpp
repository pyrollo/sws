#include "guimainwindow.h"
#include "core/coreschema.h"
#include "draw/drawnmodule.h"
#include "draw/drawnschema.h"
#include "draw/drawninput.h"
#include "draw/drawnoutput.h"
#include "draw/drawnwire.h"
#include "draw/drawnmodulefactory.h"
#include "ui_guimainwindow.h"
#include "guischemascene.h"
#include "guistyle.h"

GuiMainWindow::GuiMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GuiMainWindow), mCoreSchema(nullptr)
{
    ui->setupUi(this);

    // Workscheet view
    mCoreSchema = new CoreSchema();
    DrawnSchema *schema = new DrawnSchema(mCoreSchema);
    GuiSchemaScene* scene = new GuiSchemaScene();
    scene->setSchema(schema);
    scene->setProbeWidget(ui->probeLabel);
    ui->schemaView->setScene(scene);

    // Some modules
    schema->newModule("add");


    // Modules library view
    QGraphicsScene* moduleLibraryScene = new QGraphicsScene();
    moduleLibraryScene->setBackgroundBrush(GuiStyle::bBackground());

    DrawnModuleFactory *factory = schema->getModuleFactory();
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

    connect(ui->pushButtonStep, &QPushButton::released, this, &GuiMainWindow::handleButtonStep);
}

GuiMainWindow::~GuiMainWindow()
{
    delete ui;
}

void GuiMainWindow::handleButtonStep()
{
    mCoreSchema->step();
}

