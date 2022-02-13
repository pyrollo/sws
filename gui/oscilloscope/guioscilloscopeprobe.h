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

#ifndef GUIOSCILLOSCOPEPROBE_H
#define GUIOSCILLOSCOPEPROBE_H

#include "value/value.h"
#include "core/coresamplebuffer.h"
#include "utils/resizeablerollingbuffer.h"
#include "utils/rollingbuffer.h"

#include <QColor>

class GuiOscilloscopeProbeSample;
class DrawnPlug;
class QImage;

class GuiOscilloscopeProbe
{
public:
    GuiOscilloscopeProbe();
    ~GuiOscilloscopeProbe();

    void drawTo(QImage *image);
    void probePlug(DrawnPlug *plug);
    void setColor(QColor color) { mColor = color; }
protected:

    struct DisplaySample {
        int min;
        int max;
    };

    // TODO: Should be resizeable and rewindable
    class DisplayBuffer : public RollingBuffer<DisplaySample>
    {
    public:
        DisplayBuffer(size_t size): RollingBuffer<DisplaySample>(size) {}
    };

    // TODO: No actual need to be resizeable
    class SampleBuffer : public ResizeableRollingBuffer<Value>, public CoreSampleBuffer
    {
    public:
        SampleBuffer(): ResizeableRollingBuffer<Value>() {}

        void writeSample(Value sample) override { push(sample); }
        Value readSample() override { return Value(.0f); } // Nothing to read here
    };

    DrawnPlug *mProbedPlug;
    SampleBuffer *mSampleBuffer;

    DisplayBuffer *mDisplayBuffer;

    QColor mColor;
    Value mScale;
    Value mOffset;

    // Draw variables
    int mLast;
    float mPeriod;
    float mSampleRatio;
    DisplaySample mCurrentSample;

    void fetchSamples();
    void resizeBuffer(size_t newsize);
};

#endif // GUIOSCILLOSCOPEPROBE_H
