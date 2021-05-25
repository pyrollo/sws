#include "coremodulesinus.h"
#include <cmath>

CoreModuleSinus::CoreModuleSinus(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputOperand =newInput("operand", 0.0f);
    mOutputResult =newOutput("result");
}

void CoreModuleSinus::step()
{
    mOutputResult->setValue(sin(mInputOperand->value() * M_PI * 2.0));
}
