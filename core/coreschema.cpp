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

bool CoreSchema::queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules)
{
    // Check that all upstream modules are queued
    if (module->interconnected())
        for (auto input: module->inputs()) {
            CoreModule *connectedModule = input->connectedModule();
            if (connectedModule && unscheduledModules.find(connectedModule) != unscheduledModules.end())
                return false;
        }

    return true;
}

void CoreSchema::step()
{
    const std::lock_guard<std::mutex> lock(mStepMutex);

    // Prepare for step
    if (!mPrepared) {
        mScheduledModules.clear();

        std::unordered_set<CoreModule *> unscheduledModules;
        for (auto it: mModules)
            unscheduledModules.insert(it.second);

        bool change;
        do {
            change = false;
            for (auto module = unscheduledModules.begin(); module != unscheduledModules.end(); ) {
                if (queuable(*module, unscheduledModules)) {
                    change = true;
                    mScheduledModules.push_back(*module);
                    module = unscheduledModules.erase(module);
                } else
                    module++;
            }
        } while(change);

        if (unscheduledModules.size()) {
            throw CoreCantScheduleModulesEx();
        }
        mPrepared = true;
    }

    // Actual step operation
    for (auto module: mScheduledModules)
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
