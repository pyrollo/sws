/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2022 Pierre-Yves Rollo <dev@pyrollo.com>

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

#include "drawninteractive.h"
#include "drawnschema.h"

#include <QGraphicsSceneMouseEvent>

DrawnInteractive::DrawnInteractive(DrawnSchema *schema):
    QGraphicsObject(schema), mSchema(schema)
{
}

void DrawnInteractive::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseDoubleClickEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseDoubleClickEvent(event);
}

void DrawnInteractive::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mousePressEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mousePressEvent(event);
}

void DrawnInteractive::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseMoveEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseMoveEvent(event);
}

void DrawnInteractive::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        mSchema->mouseReleaseEvent(event, this);

    if (!event->isAccepted())
        QGraphicsItem::mouseReleaseEvent(event);
}
