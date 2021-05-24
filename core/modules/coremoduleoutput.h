#ifndef COREMODULEOUTPUT_H
#define COREMODULEOUTPUT_H

#include "../core.h"
#include "../coremodule.h"

class CoreSampleBuffer;

class CoreModuleOutput : public CoreModule
{
public:
    CoreModuleOutput(CoreSchema *schema);
    ~CoreModuleOutput();
    void step();
    CoreValue value();
    void setName(std::string name);
//    std::string exportedName() { return mName; }

    void writeToBuffer(CoreSampleBuffer *buffer);

protected:
    CoreInput *mInputValue;
//    std::string mName;
    CoreValue *mSchemaOutput;
    CoreSampleBuffer *mWriteBuffer;
};

#endif // COREMODULEOUTPUT_H
