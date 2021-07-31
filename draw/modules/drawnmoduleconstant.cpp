#include "drawnmoduleconstant.h"
#include "gui/guistyle.h"
#include "core/coremodule.h"
#include <QPainter>
#include <QInputDialog>
#include <QTextStream>
#include "value/string.h"

DrawnModuleConstant::DrawnModuleConstant(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 4.0f, 1.0f)
{
    newOutput("value", DrawnPlug::right, 0.5f);
}

void DrawnModuleConstant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);
    painter->setFont(GuiStyle::fModule());
    QRectF textRect(1.0f, 1.0f, 35.0f, 8.0f);

    QString value;
    if (mCoreModule)
        QTextStream(&value) << QString::fromStdString(core()->output("value")->value().toString());
    else
        value = "Constant";

    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, value);
}

void DrawnModuleConstant::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!mCoreModule) {
        DrawnModuleRectangle::mouseDoubleClickEvent(event);
        return;
    }

    bool ok;
    QString text = QInputDialog::getText(nullptr, "Constant module",
        "Value:", QLineEdit::Normal,
        QString::fromStdString(core()->output("value")->value().toString()), &ok);

    if (ok) {
        core()->output("value")->setValue(valueFromQString(text));
        update();
    }
}
