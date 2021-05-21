#ifndef DRAWNMODULEMULTIPLY_H
#define DRAWNMODULEMULTIPLY_H
#include "../drawnmodulerectangle.h"

class DrawnModuleMultiply : public DrawnModuleRectangle
{
    MODULE_TYPE("multiply")
public:
    DrawnModuleMultiply(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWNMODULEMULTIPLY_H
