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

#include "drawnmodulerectangle.h"
#include "gui/guistyle.h"

#include <QPainter>
#include <QSvgRenderer>

DrawnModuleRectangle::DrawnModuleRectangle(DrawnSchema *parentSchema, CoreModule *coreModule, float width, float height):
    DrawnModule(parentSchema, coreModule), mWidth(width), mHeight(height)
{
    float margin = GuiStyle::wModule() * 0.5f;
    mPosGridAnchor = QPointF(margin, margin);
}

QRectF DrawnModuleRectangle::boundingRect() const
{
    float margin = GuiStyle::wModule();
    return QRectF(-margin * 0.5f, -margin * 0.5f, mWidth + margin, mHeight + margin);
}

void DrawnModuleRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    QPainterPath path;
    path.addRoundedRect(0.0f, 0.0f, mWidth, mHeight, 0.1f, 0.1f);
    painter->drawPath(path);
}

void DrawnModuleRectangle::positionPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation, float position)
{
    plug->setOrientation(orientation);
    switch(orientation) {
    case DrawnPlug::top:
        plug->moveBy(position, 0.0f);
        break;
    case DrawnPlug::right:
        plug->moveBy(mWidth, position);
        break;
    case DrawnPlug::bottom:
        plug->moveBy(position, mHeight);
        break;
    case DrawnPlug::left:
        plug->moveBy(0.0f, position);
        break;
    }
}

DrawnInput *DrawnModuleRectangle::newInput(std::string name, DrawnPlug::Orientation orientation, float position)
{
    DrawnInput *input = DrawnModule::newInput(name);
    positionPlug(input, orientation, position);
    return input;
}

DrawnOutput *DrawnModuleRectangle::newOutput(std::string name, DrawnPlug::Orientation orientation, float position)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    positionPlug(output, orientation, position);
    return output;
}
