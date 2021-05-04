#ifndef DRAWNPLUG_H
#define DRAWNPLUG_H
#include "drawnitem.h"

class DrawnWire;
class DrawnModule;

class DrawnPlug : public DrawnItem
{
public:
    DrawnPlug(DrawnModule *parentModule);

    DrawnModule *module() { return mModule; }

    virtual bool pluggable() = 0;
    virtual bool connected() = 0;

    QRectF boundingRect() const;
    QPointF connectionPoint() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    void setHighlighted(bool highlighted);
protected:
    const float plugSize = 0.3f;

    DrawnModule *mModule;
    DrawnWire *mWire;
    bool mHighlighted;

    void setPenAndBrush(QPainter *painter);
};

#endif // DRAWNPLUG_H
