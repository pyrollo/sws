#include "coremodulemultiply.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"

CoreModuleMultiply::CoreModuleMultiply(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputOperand1 = newInput("operand1", 1.0f);
    mInputOperand2 = newInput("operand2", 1.0f);
    mOutputResult =newOutput("result");
}

void CoreModuleMultiply::step()
{
    mOutputResult->setValue(mInputOperand1->value() * mInputOperand2->value());
}

