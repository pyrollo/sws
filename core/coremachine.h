#ifndef COREMACHINE_H
#define COREMACHINE_H
#include "core.h"
#include <map>

class CoreModule;

class CoreMachine
{
public:
    CoreMachine();
    CoreMachine(CoreValue step_time);
    void prepare();
    void step();

protected:
    CoreValue time;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;
};

#endif // COREMACHINE_H
