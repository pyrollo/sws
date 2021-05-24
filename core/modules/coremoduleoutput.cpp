#include "coremoduleoutput.h"
#include "../coreexceptions.h"
#include "../coreinput.h"
#include "../coreschema.h"
#include "../coresamplebuffer.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema), mSchemaOutput(nullptr), mWriteBuffer(nullptr)
{
    mInputValue = newInput("value", 0);
}

CoreModuleOutput::~CoreModuleOutput()
{
    if (mSchema)
        setName("");
}

void CoreModuleOutput::step()
{
    if (mWriteBuffer)
        mWriteBuffer->writeSample(mInputValue->value());
}

void CoreModuleOutput::setName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->setOutputName(this, name);
}

CoreValue CoreModuleOutput::value()
{
    return mInputValue->value();
}


void CoreModuleOutput::writeToBuffer(CoreSampleBuffer *buffer)
{
    mWriteBuffer = buffer;
    if (mWriteBuffer)
        mWriteBuffer->setWriter(this);
}
