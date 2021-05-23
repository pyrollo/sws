#include "coremoduleinput.h"
#include "../coreexceptions.h"
#include "../coreoutput.h"
#include "../coreschema.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema), mName(""), mSchemaInput(nullptr)
{
    mOutputValue = newOutput("value");
}

CoreModuleInput::~CoreModuleInput()
{
    unexport();
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
        auto inputs = mSchema->inputs();
        if (inputs.find(name) != inputs.end())
            throw CoreDuplicateNameEx(name);

        unexport();
        mName = name;
        mSchemaInput = mSchema->newInput(mName, mOutputValue->value());
    }
}

void CoreModuleInput::unexport()
{
    if (!mSchemaInput)
        return;

    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->deleteInput(mName);
    mName = "";
    mSchemaInput = nullptr;
}
