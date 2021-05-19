#ifndef DRAWNMODULECONSTANT_H
#define DRAWNMODULECONSTANT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleConstant : public DrawnModuleRectangle
{
public:
    DrawnModuleConstant(DrawnSchema *parentSchema, CoreModule *coreModule);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DRAWNMODULECONSTANT_H
