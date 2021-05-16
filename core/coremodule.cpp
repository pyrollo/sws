#include "coremodule.h"
#include "coreschema.h"
#include "coreinput.h"
#include "coreoutput.h"
#include "coreexceptions.h"
#include <vector>

#include <iostream>

CoreModule::CoreModule(CoreSchema *schema) :
    mSchema(schema)
{
}

CoreModule::~CoreModule()
{
    if (mSchema)
        mSchema->removeModule(this);
}

CoreInput *CoreModule::newInput(std::string name, CoreValue defaultValue)
{
    CoreInput *input = new CoreInput(this, defaultValue);
    mInputs[name] = std::unique_ptr<CoreInput>(input);
    return input;
}

CoreOutput *CoreModule::newOutput(std::string name)
{
    CoreOutput *output = new CoreOutput(this);
    mOutputs[name] = std::unique_ptr<CoreOutput>(output);
    return output;
}

CoreInput *CoreModule::input(std::string name)
{
    try {
        return mInputs.at(name).get();
    } catch(const std::out_of_range&) {
        throw CoreUnknownInputEx(name);
    }
}

CoreOutput *CoreModule::output(std::string name)
{
    try {
        return mOutputs.at(name).get();
    } catch(const std::out_of_range&) {
        throw CoreUnknownOutputEx(name);
    }
}

void CoreModule::listUpstream(std::unordered_set<CoreModule *> &list)
{
    if (interconnected()) {
        list.insert(this);
        for (auto it = mInputs.begin(); it != mInputs.end(); it++)
            it->second->listConnectedModules(list);

    }
}

void CoreModule::listDownstream(std::unordered_set<CoreModule *> &list)
{
    if (interconnected()) {
        list.insert(this);
        for (auto it = mOutputs.begin(); it != mOutputs.end(); it++)
            it->second->listConnectedModules(list);
    }
}

bool CoreModule::isUpstream(CoreModule *module)
{
    if (!interconnected())
        return false;

    if (module == this)
        return true;

    for (auto it = mInputs.begin(); it != mInputs.end(); it++)
        if (it->second->isUpstream(module))
            return true;

    return false;
}

bool CoreModule::isDownstream(CoreModule *module)
{
    if (!interconnected())
        return false;

    if (module == this)
        return true;

    for (auto it = mOutputs.begin(); it != mOutputs.end(); it++)
        if (it->second->isDownstream(module))
            return true;

    return false;
}

const std::vector<CoreModule *> CoreModule::inputConnectedModules()
{
    std::vector<CoreModule *> result;
    for (auto it = mInputs.begin(); it != mInputs.end(); it++)
        result.push_back(it->second->module());

    return result;
}
