#ifndef COREMODULEOUTPUT_H
#define COREMODULEOUTPUT_H

#include "value/value.h"
#include "core/coremodule.h"

class CoreSampleBuffer;

class CoreModuleOutput : public CoreModule
{
public:
    CoreModuleOutput(CoreSchema *schema);
    ~CoreModuleOutput();
    void step();
    void setName(std::string name);
    CorePlug *plug() { return &mSchemaOutput; }

protected:
    CoreInput *mInputValue;
    CoreOutput mSchemaOutput;
};

#endif // COREMODULEOUTPUT_H
