#include "drawnmoduletime.h"

DrawnModuleTime::DrawnModuleTime(DrawnSchema *schema, CoreModule *coreModule):
    DrawnModuleRound(schema, coreModule)
{
    newOutput("time", right);
}

void DrawnModuleTime::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    DrawnModuleRound::paint(painter, option, widget);
}
