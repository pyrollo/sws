#ifndef DRAWNMODULEINPUT_H
#define DRAWNMODULEINPUT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleInput : public DrawnModuleRectangle
{
public:
    DrawnModuleInput(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWNMODULEINPUT_H
