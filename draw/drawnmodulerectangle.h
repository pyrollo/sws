#ifndef DRAWNMODULERECTANGLE_H
#define DRAWNMODULERECTANGLE_H
#include "drawnmodule.h"

class DrawnModuleRectangle : public DrawnModule
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    float mWidth;
    float mHeight;

    DrawnModuleRectangle(DrawnSchema *parentSchema, CoreModule *coreModule, float width, float height);

    DrawnInput *newInput(std::string name, DrawnPlug::Orientation orientation, float position);
    DrawnOutput *newOutput(std::string name, DrawnPlug::Orientation orientation, float position);

    void positionPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation, float position);
};

#endif // DRAWNMODULERECTANGLE_H
