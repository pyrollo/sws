#ifndef DRAWNPLUG_H
#define DRAWNPLUG_H
#include "drawnitem.h"
#include <unordered_set>

class DrawnWire;
class DrawnModule;

class DrawnPlug : public DrawnItem
{
public:
    DrawnPlug(DrawnModule *parentModule);
    ~DrawnPlug();

    DrawnModule *module() { return mModule; }

    virtual bool pluggable() = 0;
    bool connected();

    QRectF boundingRect() const;
    QPointF connectionPoint() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void setHighlighted(bool highlighted);

    void addConnectedWire(DrawnWire *wire);
    void removeConnectedWire(DrawnWire *wire);

protected:
    const float plugSize = 0.3f;

    DrawnModule *mModule;
    DrawnWire *mWire;
    bool mHighlighted;
    std::unordered_set<DrawnWire *>mConnectedWires;

    void setPenAndBrush(QPainter *painter);
};

#endif // DRAWNPLUG_H
