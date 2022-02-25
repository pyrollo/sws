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
    QWidget(parent), mRefreshRate(25.0f),
    mBackgroundColor(16, 48, 16), mGridColor(32, 96, 32), mDivisionSize(100)
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

void GuiOscilloscopeDisplay::drawBackground(QImage &image)
{
    // Draw background
    image.fill(mBackgroundColor);

    // Draw grid
    QPainter painter(&image);

    QPen dash(mGridColor);
    QPen solid(mGridColor);

    dash.setStyle(Qt::DashLine);
    solid.setStyle(Qt::SolidLine);

    int w = image.width();
    int h = image.height();
    int w2 = w/2;
    int h2 = h/2;

    painter.setPen(solid);
    for (int y = 0; y < h2; y += mDivisionSize)
    {
        painter.drawLine(0, h2 + y, w - 1, h2 + y);
        painter.drawLine(0, h2 - y, w - 1, h2 - y);
        painter.setPen(dash);
    }

    painter.setPen(solid);
    for (int x = 0; x < w2; x += mDivisionSize)
    {
        painter.drawLine(w2 + x, 0, w2 + x, h - 1);
        painter.drawLine(w2 - x, 0, w2 - x, h - 1);
        painter.setPen(dash);
    }
}

void GuiOscilloscopeDisplay::paintEvent(QPaintEvent *) {
    QImage image(size(), QImage::Format_RGB32);
    drawBackground(image);

    for (auto probe: mProbes)
        probe->drawTo(&image);

    QPainter painter(this);
    painter.drawImage(0.0f, 0.0f, image);
}

void  GuiOscilloscopeDisplay::setSampleRatio(float ratio)
{
    for (auto probe: mProbes)
        probe->setSampleRatio(ratio);
}

