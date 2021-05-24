#include "drawnmodulemultiply.h"
#include <QPainter>

DrawnModuleMultiply::DrawnModuleMultiply(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 2.0f, 2.0f)
{
    newInput("operand1", DrawnPlug::left, 0.5f);
    newInput("operand2", DrawnPlug::left, 1.5f);
    newOutput("result", DrawnPlug::right, 1.0f);
}

void DrawnModuleMultiply::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(0.7f, 0.7f);
    path.lineTo(1.3f, 1.3f);
    path.moveTo(1.3f, 0.7f);
    path.lineTo(0.7f, 1.3f);
    painter->drawPath(path);
}
