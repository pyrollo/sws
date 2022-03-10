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

#include "drawnmoduleoutput.h"
#include "draw/drawnschema.h"
#include "draw/style.h"

#include "core/modules/coremoduleoutput.h"
#include "core/coreschema.h"

#include <QPainter>
#include <QInputDialog>


DrawnModuleOutput::DrawnModuleOutput(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 4.0f, 2.0f), mName("")
{
    newInput("value", DrawnPlug::left, 1.0f);
}

DrawnModuleOutput::~DrawnModuleOutput()
{
    if (core() && mSchema) {
        mSchema->core()->setOutputName(core(), "");
        mSchema->notifyOutputsChanged();
    }
}

void DrawnModuleOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    setStyle(painter);

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(mWidth, 0.0f);
    path.arcTo(mWidth - (mHeight - 0.8f) * 0.5f, 0.4f, mHeight - 0.8f, mHeight - 0.8f, 90, 180);
    path.lineTo(mWidth, mHeight);
    path.lineTo(0.0f, mHeight);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);

    painter->setFont(Style::fModule());
    QRectF textRect(1.0f, 1.0f, 31.0f, 18.0f);

    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, mCoreModule?mName:"Output");
}

// TODO : Factorize DrawnModuleInput and DrawnModuleOutput
void DrawnModuleOutput::setName(QString name) {
    if (name == mName)
        return;

    mName = name;
    mSchema->core()->setOutputName(core(), mName.toStdString());
    schema()->notifyOutputsChanged();
    update();
}

void DrawnModuleOutput::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!mCoreModule) {
        DrawnModuleRectangle::mouseDoubleClickEvent(event);
        return;
    }

    bool ok;
    QString name = QInputDialog::getText(nullptr, "Output module", "Exported name:",
            QLineEdit::Normal, mName, &ok);
    if (ok)
        setName(name);
}
