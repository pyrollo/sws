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

#include "coreinput.h"
#include "coreoutput.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"

CoreInput::CoreInput(CoreModule *module, Value defaultValue) :
    CorePlug(module), mDefaultValue(defaultValue), mConnectedTo(nullptr)
{
}

CoreInput::~CoreInput()
{
    if (mConnectedTo)
        mModule->schema()->disconnect(this, mConnectedTo);
}

Value CoreInput::value() const {
    if (mConnectedTo)
        return mConnectedTo->value();
    else
        return mDefaultValue;
}

CoreModule *CoreInput::connectedModule() const
{
    if (mConnectedTo)
        return mConnectedTo->module();
    else
        return nullptr;
}


void CoreInput::listConnectedModules(std::unordered_set<CoreModule *> &list) const
{
    if (mConnectedTo)
        mConnectedTo->module()->listUpstream(list);
}

bool CoreInput::isUpstream(CoreModule *module) const
{
    if (mConnectedTo)
        return mConnectedTo->module()->isUpstream(module);

    return false;
}

void CoreInput::halfConnect(CoreOutput *output)
{
    if (mConnectedTo != nullptr)
        throw CoreAlreadyConnectedEx();

    mConnectedTo = output;
}

void CoreInput::halfDisconnect(CoreOutput *output)
{
    if (mConnectedTo != output)
        throw CoreNotConnectedEx();

    mConnectedTo = nullptr;
}

