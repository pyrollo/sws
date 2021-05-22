#ifndef DRAWNMODULEROUND_H
#define DRAWNMODULEROUND_H
#include "drawnmodule.h"

class DrawnModuleRound : public DrawnModule
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    DrawnModuleRound(DrawnSchema *parentSchema, CoreModule *coreModule);

    DrawnInput *newInput(std::string name, DrawnPlug::Orientation orientation);
    DrawnOutput *newOutput(std::string name, DrawnPlug::Orientation orientation);

    void positionPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation);

};

#endif // DRAWNMODULEROUND_H
