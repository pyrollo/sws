#ifndef DRAWNMODULERECTANGLE_H
#define DRAWNMODULERECTANGLE_H
#include "drawnmodule.h"
class CoreModule;
class DrawnSchema;

class DrawnModuleRectangle : public DrawnModule
{
public:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

protected:
    enum Side { top, right, bottom, left };

    float mWidth;
    float mHeight;

    DrawnModuleRectangle(DrawnSchema *parentSchema, CoreModule *coreModule, float width, float height);

    DrawnInput *newInput(std::string name, Side side, float position);
    DrawnOutput *newOutput(std::string name, Side side, float position);

    void positionPlug(DrawnItem *plug, Side side, float position);
};

#endif // DRAWNMODULERECTANGLE_H
