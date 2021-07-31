#ifndef COREMODULECLIP_H
#define COREMODULECLIP_H

#include "core/coremodule.h"

class CoreModuleClip : public CoreModule
{
public:
    CoreModuleClip(CoreSchema *schema);
    void step();

protected:
    CoreInput *mInputOperand;
    CoreOutput *mOutputResult;
};

#endif // COREMODULECLIP_H
