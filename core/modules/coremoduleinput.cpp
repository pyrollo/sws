#include "coremoduleinput.h"
#include "core/coreexceptions.h"
#include "core/coreoutput.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema), mSchemaInput(nullptr), mReadBuffer(nullptr)
{
    mOutputValue = newOutput("value");
}

CoreModuleInput::~CoreModuleInput()
{
    if (mSchema)
        setName("");
}

void CoreModuleInput::step()
{
    if (mSchemaInput)
        mOutputValue->setValue(*mSchemaInput);
}

void CoreModuleInput::setName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->setInputName(this, name);
}

Value CoreModuleInput::value()
{
    return mOutputValue->value();
}

void CoreModuleInput::readFromBuffer(CoreSampleBuffer *buffer)
{
    mReadBuffer = buffer;
    if (mReadBuffer)
        mReadBuffer->setReader(this);
}
