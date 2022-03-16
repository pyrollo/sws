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

#include "defaultinteraction.h"
#include "connectwireinteraction.h"
#include "draw/drawnschema.h"
#include "draw/drawnplug.h"
#include "draw/drawninteractive.h"

#include <QGraphicsSceneMouseEvent>

DefaultInteraction::DefaultInteraction(DrawnSchema *schema):
    DrawnSchemaInteraction(schema)
{}

void DefaultInteraction::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *emitter)
{
    DrawnPlug *plug = dynamic_cast<DrawnPlug *>(emitter);

    if (plug && plug->pluggable()) {
        ConnectWireInteraction *interaction = new ConnectWireInteraction(mSchema, plug);
        mSchema->startInteraction(interaction);
    }
    event->accept();
}



