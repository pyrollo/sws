#ifndef CORESAMPLEBUFFER_H
#define CORESAMPLEBUFFER_H
#include "core.h"

// TODO: Add a "sample producer" class?
class CoreModuleOutput;
class CoreModuleInput;

class CoreSampleBuffer
{
public:
    CoreSampleBuffer();
    virtual ~CoreSampleBuffer() {}

    virtual void writeSample(CoreValue sample) = 0;
    virtual CoreValue readSample() = 0;

    void setWriter(CoreModuleOutput *output);
    void setReader(CoreModuleInput *input);

protected:
    CoreModuleOutput *mCurrentWriter;
    CoreModuleInput  *mCurrentReader;
};

#endif // CORESAMPLEBUFFER_H
