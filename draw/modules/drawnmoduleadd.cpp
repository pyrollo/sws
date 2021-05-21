#include "drawnmoduleadd.h"
#include <QPainter>

DrawnModuleAdd::DrawnModuleAdd(DrawnSchema *schema, CoreModule *coreModule):
    DrawnModuleRectangle(schema, coreModule, 2.0f, 2.0f)
{
    newInput("operand1", left, 0.5f);
    newInput("operand2", left, 1.5f);
    newOutput("result", right, 1.0f);
}

void DrawnModuleAdd::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(1.0f, 0.6f);
    path.lineTo(1.0f, 1.4f);
    path.moveTo(0.6f, 1.0f);
    path.lineTo(1.4f, 1.0f);
    painter->drawPath(path);
}
