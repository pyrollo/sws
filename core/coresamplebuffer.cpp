#include "coresamplebuffer.h"
#include "modules/coremoduleoutput.h"
#include "modules/coremoduleinput.h"

CoreSampleBuffer::CoreSampleBuffer():
    mCurrentWriter(nullptr), mCurrentReader(nullptr)
{
}

void CoreSampleBuffer::setWriter(CoreModuleOutput *output)
{
    if (mCurrentWriter == output)
        return;

    if (mCurrentWriter)
        mCurrentWriter->writeToBuffer(nullptr);

    mCurrentWriter = output;
}

void CoreSampleBuffer::setReader(CoreModuleInput *input)
{
    if (mCurrentReader == input)
        return;

    if (mCurrentReader)
        mCurrentReader->readFromBuffer(nullptr);

    mCurrentReader = input;
}
