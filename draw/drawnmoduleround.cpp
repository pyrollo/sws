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

void DrawnModuleRound::positionPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation)
{
    float margin = GuiStyle::pModule().widthF() * 0.5;
    plug->setOrientation(orientation);
    switch(orientation) {
    case DrawnPlug::top:
        plug->moveBy(1.0f, margin);
        break;
    case DrawnPlug::right:
        plug->moveBy(2.0f - margin, 1.0f);
        break;
    case DrawnPlug::bottom:
        plug->moveBy(1.0f, 2.0f - margin);
        break;
    case DrawnPlug::left:
        plug->moveBy(margin, 1.0f);
        break;
    }
}

DrawnInput *DrawnModuleRound::newInput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnInput *input = DrawnModule::newInput(name);
    positionPlug(input, orientation);
    return input;
}

DrawnOutput *DrawnModuleRound::newOutput(std::string name, DrawnPlug::Orientation orientation)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    positionPlug(output, orientation);
    return output;
}
