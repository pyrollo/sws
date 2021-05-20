#ifndef DRAWNINPUT_H
#define DRAWNINPUT_H
#include "drawnplug.h"

class DrawnModule;
class DrawnOutput;
class DrawnWire;
class CoreInput;

class DrawnInput : public DrawnPlug
{
public:
    DrawnInput(DrawnModule *parent, CoreInput *coreInput = nullptr);

    CoreInput *core() { return mCoreInput; }

    bool pluggable() { return !connected(); }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

protected:
    CoreInput *mCoreInput;
};

#endif // DRAWNINPUT_H
