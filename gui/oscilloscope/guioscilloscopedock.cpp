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
#include "../guimainwindow.h"
#include "../guischemaview.h"
#include <QGraphicsSceneMouseEvent>

const float timePeriods [] = { .01f, .02f, .05f, .1f, .2f, .5f, 1.0f, 2.0f, 5.0f, 10.0f };
const QString timeLabels [] = { "10ms", "20ms", "50ms", "100ms", "200ms", "500ms", "1s", "2s", "5s", "10s" };

GuiOscilloscopeDock::GuiOscilloscopeDock(GuiSchemaView *view, int sampleRate)
    : QDockWidget(view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view), mSampleRate(sampleRate)
{
    ui->setupUi(this);

    connect(ui->addProbeButton, &QAbstractButton::pressed, this, &GuiOscilloscopeDock::handleAddProbe);
    connect(ui->timeDial, QOverload<int>::of(&QDial::valueChanged), this, &GuiOscilloscopeDock::handleTimeValueChanged);

    ui->timeDial->setValue(4);
    handleAddProbe();
}

GuiOscilloscopeDock::~GuiOscilloscopeDock()
{
    delete ui;
}

void GuiOscilloscopeDock::closeEvent(QCloseEvent *)
{
    // Remove oscilloscope on close
    delete this;
}

void GuiOscilloscopeDock::handleSchemaChange()
{
    // TODO: Cancel current interaction ?
}

void GuiOscilloscopeDock::handleAddProbe()
{
    GuiOscilloscopeProbeFrame *probe = new GuiOscilloscopeProbeFrame(ui->oscilloscopeDisplay, mView);
    ui->verticalLayout->addWidget(probe);
    probe->show();
}

void GuiOscilloscopeDock::handleTimeValueChanged(int value)
{
    ui->oscilloscopeDisplay->setSampleRatio(timePeriods[value] * float(mSampleRate) / ui->oscilloscopeDisplay->getDivisionSize());
    ui->timeLabel->setText(QString("Time/div\n").append(timeLabels[value]));
}
