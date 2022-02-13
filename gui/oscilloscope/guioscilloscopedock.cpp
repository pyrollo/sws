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

GuiOscilloscopeDock::GuiOscilloscopeDock(GuiSchemaView *view, int sampleRate)
    : QDockWidget(view->parentWidget()), ui(new Ui::GuiOscilloscopeDock), mView(view), mSampleRate(sampleRate)
{
    ui->setupUi(this);

    ui->timeSpinBox->addValue(QString("50ms"), .05f);
    ui->timeSpinBox->addValue(QString("100ms"), .1f);
    ui->timeSpinBox->addValue(QString("200ms"), .2f);
    ui->timeSpinBox->addValue(QString("500ms"), .5f);
    ui->timeSpinBox->addValue(QString("1s"), 1.0f);
    ui->timeSpinBox->addValue(QString("2s"), 2.0f);
    ui->timeSpinBox->addValue(QString("5s"), 5.0f);
    ui->timeSpinBox->addValue(QString("10s"), 10.0f);

    connect(ui->addProbeButton, &QAbstractButton::pressed, this, &GuiOscilloscopeDock::handleAddProbe);
    connect(ui->timeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &GuiOscilloscopeDock::handleTimeValueChanged);
    handleAddProbe();
    handleTimeValueChanged(0);
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

void GuiOscilloscopeDock::handleTimeValueChanged(int)
{
    float period = ui->timeSpinBox->getSelectedValue();
    if (period > .0f)
        ui->oscilloscopeDisplay->setSampleRatio(0.001f * period * float(mSampleRate));
}
