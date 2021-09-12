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
#include "modules/drawnmoduletime.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "modules/drawnmoduleclip.h"
#include "modules/drawnmoduleadd.h"
#include "modules/drawnmodulemultiply.h"
#include "modules/drawnmodulesinus.h"

#define ADDMODULECLASS(CLASS) \
    mFactories[CLASS::mType] = [](DrawnSchema *schema, CoreModule *coreModule) { return new CLASS(schema, coreModule); };

DrawnModuleFactory::DrawnModuleFactory()
{
    ADDMODULECLASS(DrawnModuleConstant)
    ADDMODULECLASS(DrawnModuleTime)
    ADDMODULECLASS(DrawnModuleInput)
    ADDMODULECLASS(DrawnModuleOutput)
    ADDMODULECLASS(DrawnModuleClip)
    ADDMODULECLASS(DrawnModuleAdd)
    ADDMODULECLASS(DrawnModuleMultiply)
    ADDMODULECLASS(DrawnModuleSinus)
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
