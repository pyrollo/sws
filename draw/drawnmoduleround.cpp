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

#include "drawnmoduleround.h"
#include "style.h"
#include "drawninput.h"
#include "drawnoutput.h"

#include <QPainter>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>

DrawnModuleRound::DrawnModuleRound(std::string type, DrawnSchema *parentSchema):
    DrawnModule(type, parentSchema)
{}

QRectF DrawnModuleRound::boundingRect() const
{
    float margin = Style::wModule();
    return QRectF(-margin * 0.5f, -margin * 0.5f, 2 * Style::sGrid() + margin, 2 * Style::sGrid() + margin);
}

void DrawnModuleRound::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    QPainterPath path;
    path.addEllipse(0.0f, 0.0f, 2.0f, 2.0f);
    painter->drawPath(path);
}

void DrawnModuleRound::placePlug(DrawnPlug *plug, DrawnPlug::Orientation orientation)
{
    float margin = Style::wModule() * 0.5;
    plug->setOrientation(orientation);
    switch(orientation) {
    case DrawnPlug::top:
        plug->moveBy(1.0f, margin);
        break;
    case DrawnPlug::right:
        plug->moveBy(2.0f - margin, 1.0f);
        break;
    case DrawnPlug::bottom:
        plug->moveBy(1.0f, 2.0f - margin);
        break;
    case DrawnPlug::left:
        plug->moveBy(margin, 1.0f);
        break;
    }
}

void DrawnModuleRound::newInput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnInput *input = DrawnModule::newInput(name);
    placePlug(input, orientation);
}

void DrawnModuleRound::newOutput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    placePlug(output, orientation);
}
