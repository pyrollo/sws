#include "coremoduleconstant.h"

CoreModuleConstant::CoreModuleConstant(CoreSchema *schema) :
    CoreModule(schema)
{
    mOutputValue = newOutput("value");
}

void CoreModuleConstant::setValue(Value value)
{
    mOutputValue->setValue(value);
}
