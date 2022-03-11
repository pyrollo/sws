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
#include "style.h"

#include <QPainter>
#include <QSvgRenderer>

DrawnModuleRectangle::DrawnModuleRectangle(std::string type, DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModule(type, parentSchema, coreModule), mWidth(2.0f), mHeight(2.0f)
{
    float margin = Style::wModule() * 0.5f;
    mPosGridAnchor = QPointF(margin, margin);
}

QRectF DrawnModuleRectangle::boundingRect() const
{
    float margin = Style::wModule();
    return QRectF(-margin * 0.5f, -margin * 0.5f, mWidth + margin, mHeight + margin);
}

void DrawnModuleRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    QPainterPath path;
    path.addRoundedRect(0.0f, 0.0f, mWidth, mHeight, 0.1f, 0.1f);
    painter->drawPath(path);
}

void DrawnModuleRectangle::repositionPlugs(DrawnPlug::Orientation orientation)
{
    int plugsNb = mPlugs[orientation].size();
    if (!plugsNb)
        return;

    bool horizontal = orientation == DrawnPlug::top || orientation == DrawnPlug::bottom;
    float totalSize = horizontal?mWidth:mHeight;
    float offset = 0.5f * (totalSize - plugsNb * 1.0f + 1.0f);

    switch(orientation) {
    case DrawnPlug::top:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(offset + index * 1.0f, 0.0f);
        break;
    case DrawnPlug::right:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(mWidth, offset + index * 1.0f);
        break;
    case DrawnPlug::bottom:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(offset + index * 1.0f, mHeight);
        break;
    case DrawnPlug::left:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(0.0f, offset + index * 1.0f);
        break;
    }
}

void DrawnModuleRectangle::addPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation)
{
    plug->setOrientation(orientation);
    mPlugs[orientation].push_back(plug);
    float minSize = mPlugs[orientation].size() * 1.0f;

    if (orientation == DrawnPlug::top || orientation == DrawnPlug::bottom) {
        if (mWidth < minSize) {
            mWidth = minSize;
            repositionPlugs(DrawnPlug::top);
            repositionPlugs(DrawnPlug::bottom);
            repositionIcon();
        } else {
            repositionPlugs(orientation);
        }
    }

    if (orientation == DrawnPlug::left || orientation == DrawnPlug::right) {
        if (mHeight < minSize) {
            mHeight = minSize;
            repositionPlugs(DrawnPlug::left);
            repositionPlugs(DrawnPlug::right);
        } else {
            repositionPlugs(orientation);
        }
    }
    update();
}

void DrawnModuleRectangle::newInput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnInput *input = DrawnModule::newInput(name);
    addPlug(input, orientation);
}

void DrawnModuleRectangle::newOutput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    addPlug(output, orientation);
}
