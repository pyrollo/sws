#include "drawninput.h"
#include "core/coreinput.h"
#include "gui/guischemascene.h"
#include <QPainter>

DrawnInput::DrawnInput(DrawnModule *parent, CoreInput *coreInput) :
    DrawnPlug(parent), mCoreInput(coreInput)
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
    GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
    if (schemaScene)
        schemaScene->setProbe(QString("input"), core()->value());
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnInput::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;
    GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
    if (schemaScene)
        schemaScene->clearProbe();
    QGraphicsItem::hoverLeaveEvent(event);
}
