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

#ifndef COREMODULE_H
#define COREMODULE_H
#include "value/value.h"
#include "coreinput.h"
#include "coreoutput.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <mutex>

class CoreSchema;

class CoreModule
{
public:
    CoreModule(CoreSchema *schema);
    virtual ~CoreModule();

    CoreSchema *schema() const { return mSchema; }

    virtual bool interconnected() const { return true; }
    virtual void step() = 0;

    CoreInput  *input(std::string name) const;
    CoreOutput *output(std::string name) const;

    void listUpstream(std::unordered_set<CoreModule *> &list);
    void listDownstream(std::unordered_set<CoreModule *> &list);

    bool isUpstream(CoreModule *module) const;
    bool isDownstream(CoreModule *module) const;

    const std::map<std::string, CoreInput *> inputs() const { return mInputs; }
    const std::map<std::string, CoreOutput *> outputs() const { return mOutputs; }

protected:
    CoreInput  *newInput(std::string name, Value defaultValue);
    CoreOutput *newOutput(std::string name);

    CoreSchema *mSchema;
    std::map<std::string, CoreInput *> mInputs;
    std::map<std::string, CoreOutput *> mOutputs;
};

#endif // COREMODULE_H
