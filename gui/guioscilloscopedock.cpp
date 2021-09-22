/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "guioscilloscopedock.h"
#include "ui_guioscilloscopedock.h"
#include "guimainwindow.h"
#include "guischemaview.h"
#include "draw/drawnschema.h"
#include "draw/drawnschemainteraction.h"
#include "draw/drawnplug.h"
#include <QGraphicsSceneMouseEvent>

class ProbeShemaInteraction : public DrawnSchemaInteraction {
public:

    ProbeShemaInteraction(DrawnSchema *schema, GuiOscilloscopeDock *dock):
        DrawnSchemaInteraction(schema), mDock(dock)
    {}

    ~ProbeShemaInteraction()
    {
    }

    void init() override
    {
        mSchema->highlightProbeable();
    }

    void terminate() override
    {
        mSchema->unHighlight();
        //mDock->enableProbeButton();
        delete this;
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) override
    {
        DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);
        if (!plug)
            return;

        //TODO SET PROBE TO PLUG

        mDock->turnOffProbeButton(); // This will end interaction with schema
        e->accept();
    }

protected:
    GuiOscilloscopeDock *mDock;
};

GuiOscilloscopeDock::GuiOscilloscopeDock(GuiSchemaView *view)
    : QDockWidget(view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view), mProbeInteraction(nullptr)
{
    ui->setupUi(this);

//    connect(parent, &GuiMainWindow::schemaChanged, this, &GuiOscilloscopeDock::handleSchemaChange);
    connect(ui->probeButton, &QAbstractButton::toggled, this, &GuiOscilloscopeDock::handleProbe);
}

GuiOscilloscopeDock::GuiOscilloscopeDock(const QString &title, GuiSchemaView *view)
    : QDockWidget(title, view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view), mProbeInteraction(nullptr)
{
    ui->setupUi(this);
}

GuiOscilloscopeDock::~GuiOscilloscopeDock()
{
    if (mProbeInteraction)
        // TODO: Sure there is a schema ?
        mView->schema()->endInteraction();

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
    printf("Probe set [to be implemented]!\n"); fflush(stdout);
}

void GuiOscilloscopeDock::turnOffProbeButton()
{
    ui->probeButton->setChecked(false);
}

void GuiOscilloscopeDock::handleSchemaChange() {
    // TODO: Cancel current interaction ?
}

void GuiOscilloscopeDock::handleProbe(bool checked) {
    // Three cases: no schema, schema probing, schema not probing...

    if (mView->schema()) {
        if (checked) {
            mProbeInteraction = new ProbeShemaInteraction(mView->schema(), this);
            mView->schema()->startInteraction(mProbeInteraction);
        } else {
            if (mProbeInteraction) {
                mView->schema()->endInteraction();
                mProbeInteraction = nullptr;
            }
        }
    }
}
