#ifndef CORESAMPLEBUFFER_H
#define CORESAMPLEBUFFER_H
#include "value/value.h"

// TODO: Add a "sample producer" class?
class CoreModuleOutput;
class CoreModuleInput;

class CoreSampleBuffer
{
public:
    CoreSampleBuffer();
    virtual ~CoreSampleBuffer() {}

    virtual void writeSample(Value sample) = 0;
    virtual Value readSample() = 0;
};

#endif // CORESAMPLEBUFFER_H
