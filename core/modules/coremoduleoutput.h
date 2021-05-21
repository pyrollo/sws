#ifndef COREMODULEOUTPUT_H
#define COREMODULEOUTPUT_H

#include "../coremodule.h"
#include "../core.h"

class CoreModuleOutput : public CoreModule
{
public:
    CoreModuleOutput(CoreSchema *schema);
    void step();
    void exportName(std::string name);
    std::string exportedName() { return mName; }

protected:
    CoreInput *mInputValue;
    std::string mName;
    CoreValue *mSchemaOutput;
};

#endif // COREMODULEOUTPUT_H
