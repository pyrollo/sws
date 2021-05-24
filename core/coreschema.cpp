#include "coreschema.h"
#include "coreexceptions.h"
#include "coremodule.h"
#include "coreinput.h"
#include "coreoutput.h"
#include "coremodulefactory.h"
#include "core.h"

CoreSchema::CoreSchema() :
    mTime(0), mPrepared(false)
{
    mModuleFactory = new CoreModuleFactory(this);
}

CoreModule *CoreSchema::newModule(std::string type)
{
    std::lock_guard<std::mutex> lock(mStepMutex);

    CoreModule *module = mModuleFactory->newModule(type);

    if (module) {
        mModules.insert(module);
        mPrepared = false;
    }

    return module;
}

void CoreSchema::removeModule(CoreModule *module)
{
    std::lock_guard<std::mutex> lock(mStepMutex);

    if (module->schema() != this)
        throw CoreNotSameSchemaEx();

    if (mModules.erase(module))
        mPrepared = false;
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

    // Prepare for step - Schedule modules in the right order to perform computations
    if (!mPrepared) {
        mScheduledModules.clear();

        std::unordered_set<CoreModule *> unscheduledModules = mModules;

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

void CoreSchema::setOutputName(CoreModuleOutput *module, std::string name)
{
    std::string oldname = "";

    std::lock_guard<std::mutex> lock(mStepMutex);

    // Check module is not yet registered
    for (auto it : mOutputs)
        if (it.second == module) {
            oldname = it.first;
            break;
        }

    if (oldname == name)
        return;

    // Check if new name is available
    if (mOutputs.find(name) != mOutputs.end())
        throw CoreDuplicateNameEx(name);

    if (oldname != "")
        mOutputs.erase(oldname);

    mOutputs[name] = module;
}

void CoreSchema::setInputName(CoreModuleInput *module, std::string name)
{
    std::string oldname = "";

    std::lock_guard<std::mutex> lock(mStepMutex);

    // Check module is not yet registered
    for (auto it : mInputs)
        if (it.second == module) {
            oldname = it.first;
            break;
        }

    if (oldname == name)
        return;

    // Check if new name is available
    if (mInputs.find(name) != mInputs.end())
        throw CoreDuplicateNameEx(name);

    if (oldname != "")
        mInputs.erase(oldname);

    mInputs[name] = module;
}


