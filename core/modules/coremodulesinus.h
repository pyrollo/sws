#ifndef COREMODULESINUS_H
#define COREMODULESINUS_H

#include "core/coremodule.h"

class CoreModuleSinus : public CoreModule
{
public:
    CoreModuleSinus(CoreSchema *schema);
    void step();

protected:
    CoreInput *mInputOperand;
    CoreOutput *mOutputResult;
};

#endif // COREMODULESINUS_H
