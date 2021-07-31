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
    Value value();
    void setName(std::string name);
//    std::string exportedName() { return mName; }
    void readFromBuffer(CoreSampleBuffer *buffer);

protected:
    CoreOutput *mOutputValue;
//    std::string mName;
    Value *mSchemaInput;
    CoreSampleBuffer *mReadBuffer;
};

#endif // COREMODULEINPUT_H
