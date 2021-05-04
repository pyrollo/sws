#ifndef DRAWNWIRE_H
#define DRAWNWIRE_H
#include "drawnitem.h"
#include "drawnschema.h"

class DrawnOutput;
class DrawnInput;
class DrawnPlug;

class DrawnWire : public DrawnItem
{
    Q_OBJECT
public:
    DrawnWire(DrawnSchema *parentSchema);

    DrawnSchema *schema() { return mSchema; }

    QRectF boundingRect() const { return storedBoundingRect; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void connectTo(DrawnOutput *output);
    void connectTo(DrawnInput *input);
    void connectTo(DrawnPlug *plug);

    void drag(QPointF scenePoint);
    void endDrag();
    bool isValid() { return connectedOutput && connectedInput; }

    Q_SLOT void endpointsmoved();

protected:
    DrawnSchema *mSchema;

    void updateBoundingRect();
    QRectF storedBoundingRect;

    bool dragging;
    QPointF dragpoint;

    QPointF from, to;

    DrawnOutput *connectedOutput;
    DrawnInput *connectedInput;
};

#endif // DRAWNWIRE_H
