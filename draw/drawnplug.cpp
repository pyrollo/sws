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

#include "drawnplug.h"
#include "drawnwire.h"
#include "drawnmodule.h"
#include "gui/guistyle.h"
#include "core/coreexceptions.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMessageBox>

DrawnPlug::DrawnPlug(DrawnModule *parentModule) :
    DrawnItem(parentModule), mModule(parentModule),
    mOrientation(top), mHighlighted(false), mConnecting(false)
{
    setFlags(flags()|ItemIsSelectable|ItemSendsGeometryChanges);
    if (mModule->schema())
        setAcceptHoverEvents(true);
}

DrawnPlug::~DrawnPlug()
{
    while (!mConnectedWires.empty())
        delete *(mConnectedWires.begin()); // Should be better with something like "disconnect"
}

QRectF DrawnPlug::boundingRect() const
{
    float margin = GuiStyle::pPlug().width();
    return QRectF(-margin, -margin - plugSize, margin + plugSize, plugSize * 2 + margin);
}

void DrawnPlug::setOrientation(Orientation orientation)
{
    setRotation(angleFromOrientation(orientation));
    mOrientation = orientation;
}

void DrawnPlug::setHighlighted(bool highlighted)
{
    if (highlighted == mHighlighted)
        return;
    mHighlighted = highlighted;
    update();
}

void DrawnPlug::setConnecting(bool connecting)
{
    if (connecting != mConnecting)
        return;
    mConnecting = connecting;
    update();
}

void DrawnPlug::setPenAndBrush(QPainter *painter)
{
    if (module()->isSelected()) {
        painter->setPen(GuiStyle::pPlugSelected());
        painter->setBrush(GuiStyle::bPlugSelected());
    } else {
        painter->setPen(GuiStyle::pPlug());
        painter->setBrush(GuiStyle::bPlug());
    }

    if (connected())
        painter->setBrush(GuiStyle::bPlugConnected());

    if (mConnecting)
        painter->setBrush(GuiStyle::bPlugConnecting());

    if (mHighlighted)
        painter->setPen(GuiStyle::pPlugConnectable());

    for (auto wire: mConnectedWires)
        if (wire->isSelected()) {
            painter->setBrush(GuiStyle::bWireSelected());
            break;
        }
}

void DrawnPlug::addConnectedWire(DrawnWire *wire)
{
    mConnectedWires.insert(wire);
    update();
}

void DrawnPlug::removeConnectedWire(DrawnWire *wire)
{
    mConnectedWires.erase(wire);
    update();
}

bool DrawnPlug::connected()
{
    return !mConnectedWires.empty();
}

bool DrawnPlug::hasSameOrientation(DrawnPlug *plug)
{
    return plug->mOrientation == mOrientation;
}

bool DrawnPlug::hasOppositeOrientation(DrawnPlug *plug)
{
    return plug->mOrientation == oppositeOrientation(mOrientation);
}

DrawnPlug::Orientation DrawnPlug::oppositeOrientation(Orientation orientation) {
    return (DrawnPlug::Orientation)((orientation + 2)%4);
}

int DrawnPlug::angleFromOrientation(Orientation orientation)
{
    return orientation * 90;
}

DrawnPlug::Orientation DrawnPlug::rotateOrientation(Orientation orientation, Orientation by)
{
    return (DrawnPlug::Orientation)((orientation + by)%4);
}

void DrawnPlug::rotatePoint(QPointF &point, Orientation by)
{
    float y;
    switch(by) {
    case right:
        return;
    case bottom:
        y = point.y();
        point.setY(-point.x());
        point.setX(y);
        return;
    case left:
        point.setX(-point.x());
        point.setY(-point.y());
        return;
    case top:
        y = point.y();
        point.setY(point.x());
        point.setX(- y);
        return;
    }
}

void DrawnPlug::unrotatePoint(QPointF &point, Orientation by)
{
    float y;
    switch(by) {
    case right:
        return;
    case bottom:
        y = point.y();
        point.setY(point.x());
        point.setX(-y);
        return;
    case left:
        point.setX(-point.x());
        point.setY(-point.y());
        return;
    case top:
        y = point.y();
        point.setY(-point.x());
        point.setX(y);
        return;
    }
}

