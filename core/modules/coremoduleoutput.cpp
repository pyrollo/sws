#include "coremoduleoutput.h"
#include "../coreinput.h"

CoreModuleOutput::CoreModuleOutput(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputValue = newInput("value", 0);
}

void CoreModuleOutput::step() {
    // TODO:Use exported outputs from "machine" class
    // ... = mInputValue->value();
}
