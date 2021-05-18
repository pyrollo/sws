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
    ~DrawnWire();

    DrawnSchema *schema() { return mSchema; }

    QRectF boundingRect() const { return mBoundingRect; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void connectTo(DrawnOutput *output);
    void connectTo(DrawnInput *input);
    void connectTo(DrawnPlug *plug);

    void drag(QPointF scenePoint);
    void endDrag();
    bool isValid() { return mConnectedOutput && mConnectedInput; }

    Q_SLOT void endpointsmoved();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QPainterPath shape() const;

protected:
    DrawnSchema *mSchema;

    QRectF mBoundingRect;

    bool mDragging;
    QPointF mDragpoint;

    QPointF mFrom, mTo;

    DrawnOutput *mConnectedOutput;
    DrawnInput *mConnectedInput;

    void updateBoundingRect();
    QPainterPath path() const;
};

#endif // DRAWNWIRE_H
