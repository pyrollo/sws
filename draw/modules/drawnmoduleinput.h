#ifndef DRAWNMODULEINPUT_H
#define DRAWNMODULEINPUT_H
#include "../drawnmodulerectangle.h"

class CoreModuleInput;

class DrawnModuleInput : public DrawnModuleRectangle
{
    MODULE_TYPE("input")
public:
    DrawnModuleInput(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    ~DrawnModuleInput();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    CoreModuleInput *core() { return (CoreModuleInput *)mCoreModule; }
protected:
    std::string mName;
};

#endif // DRAWNMODULEINPUT_H
