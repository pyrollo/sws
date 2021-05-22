#include "drawnmodulerectangle.h"
#include "gui/guistyle.h"
#include <QPainter>

DrawnModuleRectangle::DrawnModuleRectangle(DrawnSchema *parentSchema, CoreModule *coreModule, float width, float height):
    DrawnModule(parentSchema, coreModule), mWidth(width), mHeight(height)
{
    float margin = GuiStyle::pModule().widthF() * 0.5f;
    mPosGridAnchor = QPointF(margin, margin);
}

QRectF DrawnModuleRectangle::boundingRect() const
{
    float margin = GuiStyle::pModule().widthF();
    return QRectF(-margin * 0.5f, -margin * 0.5f, mWidth + margin, mHeight + margin);
}

void DrawnModuleRectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.addRoundedRect(0.0f, 0.0f, mWidth, mHeight, 0.1f, 0.1f);
    painter->drawPath(path);
}

void DrawnModuleRectangle::positionPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation, float position)
{
    plug->setOrientation(orientation);
    switch(orientation) {
    case DrawnPlug::top:
        plug->moveBy(position, 0.0f);
        break;
    case DrawnPlug::right:
        plug->moveBy(mWidth, position);
        break;
    case DrawnPlug::bottom:
        plug->moveBy(position, mHeight);
        break;
    case DrawnPlug::left:
        plug->moveBy(0.0f, position);
        break;
    }
}

DrawnInput *DrawnModuleRectangle::newInput(std::string name, DrawnPlug::Orientation orientation, float position)
{
    DrawnInput *input = DrawnModule::newInput(name);
    positionPlug(input, orientation, position);
    return input;
}

DrawnOutput *DrawnModuleRectangle::newOutput(std::string name, DrawnPlug::Orientation orientation, float position)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    positionPlug(output, orientation, position);
    return output;
}
