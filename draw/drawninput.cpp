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

#include "drawninput.h"
#include "core/coreinput.h"
#include "gui/guischemascene.h"
#include <QPainter>

DrawnInput::DrawnInput(DrawnModule *parent, CoreInput *coreInput) :
    DrawnPlug(parent, coreInput), mCoreInput(coreInput)
{}

void DrawnInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    static const QPointF points[3] = {
        QPointF(0.0, -plugSize),
        QPointF(plugSize, 0.0),
        QPointF(0.0, plugSize)
    };

    painter->drawPolygon(points, 3);
}

void DrawnInput::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = true;

    if (mCoreInput) {
//        GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
//        if (schemaScene)
//            schemaScene->setProbe(QString("input"), mCoreInput->value());
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnInput::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;

    if (mCoreInput) {
//        GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
//        if (schemaScene)
//            schemaScene->clearProbe();
    }

    QGraphicsItem::hoverLeaveEvent(event);
}
