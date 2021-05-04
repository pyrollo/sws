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

    painter->setPen(GuiStyle::pModule());
    painter->setBrush(GuiStyle::bModule());

    QPainterPath path;
    path.addRoundedRect(0.0f, 0.0f, mWidth, mHeight, 0.1f, 0.1f);
    painter->drawPath(path);
}

void DrawnModuleRectangle::positionPlug(DrawnItem *plug, Side side, float position)
{
    switch(side) {
    case top:
        plug->setRotation(90);
        plug->moveBy(position, 0.0f);
        break;
    case right:
        plug->setRotation(180);
        plug->moveBy(mWidth, position);
        break;
    case bottom:
        plug->setRotation(270);
        plug->moveBy(position, mHeight);
        break;
    case left:
        plug->setRotation(0);
        plug->moveBy(0.0f, position);
        break;
    }
}


DrawnInput *DrawnModuleRectangle::newInput(std::string name, Side side, float position)
{
    DrawnInput *input = DrawnModule::newInput(name);
    positionPlug(input, side, position);
    return input;
}

DrawnOutput *DrawnModuleRectangle::newOutput(std::string name, Side side, float position)
{
    DrawnOutput *output = DrawnModule::newOutput(name);
    positionPlug(output, side, position);
    return output;
}
