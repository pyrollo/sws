#include "coremoduleinput.h"
#include "core/coreexceptions.h"
#include "core/coreoutput.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema), mSchemaInput(this, 0.0f)
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
    mOutputValue->setValue(mSchemaInput.value());
}

void CoreModuleInput::setName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->setInputName(this, name);
}

