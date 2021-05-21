#include "coremoduleinput.h"
#include "../coreexceptions.h"
#include "../coreoutput.h"
#include "../coreschema.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema), mName(""), mSchemaInput(nullptr)
{
    mOutputValue = newOutput("value");
}

void CoreModuleInput::step()
{
    if (mSchemaInput)
        mOutputValue->setValue(*mSchemaInput);
}

void CoreModuleInput::exportName(std::string name)
{
    if (!mSchema)
        throw CoreNoSchemaEx();

    if (mName != name) {
        if (mSchemaInput)
            mSchema->deleteInput(mName);
        mName = name;
        mSchemaInput = mSchema->newInput(mName, mOutputValue->value());
    }
}
