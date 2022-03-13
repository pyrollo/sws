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

#include "drawnitemfactory.h"

#include "drawnmodulerectangle.h"
#include "drawnmoduleround.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "modules/drawnmoduleerror.h"

DrawnItemFactory::DrawnItemFactory()
{
}

void DrawnItemFactory::registerItem(std::string type, itemConstructor constructor)
{
    mConstructors[type] = constructor;
}

DrawnItem *DrawnItemFactory::newItem(std::string type, DrawnSchema *schema)
{
    if (mConstructors.count(type)) {
        return mConstructors.at(type)(schema);
    }
    return nullptr;
}

std::vector<std::string> DrawnItemFactory::listItems()
{
    std::vector<std::string> result;
    for (auto it: mConstructors)
        result.push_back(it.first);

    return result;
}

void populateFactory(DrawnItemFactory *factory)
{
    // Base modules
    factory->registerItem("constant", [](DrawnSchema *schema) { return new DrawnModuleConstant(schema); });
    factory->registerItem("input",    [](DrawnSchema *schema) { return new DrawnModuleInput(schema); });
    factory->registerItem("output",   [](DrawnSchema *schema) { return new DrawnModuleOutput(schema); });

    // Generic modules
    factory->registerItem("time", [](DrawnSchema *schema) {
        DrawnModuleRound *module = new DrawnModuleRound("time", schema);
        module->setIcon(":/module/time.svg");
        module->newOutput("time", DrawnPlug::right);
        return module;
    });

    factory->registerItem("multiply", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("multiply", schema);
        module->setIcon(":/module/multiply.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerItem("add", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("add", schema);
        module->setIcon(":/module/add.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerItem("sine", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("sine", schema);
        module->setIcon(":/module/sine.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerItem("clip", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("clip", schema);
        module->setIcon(":/module/clip.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });
}
