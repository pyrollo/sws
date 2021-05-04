#include "coreschema.h"
#include "coremodule.h"
#include "coremodulefactory.h"
#include "coreexceptions.h"

CoreSchema::CoreSchema() :
    mPrepared(false)
{
    mModuleFactory = new CoreModuleFactory(this);
}

CoreModule *CoreSchema::newModule(std::string name, std::string type)
{
    if (mModules.find(name) != mModules.end())
        throw CoreDuplicateNameEx(name);

    CoreModule *module = mModuleFactory->newModule(type);

    mModules[name] = std::unique_ptr<CoreModule>(module);

    mPrepared = false;

    return module;
}

CoreModule *CoreSchema::module(std::string name)
{
    try {
        return mModules.at(name).get();
    } catch (const std::out_of_range&) {
        throw CoreUnknownModuleEx(name);
    }
}

void CoreSchema::step()
{
    if (!mPrepared)
        prepare();

    for (auto module: orderedModules)
        module->step();
}

// This part needs optimization (isQueued, tryQueue and prepare).
// Could be done by using a set of ordered modules instead of searching in vector.
// Something to do also for inputConnectedModules

bool CoreSchema::isQueued(CoreModule *module)
{
    for (auto module2 : orderedModules)
        if (module2 == module)
            return true;
    return false;
}

bool CoreSchema::tryQueue(CoreModule *module)
{
    if (isQueued(module))
        return false;

    // Check that all upstream modules are queued
    if (module->interconnected())
        for (auto module2: module->inputConnectedModules())
            if (!isQueued(module2))
                return false;

    orderedModules.push_back(module);
    return true;
}

void CoreSchema::prepare()
{
    bool change;
    orderedModules.clear();

    do {
        change = false;
        for (auto it = mModules.begin(); it != mModules.end(); it++)
            change = change || tryQueue(it->second.get());
    } while(change);

    if (orderedModules.size() != mModules.size()) {
        throw CoreCantScheduleModulesEx();
    }

    mPrepared = true;
}
