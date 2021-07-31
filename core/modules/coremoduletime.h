#ifndef COREMODULETIME_H
#define COREMODULETIME_H

#include "core/coremodule.h"

class CoreModuleTime : public CoreModule
{
public:
    CoreModuleTime(CoreSchema *schema);
    void step();

protected:
    CoreOutput *mOutputTime;
};

#endif // COREMODULETIME_H
