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

#include "drawnitem.h"
#include "drawnschema.h"
#include "../gui/guischemascene.h"
#include <QApplication>
#include <QGraphicsSceneMouseEvent>
#include <cmath>

DrawnItem::DrawnItem(DrawnItem *parent, float posGridSize):
    QObject(), QGraphicsItem(parent), mSchema(parent?parent->schema():nullptr),
    mIsHovered(false), mPosGridSize(posGridSize), mPosGridAnchor(0.0f, 0.0f)
{
    if (mPosGridSize > 0.0f)
        setFlags(flags() | QGraphicsItem::ItemSendsGeometryChanges);
}

QVariant DrawnItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
        emit positionChanged();

    if (change == ItemPositionChange && mPosGridSize > 0.0f) {
        QPointF newPos = value.toPointF() + mPosGridAnchor;
        qreal xV = round(newPos.x()/mPosGridSize)*mPosGridSize;
        qreal yV = round(newPos.y()/mPosGridSize)*mPosGridSize;
        return QPointF(xV, yV) - mPosGridAnchor;
    }

    return QGraphicsItem::itemChange(change, value);
}

void DrawnItem::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = true;
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnItem::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;
    QGraphicsItem::hoverLeaveEvent(event);
}

void DrawnItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseDoubleClickEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseDoubleClickEvent(event);
}

void DrawnItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mousePressEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mousePressEvent(event);
}

void DrawnItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseMoveEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseMoveEvent(event);
}

void DrawnItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseReleaseEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseReleaseEvent(event);
}

void DrawnItem::deleteAll()
{
    delete this;
}

void DrawnItem::deleteSelected()
{
    for (auto qitem: childItems()) {
        DrawnItem *item = dynamic_cast<DrawnItem *>(qitem);
        if (!item)
            continue;

        if (item->isSelected())
            item->deleteAll();
        else
            item->deleteSelected();
    }
}
