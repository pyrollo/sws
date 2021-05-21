#ifndef DRAWMODULETIME_H
#define DRAWMODULETIME_H
#include "../drawnmoduleround.h"

class QPainter;

class DrawnModuleTime : public DrawnModuleRound
{
    MODULE_TYPE("time")
public:
    DrawnModuleTime(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
};

#endif // DRAWMODULETIME_H
