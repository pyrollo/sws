#include "guioscilloscopedock.h"
#include "ui_guioscilloscopedock.h"
#include "guimainwindow.h"
#include "guischemaview.h"
#include "draw/drawnschema.h"

GuiOscilloscopeDock::GuiOscilloscopeDock(GuiSchemaView *view)
    : QDockWidget(view->parentWidget()), Prober(), ui(new Ui::GuiOscilloscopeDock), mView(view)
{
    ui->setupUi(this);

//    connect(parent, &GuiMainWindow::schemaChanged, this, &GuiOscilloscopeDock::handleSchemaChange);
    connect(ui->probeButton, &QAbstractButton::toggled, this, &GuiOscilloscopeDock::handleProbe);
}

GuiOscilloscopeDock::GuiOscilloscopeDock(const QString &title, GuiSchemaView *view)
    : QDockWidget(title, view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view)
{
    ui->setupUi(this);
}

GuiOscilloscopeDock::~GuiOscilloscopeDock()
{
    delete ui;
}

void GuiOscilloscopeDock::closeEvent(QCloseEvent *event)
{
    (void)(event);
    // Remove oscilloscope on close
    delete this;
}

void GuiOscilloscopeDock::setProbe(DrawnPlug *plug)
{
    (void)(plug);
    ui->probeButton->setChecked(false);
    printf("Probe set [to be implemented]!\n"); fflush(stdout);
}

void GuiOscilloscopeDock::handleSchemaChange() {
    // MAYDO: Disconnect probing
}

void GuiOscilloscopeDock::handleProbe(bool checked) {
    if (checked)
    { printf("Probe on!\n"); fflush(stdout);}
    else
      {  printf("Probe off!\n"); fflush(stdout);}

    // Three cases: no schema, schema probing, schema not probing...

    if (mView->schema()) {
        if (checked) {
            mView->schema()->setProber(this);
            mView->schema()->highlightProbeable();
        } else {
            mView->schema()->setProber(nullptr);
            mView->schema()->unHighlight();
        }
    }
}
