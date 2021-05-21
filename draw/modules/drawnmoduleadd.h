#ifndef DRAWNMODULEADD_H
#define DRAWNMODULEADD_H
#include "../drawnmodulerectangle.h"

class QPainter;

class DrawnModuleAdd : public DrawnModuleRectangle
{
    MODULE_TYPE("add")
public:
    DrawnModuleAdd(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWNMODULEADD_H
