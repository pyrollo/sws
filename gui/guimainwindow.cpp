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
    , ui(new Ui::GuiMainWindow)
{
    ui->setupUi(this);
    GuiSchemaScene* scene = new GuiSchemaScene();
    scene->setBackgroundBrush(Qt::black);

    ui->graphicsView->setScene(scene);

    CoreSchema *coreSchema = new CoreSchema();
    DrawnSchema *schema = new DrawnSchema(coreSchema);
    DrawnModule *add1 = schema->newModule("add1", "add");
    DrawnModule *add2 = schema->newModule("add2", "add");
    DrawnModule *add3 = schema->newModule("add3", "add");
    DrawnModule *add4 = schema->newModule("add4", "add");
    add1->moveBy(-3,0);
    add3->moveBy(3,0);
    add4->moveBy(0,3);
    DrawnWire *wire1 = new DrawnWire(schema);
    wire1->connectTo(add1->output("result"));
    wire1->connectTo(add2->input("operand1"));

    DrawnWire *wire2 = new DrawnWire(schema);
    wire2->connectTo(add2->output("result"));
    wire2->connectTo(add3->input("operand1"));

    scene->setSchema(schema);
}

GuiMainWindow::~GuiMainWindow()
{
    delete ui;
}

