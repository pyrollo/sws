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
#include "drawnicon.h"
#include "style.h"

#include "gui/guischemascene.h"

#include <cmath>
#include <QApplication>
#include <QGraphicsSceneMouseEvent>

DrawnItem::DrawnItem(std::string type, DrawnSchema *schema):
    DrawnInteractive(schema), mType(type), mSchema(schema),
    mIcon(nullptr), mAlignToGrid(false)
{}

DrawnItem::~DrawnItem()
{
    if (mSchema)
        mSchema->removeItem(this);

    if (mIcon)
        delete mIcon;
}

QVariant DrawnItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange)
        emit positionChanged();

    if (change == ItemPositionChange && mAlignToGrid) {
        qreal gridSize = Style::sGrid();
        QPointF newPos = value.toPointF();
        qreal xV = round(newPos.x() / gridSize) * gridSize;
        qreal yV = round(newPos.y() / gridSize) * gridSize;
        return QPointF(xV, yV);
    }

    return QGraphicsItem::itemChange(change, value);
}

void DrawnItem::repositionIcon()
{
    if (!mIcon)
        return;
    QRectF rect = boundingRect();
    mIcon->setPos(rect.width() * 0.5 + rect.left(), rect.height() * 0.5 + rect.top());
    update();
}

void DrawnItem::setIcon(const QString &filename)
{
    if (mIcon)
        delete mIcon;

    mIcon = new DrawnIcon(this, filename);
    repositionIcon();
}

