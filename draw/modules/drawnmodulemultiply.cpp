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

#include "drawnmodulemultiply.h"
#include <QPainter>

DrawnModuleMultiply::DrawnModuleMultiply(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 2.0f, 2.0f)
{
    newInput("operand1", DrawnPlug::left, 0.5f);
    newInput("operand2", DrawnPlug::left, 1.5f);
    newOutput("result", DrawnPlug::right, 1.0f);
}

void DrawnModuleMultiply::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(0.7f, 0.7f);
    path.lineTo(1.3f, 1.3f);
    path.moveTo(1.3f, 0.7f);
    path.lineTo(0.7f, 1.3f);
    painter->drawPath(path);
}
