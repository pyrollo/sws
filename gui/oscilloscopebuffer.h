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

#ifndef OSCILLOSCOPEBUFFER_H
#define OSCILLOSCOPEBUFFER_H
#include <cstddef>
#include "core/coresamplebuffer.h"
#include "value/value.h"

class OscilloscopeBuffer : public CoreSampleBuffer
{
public:
    OscilloscopeBuffer(size_t size);
    ~OscilloscopeBuffer();
    void fill(Value value);

    void writeSample(Value sample) override;
    Value readSample() override { return Value(.0f); } // Nothing to read here

    void copyTo(int *buffer, Value scale, Value offset);
    inline size_t size() { return mSize; }

private:
    size_t mSize;
    Value *mBuffer;
    size_t mPos;
};

#endif // OSCILLOSCOPEBUFFER_H
