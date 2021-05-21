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

    CoreModule *newModule(std::string type);
    void addModule(CoreModule *module);
    void removeModule(CoreModule *module);
    void unprepare() { mPrepared = false; }
    void step();

    void connect(CoreInput *input, CoreOutput *output);
    void disconnect(CoreInput *input, CoreOutput *output);

    CoreValue getTime() { return mTime; }
    void setTime(CoreValue time) { mTime = time; }

protected:
    CoreModuleFactory *mModuleFactory;

    std::unordered_set<CoreModule *> mModules;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;
    CoreValue mTime;

    std::vector<CoreModule *> mScheduledModules;
    bool mPrepared;
    std::mutex mStepMutex;

    bool queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules);

};

#endif // CORESCHEMA_H
