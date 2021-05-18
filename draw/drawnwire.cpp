#include "drawnwire.h"
#include "drawnoutput.h"
#include "drawninput.h"
#include "../core/coreinput.h"
#include "../core/coreoutput.h"
#include "../core/coreschema.h"
#include <algorithm>
#include "../gui/guistyle.h"
#include <QPainter>
#include <QPainterPathStroker>

DrawnWire::DrawnWire(DrawnSchema *parentSchema) :
    DrawnItem(parentSchema), mSchema(parentSchema), mBoundingRect(0,0,0,0),
    mDragging(false), mDragpoint(0, 0),
    mConnectedOutput(nullptr), mConnectedInput(nullptr)
{
    setFlags(flags()|ItemIsSelectable);
    setZValue(1);
}

DrawnWire::~DrawnWire()
{
    if (mConnectedOutput && mConnectedInput)
        schema()->core()->disconnect(mConnectedInput->core(), mConnectedOutput->core());
    if (mConnectedOutput)
        mConnectedOutput->removeConnectedWire(this);
    if (mConnectedInput)
        mConnectedInput->removeConnectedWire(this);
}

void DrawnWire::connectTo(DrawnOutput *output)
{
    if (mConnectedOutput || !output)
        return;

    if (mConnectedInput)
        schema()->core()->connect(mConnectedInput->core(), output->core());

    mConnectedOutput = output;
    mConnectedOutput->addConnectedWire(this);

    connect(mConnectedOutput, SIGNAL(positionChanged()), this, SLOT(endpointsmoved()));
    updateBoundingRect();
    update();
}

void DrawnWire::connectTo(DrawnInput *input)
{
    if (mConnectedInput || !input)
        return;

    if (mConnectedOutput)
        schema()->core()->connect(input->core(), mConnectedOutput->core());

    mConnectedInput = input;
    mConnectedInput->addConnectedWire(this);

    connect(mConnectedInput, SIGNAL(positionChanged()), this, SLOT(endpointsmoved()));
    updateBoundingRect();
    update();
}

void DrawnWire::connectTo(DrawnPlug *plug)
{
    DrawnInput *input = dynamic_cast<DrawnInput *>(plug);
    if (input) {
        connectTo(input);
        return;
    }
    DrawnOutput *output = dynamic_cast<DrawnOutput *>(plug);
    if (output) {
        connectTo(output);
        return;
    }
}

Q_SLOT void DrawnWire::endpointsmoved()
{
    updateBoundingRect();
    update();
}

void DrawnWire::updateBoundingRect()
{
    prepareGeometryChange();
    float margin = GuiStyle::pWire().widthF() * 0.5f;
    mFrom = QPointF(0, 0);
    mTo = QPointF(0, 0);

    if (!mDragging && (!mConnectedInput || !mConnectedOutput)) {
        mBoundingRect = QRectF(0, 0, 0, 0);
        return;
     }

    if (mConnectedInput) {
        mFrom = mapFromItem(mConnectedInput, mConnectedInput->connectionPoint());
        if (mDragging)
            mTo = mDragpoint;
    }

    if (mConnectedOutput) {
        mTo = mapFromItem(mConnectedOutput, mConnectedOutput->connectionPoint());
        if (mDragging)
            mFrom = mDragpoint;
    }

    mBoundingRect = QRectF(QPointF(std::min(mFrom.x(), mTo.x()), std::min(mFrom.y(), mTo.y())),
            QPointF(std::max(mFrom.x(), mTo.x()), std::max(mFrom.y(), mTo.y())))
            .marginsAdded(QMarginsF(margin, margin, margin, margin));
}

void DrawnWire::drag(QPointF scenePoint)
{
    mDragging = true;
    mDragpoint = mapFromScene(scenePoint);

    updateBoundingRect();
    update();
}

void DrawnWire::endDrag()
{
    mDragging = false;
    updateBoundingRect();
    update();
}

QVariant DrawnWire::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        if (value == true)
             setZValue(2);
        else
             setZValue(1);

        if (mConnectedOutput)
            mConnectedOutput->update();

        if (mConnectedInput)
            mConnectedInput->update();
    }

    return QGraphicsItem::itemChange(change, value);
}

QPainterPath DrawnWire::path() const
{
    QPainterPath path;
    path.moveTo(mFrom);
    path.lineTo(QPointF((mFrom.x() + mTo.x())/2, mFrom.y()));
    path.lineTo(QPointF((mFrom.x() + mTo.x())/2, mTo.y()));
    path.lineTo(mTo);
    return path;
}

QPainterPath DrawnWire::shape() const
{
    QPainterPathStroker stroker;
    stroker.setWidth(0.3f); // TODO: Put that in a setting (distance around wire to select them)
    return stroker.createStroke(path());
}

void DrawnWire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    if (mDragging) {
        painter->setPen(GuiStyle::pWireConnecting());
    } else if (isSelected()) {
        painter->setPen(GuiStyle::pWireSelected());
    } else {
        painter->setPen(GuiStyle::pWire());
    }

    painter->drawPath(path());
}
