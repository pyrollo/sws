#ifndef CORESCHEMA_H
#define CORESCHEMA_H
#include "core.h"
#include <string>
#include <map>
#include <vector>

class CoreModuleFactory;
class CoreModule;

class CoreSchema
{
public:
    CoreSchema();
    CoreModule *newModule(std::string name, std::string type);
    void addModule(CoreModule *module);
    void removeModule(CoreModule *module);
    CoreModule *module(std::string name);
    void unprepare() { mPrepared = false; }
    void prepare();
    void step();

protected:
    CoreModuleFactory *mModuleFactory;
    bool mPrepared;

    std::map<std::string, CoreModule *> mModules;
    std::map<std::string, CoreValue> mInputs;
    std::map<std::string, CoreValue> mOutputs;

 //   std::vector<std::unique_ptr<CoreModule>> modules;
    std::vector<CoreModule *> orderedModules;

    bool isQueued(CoreModule *module);
    bool tryQueue(CoreModule *module);
};

#endif // CORESCHEMA_H
