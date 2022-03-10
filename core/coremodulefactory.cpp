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

#include "coremodulefactory.h"
#include "coreexceptions.h"
#include "modules/coremoduleconstant.h"
#include "modules/coremoduletime.h"
#include "modules/coremoduleinput.h"
#include "modules/coremoduleoutput.h"
#include "modules/coremoduleclip.h"
#include "modules/coremoduleadd.h"
#include "modules/coremodulemultiply.h"
#include "modules/coremodulesine.h"

class CoreSchema;

CoreModuleFactory::CoreModuleFactory(CoreSchema *schema) :
    mSchema(schema)
{
    mFactories["constant"] = [](CoreSchema *schema) { return new CoreModuleConstant(schema); };
    mFactories["time"]     = [](CoreSchema *schema) { return new CoreModuleTime(schema); };
    mFactories["input"]    = [](CoreSchema *schema) { return new CoreModuleInput(schema); };
    mFactories["output"]   = [](CoreSchema *schema) { return new CoreModuleOutput(schema); };
    mFactories["clip"]     = [](CoreSchema *schema) { return new CoreModuleClip(schema); };
    mFactories["add"]      = [](CoreSchema *schema) { return new CoreModuleAdd(schema); };
    mFactories["multiply"] = [](CoreSchema *schema) { return new CoreModuleMultiply(schema); };
    mFactories["sine"]     = [](CoreSchema *schema) { return new CoreModuleSine(schema); };
}

CoreModule *CoreModuleFactory::newModule(std::string type)
{
    try {
        return mFactories.at(type)(mSchema);
    } catch(const std::out_of_range&) {
        throw CoreUnknownTypeEx(type);
    }
}
