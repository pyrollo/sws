#include "coremoduleconstant.h"
#include "../coreoutput.h"

CoreModuleConstant::CoreModuleConstant(CoreSchema *schema) :
    CoreModule(schema)
{
    mOutputValue = newOutput("value");
}

void CoreModuleConstant::setValue(CoreValue value)
{
    mOutputValue->setValue(value);
}
