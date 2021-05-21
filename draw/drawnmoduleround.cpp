#include "drawnmoduleround.h"
#include "gui/guistyle.h"
#include <QPainter>

DrawnModuleRound::DrawnModuleRound(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModule(parentSchema, coreModule)
{
    float margin = GuiStyle::pModule().widthF() * 0.5f;
    mPosGridAnchor = QPointF(margin, margin);
}

QRectF DrawnModuleRound::boundingRect() const
{
    float margin = GuiStyle::pModule().widthF();
    return QRectF(-margin * 0.5f, -margin * 0.5f, 2.0f + margin, 2.0f + margin);
}

void DrawnModuleRound::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.addEllipse(0.0f, 0.0f, 2.0f, 2.0f);
    painter->drawPath(path);
}

void DrawnModuleRound::positionPlug(DrawnItem *plug, Side side)
{
    float margin = GuiStyle::pModule().widthF() * 0.5;

    switch(side) {
    case top:
        plug->setRotation(90);
        plug->moveBy(1.0f, margin);
        break;
    case right:
        plug->setRotation(180);
        plug->moveBy(2.0f - margin, 1.0f);
        break;
    case bottom:
        plug->setRotation(270);
        plug->moveBy(1.0f, 2.0f - margin);
        break;
    case left:
        plug->setRotation(0);
        plug->moveBy(margin, 1.0f);
        break;
    }
}

DrawnInput *DrawnModuleRound::newInput(std::string name, Side side)
{
    DrawnInput *input = DrawnModule::newInput(name);
    positionPlug(input, side);
    return input;
}

DrawnOutput *DrawnModuleRound::newOutput(std::string name, Side side)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    positionPlug(output, side);
    return output;
}
