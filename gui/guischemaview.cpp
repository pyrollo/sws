#include "guischemaview.h"
#include <QWheelEvent>
#include <QEvent>
#include <QScrollBar>
#include <cmath>
#include <iostream>

GuiSchemaView::GuiSchemaView(QWidget *parent = nullptr):
    QGraphicsView(parent)
{
    scale(10.0, 10.0);
    setDragMode(QGraphicsView::ScrollHandDrag);
}

void GuiSchemaView::wheelEvent(QWheelEvent* event)
{
    const qreal minzoom = 1;
    const qreal maxzoom = 300.0;

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

// QGraphicsScene::itemsBoundingRect
