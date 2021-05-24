#include "audiofifobuffer.h"
#include <algorithm>
#include <QtEndian>

AudioFifoBuffer::AudioFifoBuffer(QAudioFormat::Endian endianness, QObject *parent):
   QIODevice(parent), CoreSampleBuffer(), mEndianness(endianness), mReadPos(0), mWritePos(0)
{
    mBuffer = new char[mBufferSize];
}

AudioFifoBuffer::~AudioFifoBuffer()
{
    delete []mBuffer;
}

qint64 AudioFifoBuffer::writeDataNoCheck(const char *data, qint64 size)
{
    if (size <= 0)
        return 0;

    std::copy(data, data + size, mBuffer + mWritePos);
    mWritePos += size;
    if (mWritePos == mBufferSize)
        mWritePos = 0;
    return size;
}

qint64 AudioFifoBuffer::writeData(const char *data, qint64 maxSize)
{
    qint64 written = 0;
    qint64 chunksize;

    if (maxSize <= 0)
        return written;

    if (mWritePos > mReadPos) {
        chunksize = std::min(maxSize, mBufferSize - mWritePos);
        written += writeDataNoCheck(data + written, chunksize);
        maxSize -= chunksize;
    }

    chunksize = std::min(maxSize, mReadPos - mWritePos);
    written += writeDataNoCheck(data + written, chunksize);
    return written;
}

qint64 AudioFifoBuffer::readDataNoCheck(char *data, qint64 size)
{
    if (size <= 0)
        return 0;

    std::copy(mBuffer + mReadPos, mBuffer + mReadPos + size, data);
    mReadPos += size;
    if (mReadPos == mBufferSize)
        mReadPos = 0;

    return size;
}

qint64 AudioFifoBuffer::readData(char *data, qint64 maxSize)
{
    qint64 read = 0;
    qint64 chunksize;

    if (maxSize <= 0)
        return read;

    if (mReadPos > mWritePos) {
        chunksize = std::min(maxSize, mReadPos - mWritePos);
        read += readDataNoCheck(data + read, chunksize);
        maxSize -= chunksize;
    }

    chunksize = std::min(maxSize, mWritePos - mReadPos);
    read += readDataNoCheck(data + read, chunksize);
    return read;
}


void AudioFifoBuffer::writeSample(CoreValue sample)
{
    // Clamp value
    qint16 intSample = (qint16)(((sample > 1.0f)?1.0:(sample < -1.0)?-1.0:sample) * 32767);

    // Endian management
    switch(mEndianness) {
    case QAudioFormat::Endian::BigEndian:
        intSample = qToBigEndian(intSample);
        break;
    case QAudioFormat::Endian::LittleEndian:
        intSample = qToLittleEndian(intSample);
        break;
    }

    // Ignore buffer overflow
    writeData((char *)&intSample, 2);
}

CoreValue AudioFifoBuffer::readSample()
{
    qint16 intSample = 0;

    // Ignore buffer underflow (returs 0 value)
    readData((char *)&intSample, 2);

    // Endian management
    switch(mEndianness) {
    case QAudioFormat::Endian::BigEndian:
        intSample = qFromBigEndian(intSample);
        break;
    case QAudioFormat::Endian::LittleEndian:
        intSample = qFromLittleEndian(intSample);
        break;
    }

    return CoreValue(intSample) / 32767;
}


