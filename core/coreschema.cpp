#include "coreschema.h"
#include "coreexceptions.h"
#include "coremodule.h"
#include "coreinput.h"
#include "coreoutput.h"
#include "coremodulefactory.h"

CoreSchema::CoreSchema() :
    mPrepared(false)
{
    mModuleFactory = new CoreModuleFactory(this);
}

CoreModule *CoreSchema::newModule(std::string name, std::string type)
{
    std::lock_guard<std::mutex> lock(mStepMutex);

    if (mModules.find(name) != mModules.end())
        throw CoreDuplicateNameEx(name);

    CoreModule *module = mModuleFactory->newModule(type);

    if (module) {
        mModules[name] = module;
        mPrepared = false;
    }

    return module;
}

void CoreSchema::removeModule(CoreModule *module)
{
    std::lock_guard<std::mutex> lock(mStepMutex);

    for (auto it : mModules)
        if (it.second == module) {
            mModules.erase(it.first);
            mPrepared = false;
            return;
        }
}

CoreModule *CoreSchema::module(std::string name) const
{
    try {
        return mModules.at(name);
    } catch (const std::out_of_range&) {
        throw CoreUnknownModuleEx(name);
    }
}


// This part needs optimization (isQueued, tryQueue and prepare).
// Could be done by using a set of ordered modules instead of searching in vector.
// Something to do also for inputConnectedModules

bool CoreSchema::isQueued(CoreModule *module) const
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

void CoreSchema::step()
{
    std::lock_guard<std::mutex> lock(mStepMutex);

    if (!mPrepared) {
        bool change;
        orderedModules.clear();

        do {
            change = false;
            for (auto it = mModules.begin(); it != mModules.end(); it++)
                change = change || tryQueue(it->second);
        } while(change);

        if (orderedModules.size() != mModules.size()) {
            throw CoreCantScheduleModulesEx();
        }

        mPrepared = true;
    }

    for (auto module: orderedModules)
        module->step();
}

void CoreSchema::connect(CoreInput *input, CoreOutput *output)
{
    if (input->module()->schema() != this ||
            output->module()->schema() != this)
        throw CoreNotSameSchemaEx();

    if (output->module()->isUpstream(input->module()))
        throw CoreLoopConnectionEx();

    std::lock_guard<std::mutex> lock(mStepMutex);
    input->halfConnect(output);
    output->halfConnect(input);
    mPrepared = false;
}

void CoreSchema::disconnect(CoreInput *input, CoreOutput *output)
{
    if (input->module()->schema() != this ||
            output->module()->schema() != this)
        throw CoreNotSameSchemaEx();

    std::lock_guard<std::mutex> lock(mStepMutex);
    output->halfDisconnect(input);
    input->halfDisconnect(output);
    mPrepared = false;
}
