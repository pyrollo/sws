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

#include "guioscilloscopeprobeframe.h"
#include "guimainwindow.h"
#include "guischemaview.h"
//#include "draw/drawnschema.h"
#include <QGraphicsSceneMouseEvent>

GuiOscilloscopeDock::GuiOscilloscopeDock(GuiSchemaView *view)
    : QDockWidget(view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view)
{
    ui->setupUi(this);

    connect(ui->addProbeButton, &QAbstractButton::pressed, this, &GuiOscilloscopeDock::handleAddProbe);
    handleAddProbe();
}

GuiOscilloscopeDock::GuiOscilloscopeDock(const QString &title, GuiSchemaView *view)
    : QDockWidget(title, view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view)
{
    ui->setupUi(this);

    connect(ui->addProbeButton, &QAbstractButton::pressed, this, &GuiOscilloscopeDock::handleAddProbe);
    handleAddProbe();
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

void GuiOscilloscopeDock::handleSchemaChange() {
    // TODO: Cancel current interaction ?
}

void GuiOscilloscopeDock::handleAddProbe() {
    printf("ADD PROBE\n"); fflush(stdout);
    GuiOscilloscopeProbeFrame *probe = new GuiOscilloscopeProbeFrame(ui->oscilloscopeDisplay, mView);
    ui->verticalLayout->addWidget(probe);
    probe->show();
}
