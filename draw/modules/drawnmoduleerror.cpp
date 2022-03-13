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

#include "drawnmoduleerror.h"
#include "draw/style.h"

#include <QPainter>

/*
 * This specific module is a fake module for representing deserialization errors.
 *
 * It can have any type and each demand for an input or output will create it.
 * */

DrawnModuleError::DrawnModuleError(std::string type, DrawnSchema *parentSchema):
    DrawnModuleRectangle(type, parentSchema)
{}

DrawnModuleError::~DrawnModuleError()
{}

DrawnInput *DrawnModuleError::input(std::string name)
{
    return newInput(name, DrawnPlug::left);
}

DrawnOutput *DrawnModuleError::output(std::string name)
{
    return newOutput(name, DrawnPlug::right);
}

void DrawnModuleError::setStyle(QPainter *painter)
{
    DrawnModule::setStyle(painter, Style::cBackgroundError(), Style::cForegroundError());
}

void DrawnModuleError::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = baseRect();
    DrawnModuleRectangle::paint(painter, option, widget);
    painter->drawLine(rect.topLeft(), rect.bottomRight());
    painter->drawLine(rect.topRight(), rect.bottomLeft());
}
