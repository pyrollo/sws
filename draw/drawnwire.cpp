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
    connectedOutput(nullptr), connectedInput(nullptr)
{
    setZValue(2);
}

void DrawnWire::connectTo(DrawnOutput *output)
{
    if (connectedOutput || !output)
        return;

    if (connectedInput)
        output->core()->connect(connectedInput->core());

    connectedOutput = output;

    connect(connectedOutput, SIGNAL(positionChanged()), this, SLOT(endpointsmoved()));
    updateBoundingRect();
    update();
}

void DrawnWire::connectTo(DrawnInput *input)
{
    if (connectedInput || !input)
        return;

    if (connectedOutput)
        input->core()->connect(connectedOutput->core());

    connectedInput = input;

    connect(connectedInput, SIGNAL(positionChanged()), this, SLOT(endpointsmoved()));
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

    if (!dragging && (!connectedInput || !connectedOutput)) {
        storedBoundingRect = QRectF(0, 0, 0, 0);
        return;
     }

    if (connectedInput) {
        from = mapFromItem(connectedInput, connectedInput->connectionPoint());
        if (dragging)
            to = dragpoint;
    }

    if (connectedOutput) {
        to = mapFromItem(connectedOutput, connectedOutput->connectionPoint());
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

void DrawnWire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    if (dragging) {
        painter->setPen(GuiStyle::pWireConnecting());
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

//        QPointF points[2] = { from, to };

        painter->drawPolyline(points, 4);

    }
}

