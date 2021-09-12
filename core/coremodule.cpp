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

#include "coremodule.h"
#include "coreschema.h"
#include "coreinput.h"
#include "coreoutput.h"
#include "coreexceptions.h"
#include <vector>

CoreModule::CoreModule(CoreSchema *schema) :
    mSchema(schema)
{
}

CoreModule::~CoreModule()
{
    if (mSchema)
        mSchema->removeModule(this);

    for (auto it : mInputs)
        delete it.second;

    for (auto it : mOutputs)
        delete it.second;
}

CoreInput *CoreModule::newInput(std::string name, Value defaultValue)
{
    CoreInput *input = new CoreInput(this, defaultValue);
    mInputs[name] = input;
    return input;
}

CoreOutput *CoreModule::newOutput(std::string name)
{
    CoreOutput *output = new CoreOutput(this);
    mOutputs[name] = output;
    return output;
}

CoreInput *CoreModule::input(std::string name) const
{
    try {
        return mInputs.at(name);
    } catch(const std::out_of_range&) {
        throw CoreUnknownInputEx(name);
    }
}

CoreOutput *CoreModule::output(std::string name) const
{
    try {
        return mOutputs.at(name);
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

bool CoreModule::isUpstream(CoreModule *module) const
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

bool CoreModule::isDownstream(CoreModule *module) const
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
/*
const std::vector<CoreInput *> CoreModule::inputs() const
{
    std::vector<CoreInput *> result;

    for (auto it = mInputs.begin(); it != mInputs.end(); it++)
        result.push_back(it->second.get());

    return result;
}
*/
