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

#ifndef DRAWNITEMFACTORY_H
#define DRAWNITEMFACTORY_H

#include <functional>
#include <map>
#include <vector>

class DrawnItem;
class DrawnSchema;
class DrawnDecoration;
class DrawnModule;

class DrawnItemFactory
{
public:
    DrawnItemFactory();

    DrawnItem *newItem(std::string type, DrawnSchema *schema = nullptr);
    std::vector<std::string> listItems();

    typedef std::function<DrawnItem *(DrawnSchema *schema)> itemConstructor;
    void registerItem(std::string type, itemConstructor constructor);

protected:
    std::map<std::string, itemConstructor> mConstructors;
};

void populateFactory(DrawnItemFactory *factory);

#endif // DRAWNITEMFACTORY_H
