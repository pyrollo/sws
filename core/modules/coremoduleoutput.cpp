#include "coremoduleoutput.h"
#include "../coreexceptions.h"
#include "../coreinput.h"
#include "../coreschema.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema), mSchemaOutput(nullptr)
{
    mInputValue = newInput("value", 0);
}

void CoreModuleOutput::step()
{
    if (mSchemaOutput)
        *mSchemaOutput = mInputValue->value();
}

void CoreModuleOutput::exportName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    if (mName != name) {
        if (mSchemaOutput)
            mSchema->deleteOutput(mName);
        mName = name;
        mSchemaOutput = mSchema->newOutput(mName, mInputValue->value());
    }
}
