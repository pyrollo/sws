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
    Q_INIT_RESOURCE(draw);
    setIconSvgFile(":/module/multiply.svg");

    newInput("operand1", DrawnPlug::left, 0.5f);
    newInput("operand2", DrawnPlug::left, 1.5f);
    newOutput("result", DrawnPlug::right, 1.0f);
}
