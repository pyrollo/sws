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

#include "drawnmodulefactory.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "drawnmodulerectangle.h"
#include "drawnmoduleround.h"

#define ADDMODULECLASS(TYPE, CLASS) \
    mFactories[TYPE] = [](DrawnSchema *schema, CoreModule *coreModule) { return new CLASS(schema, coreModule); };

DrawnModuleFactory::DrawnModuleFactory()
{
    ADDMODULECLASS("constant", DrawnModuleConstant)
    ADDMODULECLASS("input", DrawnModuleInput)
    ADDMODULECLASS("output", DrawnModuleOutput)

    mFactories["time"] = [](DrawnSchema *schema, CoreModule *coreModule)
    {
        DrawnModuleRound *module = new DrawnModuleRound("time", schema, coreModule);
        module->setIcon(":/module/time.svg");
        module->newOutput("time", DrawnPlug::right);
        return module;
    };

    mFactories["multiply"] = [](DrawnSchema *schema, CoreModule *coreModule)
    {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("multiply", schema, coreModule);
        module->setIcon(":/module/multiply.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    };

    mFactories["add"] = [](DrawnSchema *schema, CoreModule *coreModule)
    {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("add", schema, coreModule);
        module->setIcon(":/module/add.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    };

    mFactories["sine"] = [](DrawnSchema *schema, CoreModule *coreModule)
    {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("sine", schema, coreModule);
        module->setIcon(":/module/sine.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    };

    mFactories["clip"] = [](DrawnSchema *schema, CoreModule *coreModule)
    {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("clip", schema, coreModule);
        module->setIcon(":/module/clip.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    };
}

DrawnModule *DrawnModuleFactory::newModule(std::string type, DrawnSchema *schema, CoreModule *coreModule)
{
    return mFactories.at(type)(schema, coreModule);
}

std::vector<std::string> DrawnModuleFactory::listModules()
{
    std::vector<std::string> result;
    for (auto it: mFactories)
        result.push_back(it.first);

    return result;
}
