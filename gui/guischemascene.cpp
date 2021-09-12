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

#include "guischemascene.h"
#include "guistyle.h"
#include "draw/drawnschema.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QTextStream>

GuiSchemaScene::GuiSchemaScene(QObject *parent):
    QGraphicsScene(-10, -10, 20, 20, parent), mSchema(nullptr), mProbeWidget(nullptr)
{
    setBackgroundBrush(GuiStyle::bBackground());
}

void GuiSchemaScene::keyPressEvent(QKeyEvent *event)
{
    if (!mSchema)
        return;

    if (event->key() == Qt::Key_Delete)
        mSchema->deleteSelected();
}

void GuiSchemaScene::setSchema(DrawnSchema *schema)
{
    if (schema == mSchema)
        return;

    if (mSchema)
        removeItem(mSchema);

    mSchema = schema;
    if (mSchema)
        addItem(mSchema);

    update();
}

void GuiSchemaScene::setProbeWidget(QLabel *widget)
{
    mProbeWidget = widget;
    clearProbe();
}

void GuiSchemaScene::setProbe(QString label, Value value)
{
    if (!mProbeWidget)
        return;

    QString text;
    QTextStream(&text) << label << ": " << QString::fromStdString(value.toString());
    mProbeWidget->setText(text);
}

void GuiSchemaScene::clearProbe()
{
    if (!mProbeWidget)
        return;

    mProbeWidget->setText("");
}
