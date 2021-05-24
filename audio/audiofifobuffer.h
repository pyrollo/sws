#ifndef AUDIOFIFOBUFFER_H
#define AUDIOFIFOBUFFER_H
#include <QIODevice>
#include <QAudioFormat>
#include "core/coresamplebuffer.h"

// TODO: Get rid of limitations:
// - 16 bits only
// - Fixed size (8192 bytes)

class AudioFifoBuffer : public QIODevice, CoreSampleBuffer
{
    Q_OBJECT
    Q_DISABLE_COPY(AudioFifoBuffer)
public:
    AudioFifoBuffer(QAudioFormat::Endian endianness, QObject *parent = 0);
    ~AudioFifoBuffer();

    void writeSample(CoreValue sample);
    CoreValue readSample();

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
