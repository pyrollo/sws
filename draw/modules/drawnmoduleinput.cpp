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

#include "drawnmoduleinput.h"
#include "draw/drawnschema.h"
#include "draw/style.h"

#include "core/modules/coremoduleinput.h"
#include "core/coreschema.h"

#include <QPainter>
#include <QInputDialog>

DrawnModuleInput::DrawnModuleInput(DrawnSchema *parentSchema):
    DrawnModuleRectangle("input", parentSchema), mName("")
{
    mWidth = 4;
    mHeight = 2;
    newOutput("value", DrawnPlug::right);
}

DrawnModuleInput::~DrawnModuleInput()
{
    if (mCoreModule && mSchema) {
            mSchema->core()->setInputName(core(), "");
            mSchema->notifyInputsChanged();
    }
}

void DrawnModuleInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    qreal width = Style::sGrid() * mWidth;
    qreal height = Style::sGrid() * mHeight;
    QPainterPath path;

    path.moveTo(0.0f, 0.0f);
    path.lineTo(width, 0.0f);
    path.lineTo(width, height);
    path.lineTo(0.0f, height);
    path.lineTo(0.0f, height - 0.4f);
    path.lineTo(height * 0.5f - 0.4f, height * 0.5f);
    path.lineTo(0.0f, 0.4f);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);

    painter->setFont(Style::fModule());
    QRectF textRect(8.0f, 1.0f, 31.0f, 18.0f);

    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, mCoreModule?mName:"Input");
}

// TODO : Factorize DrawnModuleInput and DrawnModuleOutput
void DrawnModuleInput::setName(QString name) {
    if (name == mName)
        return;

    mName = name;
    mSchema->core()->setInputName(core(), mName.toStdString());
    schema()->notifyInputsChanged();
    update();
}

void DrawnModuleInput::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!mCoreModule) {
        DrawnModuleRectangle::mouseDoubleClickEvent(event);
        return;
    }

    bool ok;
    QString name = QInputDialog::getText(nullptr, "Input module", "Exported name:",
            QLineEdit::Normal, mName, &ok);
    if (ok)
        setName(name);
}
