#ifndef CONNECTWIREINTERACTION_H
#define CONNECTWIREINTERACTION_H
#include "draw/drawnschemainteraction.h"
class DrawnPlug;
class DrawnWire;

class ConnectWireInteraction : public DrawnSchemaInteraction
{
public:
    ConnectWireInteraction(DrawnSchema *schema, DrawnPlug *plug);
    ~ConnectWireInteraction() {}
    void mouseMoveEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) override;
protected:
    DrawnPlug *mPlug;
    DrawnWire *mWire;
};

#endif // CONNECTWIREINTERACTION_H
