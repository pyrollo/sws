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

#include "guioscilloscopeprobe.h"

#include "draw/drawnschema.h"
#include "draw/drawnplug.h"

GuiOscilloscopeProbe::GuiOscilloscopeProbe():
    mProbedPlug(nullptr), mDisplayBuffer(nullptr), mLast(0), mPeriod(0.0f), mSampleRatio(1.0f), mCurrentSample({0, 0})
{
    mSampleBuffer = new SampleBuffer();
    mScale = 100.0f;
}

GuiOscilloscopeProbe::~GuiOscilloscopeProbe()
{
    probePlug(nullptr);
    delete mSampleBuffer;
}

void GuiOscilloscopeProbe::probePlug(DrawnPlug *plug)
{
    if (mProbedPlug)
        mProbedPlug->schema()->core()->disconnectReadingBuffer(mSampleBuffer);

    mProbedPlug = plug;

    if (mProbedPlug)
        mProbedPlug->schema()->core()->connectReadingBuffer(mSampleBuffer, mProbedPlug->core());
}

void addPixel(QImage *image, int x, int y, QColor &color)
{
    QRgb *line = (QRgb*)image->scanLine(y);
    QRgb pixel = line[x];
    // Here is the color composition rule (basic 'lighten only' thing for now)
    line[x] = qRgb(
        std::max(qRed(pixel), color.red()),
        std::max(qGreen(pixel), color.green()),
        std::max(qBlue(pixel), color.blue())
    );
}

void GuiOscilloscopeProbe::fetchSamples()
{
    // Convert and merge new core samples to display samples
    while (!mSampleBuffer->underflow()) {

        mLast = mSampleBuffer->pop().toInt(mScale, mOffset);

        if (mCurrentSample.min > mLast)
            mCurrentSample.min = mLast;
        if (mCurrentSample.max < mLast)
            mCurrentSample.max = mLast;

        mPeriod += 1.0f;
        if (mPeriod > mSampleRatio) {
            mDisplayBuffer->push(mCurrentSample);
            mPeriod -= mSampleRatio;
            mCurrentSample.min = mLast;
            mCurrentSample.max = mLast;
        }
    }
}

void GuiOscilloscopeProbe::resizeBuffer(size_t newsize)
{
    // TODO: Should not be resized
    // --> Should be adapted to sample rate and refresh rate.
    // Sample buffer should contain sample produced between two displays.
    // If display is 50hz, take 25Hz in account. If sample rate is ~50KHz, then
    // 2000 max samples is enough for all cases.
    mSampleBuffer->resize(newsize);

    // TODO: Should use a resizeable buffer capable of rewind
    size_t oldsize = (mDisplayBuffer)?mDisplayBuffer->size():0;

    if (oldsize == newsize)
        return;

    DisplayBuffer* oldbuffer = mDisplayBuffer;
    mDisplayBuffer = new DisplayBuffer(newsize);

    // Fill unset part of buffer with zeros
    DisplaySample zero = {0, 0};

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

void GuiOscilloscopeProbe::drawTo(QImage *image)
{
    if (!mEnabled)
        return;

    resizeBuffer(image->width());
    fetchSamples();

    QColor color;
    int yoffset = image->size().height() / 2;
    int ylimit = image->size().height() - 1;
    int ymin, ymax;

    mDisplayBuffer->rewind();

    for (int x = 0; x < image->width(); x ++)
    {
        auto sample = mDisplayBuffer->pop();
        ymin = (sample.min + yoffset > 0)?sample.min + yoffset:0;
        ymax = (sample.max + yoffset < ylimit)?sample.max + yoffset:ylimit;
        if (ymin <= ylimit && ymax >= 0) {
            color = mColor.darker(100 + (ymax - ymin) * 5);
            for (int y = ymin; y <= ymax; y++)
                addPixel(image, x, y, color);
        }
    }
}
