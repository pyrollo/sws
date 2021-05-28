#ifndef DRAWNMODULEOUTPUT_H
#define DRAWNMODULEOUTPUT_H
#include "../drawnmodulerectangle.h"

class CoreModuleOutput;

class DrawnModuleOutput : public DrawnModuleRectangle
{
    MODULE_TYPE("output")
public:
    DrawnModuleOutput(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    ~DrawnModuleOutput();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void setName(QString name);
    CoreModuleOutput *core() { return (CoreModuleOutput *)mCoreModule; }
protected:
    QString mName;
};

#endif // DRAWNMODULEOUTPUT_H
