#include "coremoduleinput.h"
#include "../coreoutput.h"

CoreModuleInput::CoreModuleInput(CoreSchema *schema) :
    CoreModule(schema)
{
    mOutputValue = newOutput("value");
}

void CoreModuleInput::step() {
    // TODO:Use exported input from "machine" class
    // mOutputValue->setValue(...);
}
