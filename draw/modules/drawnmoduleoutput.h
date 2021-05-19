#ifndef DRAWNMODULEOUTPUT_H
#define DRAWNMODULEOUTPUT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleOutput : public DrawnModuleRectangle
{
public:
    DrawnModuleOutput(DrawnSchema *parentSchema, CoreModule *coreModule);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAWNMODULEOUTPUT_H
