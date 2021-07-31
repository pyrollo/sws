#include "coremoduleoutput.h"
#include "core/coreexceptions.h"
#include "core/coreinput.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema), mSchemaOutput(nullptr), mWriteBuffer(nullptr)
{
    mInputValue = newInput("value", 0.0f);
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

Value CoreModuleOutput::value()
{
    return mInputValue->value();
}


void CoreModuleOutput::writeToBuffer(CoreSampleBuffer *buffer)
{
    mWriteBuffer = buffer;
    if (mWriteBuffer)
        mWriteBuffer->setWriter(this);
}
