#ifndef COREMODULEINPUT_H
#define COREMODULEINPUT_H

#include "../coremodule.h"
#include "../core.h"

class CoreSampleBuffer;

class CoreModuleInput : public CoreModule
{
public:
    CoreModuleInput(CoreSchema *schema);
    ~CoreModuleInput();
    void step();
    CoreValue value();
    void setName(std::string name);
//    std::string exportedName() { return mName; }
    void readFromBuffer(CoreSampleBuffer *buffer);

protected:
    CoreOutput *mOutputValue;
//    std::string mName;
    CoreValue *mSchemaInput;
    CoreSampleBuffer *mReadBuffer;
};

#endif // COREMODULEINPUT_H
