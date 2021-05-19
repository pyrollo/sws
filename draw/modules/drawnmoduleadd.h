#ifndef DRAWNMODULEADD_H
#define DRAWNMODULEADD_H
#include "../drawnmodulerectangle.h"

class QPainter;

class DrawnModuleAdd : public DrawnModuleRectangle
{
public:
    DrawnModuleAdd(DrawnSchema *parentSchema, CoreModule *coreModule);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAWNMODULEADD_H
