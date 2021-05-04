#ifndef COREMODULECONSTANT_H
#define COREMODULECONSTANT_H

#include "../core.h"
#include "../coremodule.h"

class CoreModuleConstant : public CoreModule
{
public:
    CoreModuleConstant(CoreSchema *schema);
    void step() {}
    void setValue(CoreValue value);
protected:
    CoreOutput *mOutputValue;
};

#endif // COREMODULECONSTANT_H
