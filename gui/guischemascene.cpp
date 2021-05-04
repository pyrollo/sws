#include "guischemascene.h"
#include <QPainter>

void GuiSchemaScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QPen pen2(Qt::red, 0.3);
    painter->setPen(pen2);
    painter->drawRect(sceneRect());

    QRectF visible = rect.intersected(sceneRect());

    painter->fillRect(visible, Qt::darkGray);

    int gridSize =  getGridSize();

    QPen pen(Qt::lightGray, 0.1);
    painter->setPen(pen);

    qreal left = int(visible.left()) - (int(visible.left()) % gridSize);
    qreal top = int(visible.top()) - (int(visible.top()) % gridSize);

    QVector<QPointF> points;

    for (qreal x = left; x < visible.right(); x += gridSize){
        for (qreal y = top; y < visible.bottom(); y += gridSize){
            points.append(QPointF(x,y));
        }
    }
    painter->drawPoints(points.data(), points.size());
}
