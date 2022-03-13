/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "drawnmoduleconstant.h"
#include "draw/style.h"

#include "core/coremodule.h"

#include <QPainter>
#include <QInputDialog>
#include <QTextStream>
#include "value/string.h"

DrawnModuleConstant::DrawnModuleConstant(DrawnSchema *parentSchema):
    DrawnModuleRectangle("constant", parentSchema)
{
    mWidth = 4;
    mHeight = 1;
    newOutput("value", DrawnPlug::right);
}

void DrawnModuleConstant::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRectangle::paint(painter, option, widget);
    painter->setFont(Style::fModule());
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
