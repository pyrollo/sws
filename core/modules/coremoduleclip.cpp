#include "coremoduleclip.h"
#include "../coreinput.h"
#include "../coreoutput.h"
#include <cmath>

CoreModuleClip::CoreModuleClip(CoreSchema *schema):
    CoreModule(schema)
{
    mInputOperand = newInput("operand", 0);
    mOutputResult = newOutput("result");
}

void CoreModuleClip::step()
{
    double integral;
    mOutputResult->setValue(modf(mInputOperand->value(), &integral));
}
