#include "guimainwindow.h"
#include "../core/coreschema.h"
#include "../draw/drawnmodule.h"
#include "../draw/drawnschema.h"
#include "../draw/drawninput.h"
#include "../draw/drawnoutput.h"
#include "../draw/drawnwire.h"
#include "ui_guimainwindow.h"
#include "guischemascene.h"

GuiMainWindow::GuiMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GuiMainWindow), mCoreSchema(nullptr)
{
    ui->setupUi(this);
    GuiSchemaScene* scene = new GuiSchemaScene();
    scene->setProbeWidget(ui->probeLabel);

    ui->graphicsView->setScene(scene);

    mCoreSchema = new CoreSchema();
    DrawnSchema *schema = new DrawnSchema(mCoreSchema);
    DrawnModule *add1 = schema->newModule("add1", "add");
    DrawnModule *add2 = schema->newModule("add2", "add");
    DrawnModule *mult1 = schema->newModule("mult1", "multiply");
    DrawnModule *const1 = schema->newModule("const1", "constant");
    add1->moveBy(-3,0);
    mult1->moveBy(3,0);
    const1->moveBy(0,3);

    DrawnModule *in1 = schema->newModule("in1", "input");
    DrawnModule *out1 = schema->newModule("out1", "output");


    scene->setSchema(schema);


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

