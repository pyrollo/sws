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

#include "guischemaview.h"
#include "guischemascene.h"
#include "draw/drawnschema.h"
#include "draw/drawnmodule.h"
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <cmath>
#include <iostream>
#include <QMimeData>

GuiSchemaView::GuiSchemaView(QWidget *parent):
    QGraphicsView(parent), mScene()
{
    setDragMode(QGraphicsView::ScrollHandDrag);
    setAcceptDrops(true);
    setScene(&mScene);
}

void GuiSchemaView::setSchema(DrawnSchema *schema)
{
    mScene.setSchema(schema);
    emit schemaChanged();
}

DrawnSchema *GuiSchemaView::schema()
{
    return mScene.schema();
}

void GuiSchemaView::wheelEvent(QWheelEvent* event)
{
    const qreal minzoom = 3; //1.0f;
    const qreal maxzoom = 30; //300.0f;

    const QPointF p0scene = mapToScene(event->pos());

    qreal zoom = transform().m11(); // Wont work if rotated
    qreal factor = std::pow(1.005, event->delta());

    if (zoom*factor < minzoom)
        factor = minzoom/zoom;

    if (zoom*factor > maxzoom)
        factor = maxzoom/zoom;

    scale(factor, factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos(); // The move
    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
}

void GuiSchemaView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("sws/itemtype"))
        event->acceptProposedAction();
}

void GuiSchemaView::dragMoveEvent(QDragMoveEvent *event)
{
    (void)(event);
}

void GuiSchemaView::dropEvent(QDropEvent *event)
{
    std::string type = event->mimeData()->data("sws/itemtype").toStdString();
    QPointF pos = mapToScene(event->pos());
    DrawnItem *item = mScene.schema()->newItem(type);
    item->moveBy(pos.x(), pos.y());
    event->acceptProposedAction();
}

