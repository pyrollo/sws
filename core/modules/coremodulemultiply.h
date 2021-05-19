#ifndef COREMODULEMULTIPLY_H
#define COREMODULEMULTIPLY_H

#include "../coremodule.h"

class CoreModuleMultiply : public CoreModule
{
public:
    CoreModuleMultiply(CoreSchema *schema);
    void step();

protected:
    CoreInput *mInputOperand1;
    CoreInput *mInputOperand2;
    CoreOutput *mOutputResult;
};

#endif // COREMODULEMULTIPLY_H
