#include "coremoduleoutput.h"
#include "core/coreexceptions.h"
#include "core/coreschema.h"
#include "core/coresamplebuffer.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema), mSchemaOutput(this)
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
    mSchemaOutput.setValue(mInputValue->value());
}

void CoreModuleOutput::setName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->setOutputName(this, name);
}
