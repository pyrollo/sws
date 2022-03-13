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

#include "connectwireinteraction.h"
#include "QGraphicsSceneMouseEvent"
#include "QGraphicsScene"
#include "QMessageBox"
#include "draw/drawnplug.h"
#include "draw/drawnschema.h"
#include "draw/drawnwire.h"
#include "core/coreexceptions.h"

ConnectWireInteraction::ConnectWireInteraction(DrawnSchema *schema, DrawnPlug *plug):
    DrawnSchemaInteraction(schema), mPlug(plug)
{
    mWire = new DrawnWire(mSchema);
    mWire->connectTo(plug);
    mSchema->highlightConnectable(plug);
}

void ConnectWireInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *)
{
    mWire->drag(event->scenePos());
    event->accept();
}

void ConnectWireInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *)
{
    auto items = mSchema->scene()->items(event->scenePos());
    for (auto item: items) {
        DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);
        if (plug) {
            try {
                mWire->connectTo(plug);
                break;
            } catch(CoreException &except) {
                QMessageBox msgBox;
                msgBox.setText(except.what());
                msgBox.exec();
            }
        }
    }
    mWire->endDrag();
    if (!mWire->isValid())
        delete mWire;
    mSchema->unHighlight();
    mSchema->endInteraction();
    event->accept();
}
