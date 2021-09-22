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

void ConnectWireInteraction::mouseMoveEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item)
{
    (void)(item);
    mWire->drag(e->scenePos());
    e->accept();
}

void ConnectWireInteraction::mouseReleaseEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item)
{
    (void)(item);

    auto items = mSchema->scene()->items(e->scenePos());
    for (auto item: items) {
        DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);
        if (plug) {
            try {
                mWire->connectTo(plug);
                break;
            } catch(CoreException &e) {
                QMessageBox msgBox;
                msgBox.setText(e.what());
                msgBox.exec();
            }
        }
    }
    mWire->endDrag();
    if (!mWire->isValid())
        delete mWire;
    mSchema->unHighlight();
    mSchema->endInteraction();
    e->accept();
}
