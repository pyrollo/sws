#ifndef DRAWNMODULEOUTPUT_H
#define DRAWNMODULEOUTPUT_H
#include "../drawnmodulerectangle.h"

class DrawnModuleOutput : public DrawnModuleRectangle
{
    MODULE_TYPE("output")
public:
    DrawnModuleOutput(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWNMODULEOUTPUT_H
