#include "drawnmoduleclip.h"
#include <QPainter>

DrawnModuleClip::DrawnModuleClip(DrawnSchema *schema, CoreModule *coreModule):
    DrawnModuleRectangle(schema, coreModule, 2.0f, 2.0f)
{
    newInput("operand", left, 1.0f);
    newOutput("result", right, 1.0f);
}

void DrawnModuleClip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(0.5f, 1.5f);
    path.lineTo(1.5f, 0.5f);
    path.lineTo(1.5f, 1.5f);
    painter->drawPath(path);
}
