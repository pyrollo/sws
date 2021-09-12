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

#include "drawnmoduleadd.h"
#include <QPainter>

DrawnModuleAdd::DrawnModuleAdd(DrawnSchema *schema, CoreModule *coreModule):
    DrawnModuleRectangle(schema, coreModule, 2.0f, 2.0f)
{
    newInput("operand1", DrawnPlug::left, 0.5f);
    newInput("operand2", DrawnPlug::left, 1.5f);
    newOutput("result", DrawnPlug::right, 1.0f);
}

void DrawnModuleAdd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(1.0f, 0.6f);
    path.lineTo(1.0f, 1.4f);
    path.moveTo(0.6f, 1.0f);
    path.lineTo(1.4f, 1.0f);
    painter->drawPath(path);
}
