#ifndef COREMODULEINPUT_H
#define COREMODULEINPUT_H

#include "core/coremodule.h"
#include "value/value.h"

class CoreSampleBuffer;

class CoreModuleInput : public CoreModule
{
public:
    CoreModuleInput(CoreSchema *schema);
    ~CoreModuleInput();
    void step();
    void setName(std::string name);
    CorePlug *plug() { return &mSchemaInput; }

protected:
    CoreOutput *mOutputValue;
    CoreInput mSchemaInput;
};

#endif // COREMODULEINPUT_H
