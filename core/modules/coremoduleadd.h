#ifndef COREMODULEADD_H
#define COREMODULEADD_H

#include "../coremodule.h"

class CoreModuleAdd : public CoreModule
{
public:
    CoreModuleAdd(CoreSchema *schema);
    void step();

protected:
    CoreInput *mInputOperand1;
    CoreInput *mInputOperand2;
    CoreOutput *mOutputResult;
};

#endif // COREMODULEADD_H
