#ifndef COREMODULEINPUT_H
#define COREMODULEINPUT_H

#include "../coremodule.h"
#include "../core.h"

class CoreModuleInput : public CoreModule
{
public:
    CoreModuleInput(CoreSchema *schema);
    void step();
    void exportName(std::string name);
    std::string exportedName() { return mName; }

protected:
    CoreOutput *mOutputValue;
    std::string mName;
    CoreValue *mSchemaInput;
};

#endif // COREMODULEINPUT_H
