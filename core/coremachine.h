#ifndef COREMACHINE_H
#define COREMACHINE_H

#include "core.h"
#include <map>
#include <memory>

class CoreModule;

class CoreMachine
{
public:
    CoreMachine();
    /*
    CoreMachine(CoreValue step_time);
    void prepare();
    void step();

protected:
    std::vector<std::unique_ptr<CoreModule>> modules;
    std::vector<CoreModule *> orderedModules;
    CoreValue time;
    */

    std::map<std::string, std::unique_ptr<CoreModule>> mModules;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;
};

#endif // COREMACHINE_H
