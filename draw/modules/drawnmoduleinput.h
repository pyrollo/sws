#ifndef DRAWNMODULEINPUT_H
#define DRAWNMODULEINPUT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleInput : public DrawnModuleRectangle
{
public:
    DrawnModuleInput(DrawnSchema *parentSchema, CoreModule *coreModule);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAWNMODULEINPUT_H
