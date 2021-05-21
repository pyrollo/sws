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

GuiSchemaView::GuiSchemaView(QWidget *parent = nullptr):
    QGraphicsView(parent), mSchemaScene(nullptr)
{
    scale(10.0, 10.0);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setAcceptDrops(true);
}

void GuiSchemaView::setScene(GuiSchemaScene *scene)
{
    mSchemaScene = scene;
    QGraphicsView::setScene(scene);
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

void GuiSchemaView::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("sws/moduletype"))
        event->acceptProposedAction();
}

void GuiSchemaView::dragMoveEvent(QDragMoveEvent *event)
{
    (void)(event);
}

void GuiSchemaView::dropEvent(QDropEvent *event)
{
    std::string moduletype = event->mimeData()->data("sws/moduletype").toStdString();
    QPointF pos = mapToScene(event->pos());
    DrawnModule *module = mSchemaScene->schema()->newModule(moduletype);
    module->moveBy(pos.x(), pos.y());
    event->acceptProposedAction();
}

// QGraphicsScene::itemsBoundingRect
