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
#include "utils/resizeablerollingbuffer.h"
#include "utils/rollingbuffer.h"
#include "draw/drawnplug.h"
#include "draw/drawnschema.h"
#include "core/coreplug.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

#include <QPainter>
#include <QTimer>
#include <QResizeEvent>

#include <algorithm>

class DisplayBuffer : public RollingBuffer<int>
{
public:
    DisplayBuffer(size_t size): RollingBuffer<int>(size) {}
};

class OscilloscopeBuffer : public ResizeableRollingBuffer<Value>, public CoreSampleBuffer
{
public:
    OscilloscopeBuffer(): ResizeableRollingBuffer<Value>() {}

    void writeSample(Value sample) override { push(sample); }
    Value readSample() override { return Value(.0f); } // Nothing to read here
};

GuiOscilloscopeDisplay::GuiOscilloscopeDisplay(QWidget *parent) :
    QWidget(parent), mDisplayBuffer(nullptr), mProbedPlug(nullptr)
{
    mSampleBuffer = new OscilloscopeBuffer();
    mSampleBuffer->resize(width());
    // --> Should be adapted to sample rate and refresh rate.
    // Sample buffer should contain sample produced between two displays.
    // If display is 50hz, take 25Hz in account. If sample rate is ~50KHz, then
    // 2000 max samples is enough for all cases.

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    mTimer->setInterval(50);
    mTimer->setSingleShot(false);
    mTimer->start();
}

GuiOscilloscopeDisplay::~GuiOscilloscopeDisplay()
{
    probePlug(nullptr);
    mTimer->stop();
    delete mTimer;
    delete mSampleBuffer;
    delete mDisplayBuffer;
}

void GuiOscilloscopeDisplay::probePlug(DrawnPlug *plug)
{
    if (mProbedPlug)
        mProbedPlug->schema()->core()->disconnectReadingBuffer(mSampleBuffer);

    mProbedPlug = plug;

    if (mProbedPlug)
        mProbedPlug->schema()->core()->connectReadingBuffer(mSampleBuffer, mProbedPlug->core());
}

void GuiOscilloscopeDisplay::resizeBuffer()
{
    size_t newsize = width();
    size_t oldsize = (mDisplayBuffer)?mDisplayBuffer->size():0;

    if (oldsize == newsize)
        return;

    DisplayBuffer* oldbuffer = mDisplayBuffer;
    mDisplayBuffer = new DisplayBuffer(newsize);

    // Fill unset part of buffer with zeros
    int zero = size().height()*0.5f;
    size_t fill = newsize;
    if (oldbuffer)
    {
        if (oldbuffer->length() < newsize)
            fill = newsize - oldbuffer->length();
        else
            fill = 0;
    }
    while (fill--)
        mDisplayBuffer->push(zero);

    // Copy existing stuff from old buffer to new buffer
    if (!oldbuffer)
        return;

    oldbuffer->rewind();
    while (!oldbuffer->underflow())
        mDisplayBuffer->push(oldbuffer->pop());

    delete oldbuffer;
}

void GuiOscilloscopeDisplay::resizeEvent(QResizeEvent *)
{
    resizeBuffer();
    mSampleBuffer->resize(width());
}

void GuiOscilloscopeDisplay::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    // Copy and convert new samples
    while (!mSampleBuffer->underflow())
        // TODO: compute values only once
        mDisplayBuffer->push(mSampleBuffer->pop().toInt(Value(100.0f), Value(size().height()*0.5f)));

    mDisplayBuffer->rewind();

    painter.setPen(Qt::white);
    painter.fillRect(rect(), Qt::darkGreen);

    for (int x = 0; x < width(); x ++)
//        painter.drawLine(x, mIntBuffer[x].min, x, mIntBuffer[x].max);
        painter.drawPoint(x, mDisplayBuffer->pop());
}
