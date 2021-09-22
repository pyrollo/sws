#include "defaultinteraction.h"
#include "connectwireinteraction.h"
#include "draw/drawnschema.h"
#include "draw/drawnplug.h"
#include <QGraphicsSceneMouseEvent>

DefaultInteraction::DefaultInteraction(DrawnSchema *schema):
    DrawnSchemaInteraction(schema)
{}

void DefaultInteraction::mousePressEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item)
{
    DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);

    if (plug && plug->pluggable()) {
        ConnectWireInteraction *interaction = new ConnectWireInteraction(mSchema, plug);
        mSchema->startInteraction(interaction);
    }
    e->accept();
}



