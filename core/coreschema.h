#ifndef CORESCHEMA_H
#define CORESCHEMA_H
#include "core.h"
#include <string>
#include <map>
#include <vector>
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
    bool mPrepared;

    std::map<std::string, CoreModule *> mModules;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;

    std::vector<CoreModule *> orderedModules;

    bool isQueued(CoreModule *module) const;
    bool tryQueue(CoreModule *module);

    std::mutex mStepMutex;
};

#endif // CORESCHEMA_H
