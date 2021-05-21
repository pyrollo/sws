#ifndef DRAWNMODULEROUND_H
#define DRAWNMODULEROUND_H
#include "drawnmodule.h"

class DrawnModuleRound : public DrawnModule
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    enum Side { top, right, bottom, left };

    DrawnModuleRound(DrawnSchema *parentSchema, CoreModule *coreModule);

    DrawnInput *newInput(std::string name, Side side);
    DrawnOutput *newOutput(std::string name, Side side);

    void positionPlug(DrawnItem *plug, Side side);

};

#endif // DRAWNMODULEROUND_H
