#include "drawnmodulesinus.h"
#include <QPainter>

DrawnModuleSinus::DrawnModuleSinus(DrawnSchema *schema, CoreModule *coreModule):
    DrawnModuleRectangle(schema, coreModule, 2.0f, 2.0f)
{
    newInput("operand", DrawnPlug::left, 1.0f);
    newOutput("result", DrawnPlug::right, 1.0f);
}

void DrawnModuleSinus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);

    QPainterPath path;
    path.moveTo(0.5f, 1.0f);
    path.cubicTo(0.6f, 1.5f, 0.9f, 1.5f, 1.0f, 1.0f);
    path.cubicTo(1.1f, 0.5f, 1.4f, 0.5f, 1.5f, 1.0f);
    path.lineTo(1.5f, 1.0f);
    painter->drawPath(path);
}
