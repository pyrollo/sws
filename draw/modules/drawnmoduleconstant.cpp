#include "drawnmoduleconstant.h"
#include "gui/guistyle.h"
#include "core/coremodule.h"
#include <QPainter>
#include <QInputDialog>
#include <QTextStream>

DrawnModuleConstant::DrawnModuleConstant(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 4.0f, 1.0f)
{
    newOutput("value", right, 0.5f);
}

void DrawnModuleConstant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);
    painter->setFont(GuiStyle::fModule());
    QRectF textRect(1.0f, 1.0f, 35.0f, 8.0f);

    QString value;
    QTextStream(&value) << core()->output("value")->value();
    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, value);
}

void DrawnModuleConstant::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    bool ok;
    double value = QInputDialog::getDouble(nullptr, "Constant module",
            "Value:", core()->output("value")->value(), -2147483647, 2147483647, 6, &ok);
    if (ok) {
        core()->output("value")->setValue(value);
        update();
    }
}
