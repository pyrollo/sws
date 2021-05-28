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
    void setName(QString name);
    CoreModuleInput *core() { return (CoreModuleInput *)mCoreModule; }
protected:
    QString mName;
};

#endif // DRAWNMODULEINPUT_H
