#include "drawnmoduleinput.h"
#include <QPainter>

DrawnModuleInput::DrawnModuleInput(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 2.0f, 2.0f)
{
    newOutput("value", right, 1.0f);
}

void DrawnModuleInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(mWidth, 0.0f);
    path.lineTo(mWidth, mHeight);
    path.lineTo(0.0f, mHeight);
    path.lineTo(0.0f, mHeight - 0.4f);
    path.lineTo(mWidth/2 - 0.2f, mHeight/2);
    path.lineTo(0.0f, 0.4f);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);
}
