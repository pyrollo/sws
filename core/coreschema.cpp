/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "coreschema.h"
#include "coreexceptions.h"
#include "coremodule.h"
#include "coreinput.h"
#include "coreoutput.h"
#include "coremodulefactory.h"
#include "coresamplebuffer.h"
#include "value/value.h"

CoreSchema::CoreSchema() :
    mTime(0.0f), mPrepared(false)
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
    std::lock_guard<std::mutex> steplock(mStepMutex);

    if (module->schema() != this)
        throw CoreNotSameSchemaEx();

    if (mModules.erase(module)) {
        {   // Disconnect reading buffers if any
            std::lock_guard<std::mutex> bufferlock(mBuffersMutex);
            for (auto it = mReadingBuffers.begin(); it != mReadingBuffers.end();)
                if (it->second.first == module)
                    it = mReadingBuffers.erase(it);
                else
                    it ++;
        }

        mPrepared = false;
    }
}

bool CoreSchema::queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules)
{
    // Check that all upstream modules are queued
    if (module->interconnected())
        for (auto it: module->inputs()) {
            CoreModule *connectedModule = it.second->connectedModule();
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

    // Read buffers update
    for (auto it : mReadingBuffers)
        it.first->writeSample(it.second.second->value());
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

    std::lock_guard<std::mutex> steplock(mStepMutex);

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

    // Register only named outputs
    if (name != "")
        mOutputs[name] = module;
}

void CoreSchema::setInputName(CoreModuleInput *module, std::string name)
{
    std::string oldname = "";

    std::lock_guard<std::mutex> steplock(mStepMutex);

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

    // Register only named inputs
    if (name != "")
        mInputs[name] = module;
}

void CoreSchema::connectReadingBuffer(CoreSampleBuffer *buffer, CorePlug *plug)
{
    std::lock_guard<std::mutex> bufferlock(mBuffersMutex);

    // Disconnect first
    mReadingBuffers.erase(buffer);

    // Check module & plug
    if (plug->module()->schema() != this)
        throw CoreNotSameSchemaEx();

    mReadingBuffers[buffer].first = plug->module();
    mReadingBuffers[buffer].second = plug;
}

void CoreSchema::disconnectReadingBuffer(CoreSampleBuffer *buffer)
{
    std::lock_guard<std::mutex> bufferlock(mBuffersMutex);

    mReadingBuffers.erase(buffer);
}

