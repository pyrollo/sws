#ifndef DRAWNMODULEMULTIPLY_H
#define DRAWNMODULEMULTIPLY_H
#include "../drawnmodulerectangle.h"

class DrawnModuleMultiply : public DrawnModuleRectangle
{
public:
    DrawnModuleMultiply(DrawnSchema *parentSchema, CoreModule *coreModule);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAWNMODULEMULTIPLY_H
