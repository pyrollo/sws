#ifndef CORESAMPLEBUFFER_H
#define CORESAMPLEBUFFER_H
#include "core.h"

class CoreSampleBuffer
{
public:
    CoreSampleBuffer() {}
    virtual ~CoreSampleBuffer() {}

    virtual void writeSample(CoreValue sample) = 0;
    virtual CoreValue readSample() = 0;
};

#endif // CORESAMPLEBUFFER_H
