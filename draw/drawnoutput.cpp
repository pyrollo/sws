#include "drawnoutput.h"
#include "core/coreoutput.h"
#include "gui/guischemascene.h"
#include <QPainter>

DrawnOutput::DrawnOutput(DrawnModule *parent, CoreOutput *coreOutput) :
    DrawnPlug(parent), mCoreOutput(coreOutput)
{}

void DrawnOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    painter->drawChord(QRectF(-plugSize, -plugSize, plugSize*2, plugSize*2), -90*16, 180*16);
}

void DrawnOutput::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = true;
    GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
    if (schemaScene)
        schemaScene->setProbe(QString("output"), core()->value());
    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnOutput::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;
    GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
    if (schemaScene)
        schemaScene->clearProbe();
    QGraphicsItem::hoverLeaveEvent(event);
}
