#include "coremoduleadd.h"

CoreModuleAdd::CoreModuleAdd(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputOperand1 = newInput("operand1", 0.0f);
    mInputOperand2 = newInput("operand2", 0.0f);
    mOutputResult = newOutput("result");
}

void CoreModuleAdd::step()
{
    mOutputResult->setValue(mInputOperand1->value() + mInputOperand2->value());
}
