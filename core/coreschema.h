#ifndef CORESCHEMA_H
#define CORESCHEMA_H
#include "core.h"
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <mutex>

class CoreModuleFactory;
class CoreModule;
class CoreInput;
class CoreOutput;
class CoreModuleOutput;
class CoreModuleInput;

class CoreSchema
{
public:
    CoreSchema();

    CoreModule *newModule(std::string type);
    void addModule(CoreModule *module);
    void removeModule(CoreModule *module);
    void unprepare() { mPrepared = false; }
    void step();

    void connect(CoreInput *input, CoreOutput *output);
    void disconnect(CoreInput *input, CoreOutput *output);

    CoreValue getTime() { return mTime; }
    void setTime(CoreValue time) { mTime = time; }

    void setInputName(CoreModuleInput *module, std::string name);
    const std::map<std::string, CoreModuleInput *> &inputs() { return mInputs; }
    CoreModuleInput *input(std::string name) { return mInputs.at(name); }

    void setOutputName(CoreModuleOutput *module, std::string name);
    const std::map<std::string, CoreModuleOutput *> &outputs() { return mOutputs; }
    CoreModuleOutput *output(std::string name) { return mOutputs.at(name); }

protected:
    CoreModuleFactory *mModuleFactory;

    std::unordered_set<CoreModule *> mModules;
    std::map<std::string, CoreModuleInput *> mInputs;
    std::map<std::string, CoreModuleOutput *> mOutputs;
    CoreValue mTime;

    std::vector<CoreModule *> mScheduledModules;
    bool mPrepared;
    std::mutex mStepMutex;

    bool queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules);

};

#endif // CORESCHEMA_H
