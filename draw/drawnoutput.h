#ifndef DRAWNOUTPUT_H
#define DRAWNOUTPUT_H
#include "drawnplug.h"

class DrawnModule;
class CoreOutput;

class DrawnOutput : public DrawnPlug
{
public:
    DrawnOutput(DrawnModule *parent, CoreOutput *coreOutput);

    CoreOutput *core() { return mCoreOutput; }

    bool pluggable() { return true; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    CoreOutput *mCoreOutput;
};

#endif // DRAWNOUTPUT_H
