#ifndef COREMODULEINPUT_H
#define COREMODULEINPUT_H

#include "../coremodule.h"

class CoreModuleInput : public CoreModule
{
public:
    CoreModuleInput(CoreSchema *schema);
    void step();

protected:
    CoreOutput *mOutputValue;
};

#endif // COREMODULEINPUT_H
