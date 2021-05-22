#ifndef DRAWNPLUG_H
#define DRAWNPLUG_H
#include "drawnitem.h"
#include <unordered_set>

class DrawnWire;
class DrawnModule;

class DrawnPlug : public DrawnItem
{
public:
    enum Orientation { left = 0, top, right, bottom };

    DrawnPlug(DrawnModule *parentModule);
    ~DrawnPlug();

    DrawnModule *module() { return mModule; }

    virtual bool pluggable() = 0;
    bool connected();

    QRectF boundingRect() const;
    QPointF connectionPoint() const;

    void setOrientation(Orientation orientation);
    Orientation getOrientation() { return mOrientation; }

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void setHighlighted(bool highlighted);

    void addConnectedWire(DrawnWire *wire);
    void removeConnectedWire(DrawnWire *wire);

    bool hasSameOrientation(DrawnPlug *plug);
    bool hasOppositeOrientation(DrawnPlug *plug);

    static Orientation oppositeOrientation(Orientation orientation);
    static int angleFromOrientation(Orientation orientation);
    static Orientation rotateOrientation(Orientation orientation, Orientation by);
    static void rotatePoint(QPointF &point, Orientation by);
    static void unrotatePoint(QPointF &point, Orientation by);

protected:
    const float plugSize = 0.3f;

    DrawnModule *mModule;
    Orientation mOrientation;
    DrawnWire *mWire;
    bool mHighlighted;
    std::unordered_set<DrawnWire *>mConnectedWires;

    void setPenAndBrush(QPainter *painter);
};



#endif // DRAWNPLUG_H
