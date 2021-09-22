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
#include "oscilloscopebuffer.h"

#include <QPainter>
#include <QTimer>
#include <algorithm>
GuiOscilloscopeDisplay::GuiOscilloscopeDisplay(QWidget *parent) : QWidget(parent)
{
    mSampleBuffer = new OscilloscopeBuffer(300);
    mIntBuffer = new int[mSampleBuffer->size()];

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
    delete mSampleBuffer;
    delete mIntBuffer;
}

void GuiOscilloscopeDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int width = std::min(size().width(), (int)mSampleBuffer->size());

    painter.setPen(Qt::white);
    painter.fillRect(QRectF(QPointF(), size()), Qt::black);

    mSampleBuffer->copyTo(mIntBuffer, Value(100.0f), Value(size().height()*0.5f));

    for (int x = 0; x < width; x ++)
        painter.drawPoint(x, mIntBuffer[x]);
}
