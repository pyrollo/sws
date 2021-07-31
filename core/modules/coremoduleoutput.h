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
    Value value();
    void setName(std::string name);
//    std::string exportedName() { return mName; }

    void writeToBuffer(CoreSampleBuffer *buffer);

protected:
    CoreInput *mInputValue;
//    std::string mName;
    Value *mSchemaOutput;
    CoreSampleBuffer *mWriteBuffer;
};

#endif // COREMODULEOUTPUT_H
