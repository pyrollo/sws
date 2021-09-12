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

#include "drawnoutput.h"
#include "core/coreoutput.h"
#include "gui/guischemascene.h"
#include <QPainter>

DrawnOutput::DrawnOutput(DrawnModule *parent, CoreOutput *coreOutput) :
    DrawnPlug(parent), mCoreOutput(coreOutput)
{}

void DrawnOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    painter->drawChord(QRectF(-plugSize, -plugSize, plugSize*2, plugSize*2), -90*16, 180*16);
}

void DrawnOutput::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = true;

    if (mCoreOutput) {
        GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
        if (schemaScene)
            schemaScene->setProbe(QString("output"), mCoreOutput->value());
    }

    QGraphicsItem::hoverEnterEvent(event);
}

void DrawnOutput::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    mIsHovered = false;

    if (mCoreOutput) {
        GuiSchemaScene *schemaScene = dynamic_cast<GuiSchemaScene *>(scene());
        if (schemaScene)
            schemaScene->clearProbe();
    }

    QGraphicsItem::hoverLeaveEvent(event);
}
