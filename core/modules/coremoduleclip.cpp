#include "coremoduleclip.h"

CoreModuleClip::CoreModuleClip(CoreSchema *schema):
    CoreModule(schema)
{
    mInputOperand = newInput("operand", 0.0f);
    mOutputResult = newOutput("result");
}

void CoreModuleClip::step()
{
    mOutputResult->setValue(mInputOperand->value().moduloOne());
}
