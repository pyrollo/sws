#include "drawnplug.h"
#include "drawnwire.h"
#include "drawnmodule.h"
#include "gui/guistyle.h"
#include "core/coreexceptions.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QMessageBox>

DrawnPlug::DrawnPlug(DrawnModule *parentModule) :
    DrawnItem(parentModule), mModule(parentModule), mOrientation(top), mWire(nullptr), mHighlighted(false)
{
    setFlags(flags()|ItemIsSelectable|ItemSendsGeometryChanges);
    if (mModule->schema())
        setAcceptHoverEvents(true);
}

DrawnPlug::~DrawnPlug()
{
    while (!mConnectedWires.empty())
        delete *(mConnectedWires.begin()); // Should be better with something like "disconnect"
}

QRectF DrawnPlug::boundingRect() const
{
    float margin = GuiStyle::pPlug().width();
    return QRectF(-margin, -margin - plugSize, margin + plugSize, plugSize * 2 + margin);
}

QPointF DrawnPlug::connectionPoint() const
{
    return QPointF(0, 0);
}

void DrawnPlug::setOrientation(Orientation orientation)
{
    setRotation(angleFromOrientation(orientation));
    mOrientation = orientation;
}

void DrawnPlug::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (mModule->schema() && pluggable()) {
        if (mWire)
            delete mWire;
        mWire = new DrawnWire(mModule->schema());
        mWire->connectTo(this);
        mWire->drag(mapToScene(event->pos()));
        mModule->schema()->highlightConnectable(this);
        update();
    }
}

void DrawnPlug::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mWire) {
        mWire->drag(mapToScene(event->pos()));
    } else {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void DrawnPlug::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (mWire) {
        auto items = scene()->items(event->scenePos());
        for (auto item: items) {
            DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);
            if (plug) {
                try {
                    mWire->connectTo(plug);
                    break;
                } catch(CoreException &e) {
                    QMessageBox msgBox;
                    msgBox.setText(e.what());
                    msgBox.exec();
                }
            }
        }

        mWire->endDrag();
        if (!mWire->isValid())
            delete mWire;
        mWire = nullptr;
        module()->schema()->unHighlight();
        update();
    } else {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}

void DrawnPlug::setHighlighted(bool highlighted)
{
    if (highlighted != mHighlighted) {
        mHighlighted = highlighted;
        update();
    }
}

void DrawnPlug::setPenAndBrush(QPainter *painter)
{
    if (module()->isSelected()) {
        painter->setPen(GuiStyle::pPlugSelected());
        painter->setBrush(GuiStyle::bPlugSelected());
    } else {
        painter->setPen(GuiStyle::pPlug());
        painter->setBrush(GuiStyle::bPlug());
    }

    if (connected()) {
//        painter->setPen(GuiStyle::pPlugConnected());
        painter->setBrush(GuiStyle::bPlugConnected());
    }

    if (mWire) {
//        painter->setPen(GuiStyle::pPlugConnecting());
        painter->setBrush(GuiStyle::bPlugConnecting());
    }

    if (mHighlighted) {
        painter->setPen(GuiStyle::pPlugConnectable());
//        painter->setBrush(GuiStyle::bPlugConnectable());
    }

    for (auto wire: mConnectedWires)
        if (wire->isSelected()) {
            painter->setBrush(GuiStyle::bWireSelected());
            break;
        }
}

void DrawnPlug::addConnectedWire(DrawnWire *wire)
{
    mConnectedWires.insert(wire);
    update();
}

void DrawnPlug::removeConnectedWire(DrawnWire *wire)
{
    mConnectedWires.erase(wire);
    update();
}

bool DrawnPlug::connected()
{
    return !mConnectedWires.empty();
}

bool DrawnPlug::hasSameOrientation(DrawnPlug *plug)
{
    return plug->mOrientation == mOrientation;
}

bool DrawnPlug::hasOppositeOrientation(DrawnPlug *plug)
{
    return plug->mOrientation == oppositeOrientation(mOrientation);
}

DrawnPlug::Orientation DrawnPlug::oppositeOrientation(Orientation orientation) {
    return (DrawnPlug::Orientation)((orientation + 2)%4);
}

int DrawnPlug::angleFromOrientation(Orientation orientation)
{
    return orientation * 90;
}

DrawnPlug::Orientation DrawnPlug::rotateOrientation(Orientation orientation, Orientation by)
{
    return (DrawnPlug::Orientation)((orientation + by)%4);
}

void DrawnPlug::rotatePoint(QPointF &point, Orientation by)
{
    float y;
    switch(by) {
    case right:
        return;
    case bottom:
        y = point.y();
        point.setY(-point.x());
        point.setX(y);
        return;
    case left:
        point.setX(-point.x());
        point.setY(-point.y());
        return;
    case top:
        y = point.y();
        point.setY(point.x());
        point.setX(- y);
        return;
    }
}

void DrawnPlug::unrotatePoint(QPointF &point, Orientation by)
{
    float y;
    switch(by) {
    case right:
        return;
    case bottom:
        y = point.y();
        point.setY(point.x());
        point.setX(-y);
        return;
    case left:
        point.setX(-point.x());
        point.setY(-point.y());
        return;
    case top:
        y = point.y();
        point.setY(-point.x());
        point.setX(y);
        return;
    }
}

