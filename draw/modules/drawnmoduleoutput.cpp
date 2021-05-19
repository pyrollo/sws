#include "drawnmoduleoutput.h"
#include <QPainter>

DrawnModuleOutput::DrawnModuleOutput(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 2.0f, 2.0f)
{
    newInput("value", left, 1.0f);
}

void DrawnModuleOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(mWidth, 0.0f);
    path.arcTo(mWidth/2 + 0.4f, 0.4f, mWidth - 0.8f, mHeight - 0.8f, 90, 180);
    path.lineTo(mWidth, mHeight);
    path.lineTo(0.0f, mHeight);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);
}
