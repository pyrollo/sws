#include "drawninput.h"
#include "../gui/guistyle.h"
#include "../core/coreinput.h"
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

