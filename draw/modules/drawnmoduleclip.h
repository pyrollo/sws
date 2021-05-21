#ifndef DRAWNMODULECLIP_H
#define DRAWNMODULECLIP_H
#include "../drawnmodulerectangle.h"

class QPainter;

class DrawnModuleClip : public DrawnModuleRectangle
{
    MODULE_TYPE("clip")
public:
    DrawnModuleClip(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

};

#endif // DRAWNMODULECLIP_H
