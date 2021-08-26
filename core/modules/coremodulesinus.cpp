#include "coremodulesinus.h"
#include "math.h"

CoreModuleSinus::CoreModuleSinus(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputOperand =newInput("operand", 0.0f);
    mOutputResult =newOutput("result");
}

void CoreModuleSinus::step()
{
    mOutputResult->setValue(Value(sin(mInputOperand->value().moduloOne().toDouble() * M_PI * 2.0)));
}
