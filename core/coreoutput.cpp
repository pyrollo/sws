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

#include "coreoutput.h"
#include "coreinput.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"

CoreOutput::CoreOutput(CoreModule *module) :
    CorePlug(module), mValue(0.0f)
{
}

CoreOutput::~CoreOutput()
{
    for (const auto& connectedTo: mConnectedTo)
        mModule->schema()->disconnect(connectedTo, this);
}

void CoreOutput::listConnectedModules(std::unordered_set<CoreModule *> &list)
{
    for (const auto& connectedTo: mConnectedTo)
        connectedTo->module()->listDownstream(list);
}

bool CoreOutput::isDownstream(CoreModule *module) const
{
    for (const auto& connectedTo: mConnectedTo)
        if (connectedTo->module()->isDownstream(module))
            return true;

    return false;
}

void CoreOutput::halfConnect(CoreInput *input)
{
    auto result = mConnectedTo.insert(input);
    if (!result.second)
        throw CoreAlreadyConnectedEx();
}

void CoreOutput::halfDisconnect(CoreInput *input)
{
    if (!mConnectedTo.erase(input))
        throw CoreNotConnectedEx();
}

