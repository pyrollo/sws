#include "coremoduleoutput.h"
#include "../coreexceptions.h"
#include "../coreinput.h"
#include "../coreschema.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema), mSchemaOutput(nullptr)
{
    mInputValue = newInput("value", 0);
}

CoreModuleOutput::~CoreModuleOutput()
{
    unexport();
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
        auto outputs = mSchema->outputs();
        if (outputs.find(name) != outputs.end())
            throw CoreDuplicateNameEx(name);

        unexport();
        mName = name;
        mSchemaOutput = mSchema->newOutput(mName, mInputValue->value());
    }
}

void CoreModuleOutput::unexport()
{
    if (!mSchemaOutput)
        return;

    if (!mSchema)
        throw CoreNoSchemaEx();

    mSchema->deleteOutput(mName);
    mName = "";
    mSchemaOutput = nullptr;
}
