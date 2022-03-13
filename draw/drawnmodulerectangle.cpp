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
#include "drawninput.h"
#include "drawnoutput.h"
#include "style.h"

#include <QPainter>
#include <QSvgRenderer>

DrawnModuleRectangle::DrawnModuleRectangle(std::string type, DrawnSchema *schema):
    DrawnModule(type, schema), mWidth(2), mHeight(2)
{}

QRectF DrawnModuleRectangle::baseRect() const
{
    return QRectF(0.0f, 0.0f, Style::sGrid() * mWidth, Style::sGrid() * mHeight);
}

QRectF DrawnModuleRectangle::boundingRect() const
{
    float margin = Style::wModule();
    return baseRect().marginsAdded(QMarginsF(margin, margin, margin, margin));
}

void DrawnModuleRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    QPainterPath path;
    path.addRoundedRect(0.0f, 0.0f, Style::sGrid() * mWidth, Style::sGrid() * mHeight, 0.1f, 0.1f);
    painter->drawPath(path);
}

void DrawnModuleRectangle::repositionPlugs(DrawnPlug::Orientation orientation)
{
    int plugsNb = mPlugs[orientation].size();
    if (!plugsNb)
        return;

    bool horizontal = orientation == DrawnPlug::top || orientation == DrawnPlug::bottom;
    float totalSize = Style::sGrid() * (horizontal?mWidth:mHeight);
    float offset = 0.5f * (totalSize - plugsNb * Style::sGrid() + Style::sGrid());

    switch(orientation) {
    case DrawnPlug::top:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(offset + Style::sGrid() * index, 0.0f);
        break;
    case DrawnPlug::right:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(Style::sGrid() * mWidth, offset + Style::sGrid() * index);
        break;
    case DrawnPlug::bottom:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(offset + Style::sGrid() * index, Style::sGrid() * mHeight);
        break;
    case DrawnPlug::left:
        for (int index = 0; index < plugsNb; ++index)
            mPlugs[orientation][index]->setPos(0.0f, offset + Style::sGrid() * index);
        break;
    }
}

void DrawnModuleRectangle::addPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation)
{
    plug->setOrientation(orientation);
    mPlugs[orientation].push_back(plug);
    int minSize = mPlugs[orientation].size();

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

DrawnInput* DrawnModuleRectangle::newInput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnInput *input = DrawnModule::newInput(name);
    addPlug(input, orientation);
    return input;
}

DrawnOutput* DrawnModuleRectangle::newOutput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    addPlug(output, orientation);
    return output;
}
