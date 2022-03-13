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

#include "drawncomment.h"
#include "drawnmodulerectangle.h"
#include "drawnmoduleround.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "modules/drawnmoduleerror.h"

DrawnItemFactory::DrawnItemFactory()
{
}

void DrawnItemFactory::registerDecoration(std::string type, decorationConstructor constructor)
{
    mConstructors[decorationPrefix + type] = constructor;
}

void DrawnItemFactory::registerModule(std::string type, moduleConstructor constructor)
{
    mConstructors[modulePrefix + type] = constructor;
}

DrawnItem *DrawnItemFactory::newItem(std::string type, DrawnSchema *schema)
{
    if (mConstructors.count(type)) {
        return mConstructors.at(type)(schema);
    }
    return nullptr;
}

DrawnModule *DrawnItemFactory::newModule(std::string type, DrawnSchema *schema)
{
    return (DrawnModule *)newItem(modulePrefix + type, schema);
}

DrawnDecoration *DrawnItemFactory::newDecoration(std::string type, DrawnSchema *schema)
{
    return (DrawnDecoration *)newItem(decorationPrefix + type, schema);
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
    // Decorations
    factory->registerDecoration("comment", [](DrawnSchema *schema) { return new DrawnComment(schema); });

    // Base modules
    factory->registerModule("constant", [](DrawnSchema *schema) { return new DrawnModuleConstant(schema); });
    factory->registerModule("input",    [](DrawnSchema *schema) { return new DrawnModuleInput(schema); });
    factory->registerModule("output",   [](DrawnSchema *schema) { return new DrawnModuleOutput(schema); });

    // Generic modules
    factory->registerModule("time", [](DrawnSchema *schema) {
        DrawnModuleRound *module = new DrawnModuleRound("time", schema);
        module->setIcon(":/module/time.svg");
        module->newOutput("time", DrawnPlug::right);
        return module;
    });

    factory->registerModule("multiply", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("multiply", schema);
        module->setIcon(":/module/multiply.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerModule("add", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("add", schema);
        module->setIcon(":/module/add.svg");
        module->newInput("operand1", DrawnPlug::left);
        module->newInput("operand2", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerModule("sine", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("sine", schema);
        module->setIcon(":/module/sine.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });

    factory->registerModule("clip", [](DrawnSchema *schema) {
        DrawnModuleRectangle *module = new DrawnModuleRectangle("clip", schema);
        module->setIcon(":/module/clip.svg");
        module->newInput("operand", DrawnPlug::left);
        module->newOutput("result", DrawnPlug::right);
        return module;
    });
}
