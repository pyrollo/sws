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

class CoreSchema
{
public:
    CoreSchema();

    CoreModule *newModule(std::string name, std::string type);
    void addModule(CoreModule *module);
    void removeModule(CoreModule *module);
    CoreModule *module(std::string name) const;
    void unprepare() { mPrepared = false; }
    void step();

    void connect(CoreInput *input, CoreOutput *output);
    void disconnect(CoreInput *input, CoreOutput *output);

protected:
    CoreModuleFactory *mModuleFactory;

    std::map<std::string, CoreModule *> mModules;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;

    std::vector<CoreModule *> mScheduledModules;
    bool mPrepared;
    std::mutex mStepMutex;

    bool queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules);

};

#endif // CORESCHEMA_H
