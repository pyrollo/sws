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

#ifndef COREMODULEFACTORY_H
#define COREMODULEFACTORY_H
#include <functional>
#include <map>

class CoreModule;
class CoreSchema;

class CoreModuleFactory
{
public:
    explicit CoreModuleFactory(CoreSchema *schema);
    CoreModule *newModule(std::string type);
protected:
    CoreSchema *mSchema;
    std::map<std::string, std::function<CoreModule *(CoreSchema *schema)>> mFactories;
};

#endif // COREMODULEFACTORY_H
