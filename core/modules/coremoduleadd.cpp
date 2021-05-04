#include "coremoduleadd.h"
#include "../coreinput.h"
#include "../coreoutput.h"

CoreModuleAdd::CoreModuleAdd(CoreSchema *schema) :
    CoreModule(schema)
{
    mInputOperand1 = newInput("operand1", 0);
    mInputOperand2 = newInput("operand2", 0);
    mOutputResult =newOutput("result");
}

void CoreModuleAdd::step()
{
    mOutputResult->setValue(mInputOperand1->value() + mInputOperand2->value());
}
