#ifndef DRAWNMODULESINUS_H
#define DRAWNMODULESINUS_H
#include "../drawnmodulerectangle.h"

class QPainter;

class DrawnModuleSinus : public DrawnModuleRectangle
{
    MODULE_TYPE("sinus")
public:
    DrawnModuleSinus(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWNMODULESINUS_H
