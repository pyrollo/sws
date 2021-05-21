#ifndef DRAWNMODULECONSTANT_H
#define DRAWNMODULECONSTANT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleConstant : public DrawnModuleRectangle
{
    MODULE_TYPE("constant")
public:
    DrawnModuleConstant(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};

#endif // DRAWNMODULECONSTANT_H
