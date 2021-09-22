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

#ifndef COREOUTPUT_H
#define COREOUTPUT_H
#include <unordered_set>
#include "coreplug.h"

class CoreInput;

class CoreOutput : public CorePlug
{
public:
    explicit CoreOutput(CoreModule *module);
    ~CoreOutput();

    Value value() const override { return mValue; }
    void setValue(Value value) { mValue = value; }

    void listConnectedModules(std::unordered_set<CoreModule *> &list);
    bool isDownstream(CoreModule *module) const;

    // Internal use only
    void halfConnect(CoreInput *input);
    void halfDisconnect(CoreInput *input);

protected:
    Value mValue;
    std::unordered_set<CoreInput *> mConnectedTo;
};

#endif // COREOUTPUT_H
