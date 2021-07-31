#ifndef COREMODULECONSTANT_H
#define COREMODULECONSTANT_H

#include "value/value.h"
#include "core/coremodule.h"

class CoreModuleConstant : public CoreModule
{
public:
    CoreModuleConstant(CoreSchema *schema);
    void step() {}
    void setValue(Value value);
    Value getValue() { return mOutputValue->value(); }
protected:
    CoreOutput *mOutputValue;
};

#endif // COREMODULECONSTANT_H
