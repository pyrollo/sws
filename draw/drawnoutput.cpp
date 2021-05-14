#include "drawnoutput.h"
#include "../core/coreoutput.h"
#include <QPainter>

DrawnOutput::DrawnOutput(DrawnModule *parent, CoreOutput *coreOutput) :
    DrawnPlug(parent), mCoreOutput(coreOutput)
{
}

void DrawnOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    painter->drawChord(QRectF(-plugSize, -plugSize, plugSize*2, plugSize*2), -90*16, 180*16);
}

