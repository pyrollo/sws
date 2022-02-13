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

#include "guioscilloscopedisplay.h"
#include "guioscilloscopeprobe.h"
#include "draw/drawnplug.h"
#include "draw/drawnschema.h"
#include "core/coreplug.h"
#include "core/coreschema.h"

#include <QPainter>
#include <QTimer>
#include <QResizeEvent>

#include <algorithm>

GuiOscilloscopeDisplay::GuiOscilloscopeDisplay(QWidget *parent) :
    QWidget(parent), mRefreshRate(25.0f)
{
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    mTimer->setInterval(50);
    mTimer->setSingleShot(false);
    mTimer->start();
}

GuiOscilloscopeDisplay::~GuiOscilloscopeDisplay()
{
    mTimer->stop();
    delete mTimer;
}

void GuiOscilloscopeDisplay::resizeEvent(QResizeEvent *e)
{
    emit resized(e);
}

void GuiOscilloscopeDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPoint origin(0.0f, 0.0f);
    QColor background(16, 48, 16);

    QImage image(size(), QImage::Format_RGB32);
    image.fill(background);

    for (auto probe: probes)
        probe->drawTo(&image);

    painter.drawImage(origin, image);
}
