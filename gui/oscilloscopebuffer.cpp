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

#include "oscilloscopebuffer.h"

OscilloscopeBuffer::OscilloscopeBuffer(size_t size):
    mSize(size), mPos(0)
{
    mBuffer = new Value[mSize];
}

OscilloscopeBuffer::~OscilloscopeBuffer()
{
    delete []mBuffer;
}

void OscilloscopeBuffer::fill(Value value)
{
    for (size_t pos = 0; pos < mSize; pos++)
        mBuffer[pos] = value;
}

void OscilloscopeBuffer::writeSample(Value value)
{
    mBuffer[mPos] = value;
    mPos++;
    if (mPos > mSize)
        mPos = 0;
}

void OscilloscopeBuffer::copyTo(int *buffer, Value scale, Value offset) {
    size_t n = 0;
    size_t pos = mPos;

    while (pos < mSize)
        buffer[n++] = (mBuffer[pos++] * scale + offset).toInt();

    pos = 0;
    while (pos < mPos)
        buffer[n++] = (mBuffer[pos++] * scale + offset).toInt();
}

