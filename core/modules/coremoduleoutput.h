#ifndef COREMODULEOUTPUT_H
#define COREMODULEOUTPUT_H

#include "../coremodule.h"

class CoreModuleOutput : public CoreModule
{
public:
    CoreModuleOutput(CoreSchema *schema);
    void step();

protected:
    CoreInput *mInputValue;
};

#endif // COREMODULEOUTPUT_H
