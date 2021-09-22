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

#ifndef AUDIOFIFOBUFFER_H
#define AUDIOFIFOBUFFER_H
#include <QIODevice>
#include <QAudioFormat>
#include "core/coresamplebuffer.h"

// TODO: Get rid of limitations:
// - 16 bits only
// - Fixed size (8192 bytes)

class AudioFifoBuffer : public QIODevice, public CoreSampleBuffer
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioFifoBuffer)
public:
    explicit AudioFifoBuffer(QAudioFormat::Endian endianness, QObject *parent = 0);
    ~AudioFifoBuffer();

    void writeSample(Value sample);
    Value readSample();

    qint64 fill(char value, qint64 size);

protected:
    QAudioFormat::Endian mEndianness;

    qint64 mBufferSize = 8192; // ~ 1/4s at 44100KHz/16bits mono
    char *mBuffer;

    qint64 mReadPos;
    qint64 mWritePos;


    qint64 writeDataNoCheck(const char *data, qint64 size);
    qint64 readDataNoCheck(char *data, qint64 size);

    qint64 readData(char *data, qint64 maxSize);
    qint64 writeData(const char *data, qint64 maxSize);
};

#endif // AUDIOFIFOBUFFER_H
