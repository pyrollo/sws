#include "drawnwire.h"
#include "drawnoutput.h"
#include "drawninput.h"
#include "../core/coreinput.h"
#include "../core/coreoutput.h"
#include <algorithm>
#include "../gui/guistyle.h"
#include <QPainter>

DrawnWire::DrawnWire(DrawnSchema *parentSchema) :
    DrawnItem(parentSchema), mSchema(parentSchema),
    storedBoundingRect(0, 0, 0, 0),
    dragging(false), dragpoint(0, 0),
    mConnectedOutput(nullptr), mConnectedInput(nullptr)
{
    setFlags(flags()|ItemIsSelectable);
    setZValue(1);
}

DrawnWire::~DrawnWire()
{
    if (mConnectedOutput && mConnectedInput)
        mConnectedOutput->core()->disconnect(mConnectedInput->core());
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
        output->core()->connect(mConnectedInput->core());

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
        input->core()->connect(mConnectedOutput->core());

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
    from = QPointF(0, 0);
    to = QPointF(0, 0);

    if (!dragging && (!mConnectedInput || !mConnectedOutput)) {
        storedBoundingRect = QRectF(0, 0, 0, 0);
        return;
     }

    if (mConnectedInput) {
        from = mapFromItem(mConnectedInput, mConnectedInput->connectionPoint());
        if (dragging)
            to = dragpoint;
    }

    if (mConnectedOutput) {
        to = mapFromItem(mConnectedOutput, mConnectedOutput->connectionPoint());
        if (dragging)
            from = dragpoint;
    }

    storedBoundingRect = QRectF(QPointF(std::min(from.x(), to.x()), std::min(from.y(), to.y())),
            QPointF(std::max(from.x(), to.x()), std::max(from.y(), to.y())))
            .marginsAdded(QMarginsF(margin, margin, margin, margin));
}

void DrawnWire::drag(QPointF scenePoint)
{
    dragging = true;
    dragpoint = mapFromScene(scenePoint);

    updateBoundingRect();
    update();
}

void DrawnWire::endDrag()
{
    dragging = false;
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

void DrawnWire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    if (dragging) {
        painter->setPen(GuiStyle::pWireConnecting());
    } else if (isSelected()) {
        painter->setPen(GuiStyle::pWireSelected());
    } else {
        painter->setPen(GuiStyle::pWire());
    }

    QPointF input;
    QPointF output;

    if (from != to) {
        QPointF points[4] = {
            from,
            QPointF((from.x() + to.x())/2, from.y()),
            QPointF((from.x() + to.x())/2, to.y()),
            to
        };

        painter->drawPolyline(points, 4);

    }
}

