/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "drawnwire.h"
#include "drawnoutput.h"
#include "drawninput.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"
#include "core/coreschema.h"
#include <algorithm>
#include <cmath>
#include "../gui/guistyle.h"
#include <QPainter>
#include <QPainterPathStroker>

DrawnWire::DrawnWire(DrawnSchema *parentSchema) :
    DrawnItem(parentSchema), mBoundingRect(0,0,0,0),
    mDragging(false), mDragpoint(0, 0),
    mConnectedOutput(nullptr), mConnectedInput(nullptr)
{
    setFlags(flags()|ItemIsSelectable);
    setZValue(1);
}

DrawnWire::~DrawnWire()
{
    if (mConnectedOutput && mConnectedInput)
        mSchema->core()->disconnect(mConnectedInput->core(), mConnectedOutput->core());
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
    updatePath();
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
    updatePath();
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
    updatePath();
}

void DrawnWire::drag(QPointF scenePoint)
{
    mDragging = true;
    mDragpoint = mapFromScene(scenePoint);
    updatePath();
}

void DrawnWire::endDrag()
{
    mDragging = false;
    updatePath();
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

bool DrawnWire::isDrawable() const
{
    return (mDragging && (mConnectedOutput || mConnectedInput)) ||
            (mConnectedInput && mConnectedOutput);
}
QTransform DrawnWire::transformFromPlug(DrawnPlug* plug) const
{
    QPointF t = mapFromItem(plug, plug->connectionPoint());
    return rotateFromPlug(plug).translate(-t.x(), -t.y());
}

QTransform DrawnWire::rotateFromPlug(DrawnPlug* plug) const
{
    switch(plug->getOrientation()) {
    case DrawnPlug::left:
        return QTransform(-1.0, 0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0, 1.0);
    case DrawnPlug::top:
        return QTransform(0.0, 1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    case DrawnPlug::right:
        return QTransform(1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0);
    case DrawnPlug::bottom:
        return QTransform(0.0, -1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    }
    return QTransform(); // Should never happen
}

//TODO: tgtdir and/or transformations could be obtained from plugs (transformations are used for drawing)

QPainterPath DrawnWire::path() const
{
    static const float lateral = 2.0f;
    static const float extension = 1.0f;

    if (!isDrawable())
        return QPainterPath();

    QTransform transform;
    QPointF tgt; // Source is 0,0, target is that point (in transformed coordinates)
    QPointF tgtdir; // Target orientation as vector

    if (!mDragging || mConnectedOutput)
        transform = transformFromPlug(mConnectedOutput);
    else
        transform = transformFromPlug(mConnectedInput);

    if (mDragging) {
        tgt = transform.map(mDragpoint);
        if (tgt.x() < extension)
            tgtdir = QPointF(1.0f, 0.0f);
        else
            tgtdir = QPointF(-1.0f, 0.0f);
    } else {
        tgt = transform.map(mapFromItem(mConnectedInput, mConnectedInput->connectionPoint()));
        tgtdir = rotateFromPlug(mConnectedOutput).map(
                    rotateFromPlug(mConnectedInput).inverted().map(QPointF(1.0, 0.0)));
    }
    tgtdir = tgtdir * extension;

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);

    // Same orientation
    if (tgtdir.x() > 0.0f) {
        float x = fmax(tgt.x(), 0.0) + extension;
        path.lineTo(x, 0.0f);
        path.lineTo(x, tgt.y());
    }

    // Opposite orientation
    else if (tgtdir.x() < 0.0f) {
        // Face to face - Zigzag
        if (tgt.x() > 0) {
            path.lineTo(tgt.x() * 0.5f, 0.0f);
            path.lineTo(tgt.x() * 0.5f, tgt.y());
        }
        // Back to back
        else {
            if (fabs(tgt.y()) < lateral * 2.0) {
                // Not enough room to zigzag, go around
                float y = fmin(tgt.y(), 0.0) - lateral;
                path.lineTo(extension, 0.0f);
                path.lineTo(extension, y);
                path.lineTo(tgt.x() - extension, y);
                path.lineTo(tgt.x() - extension, tgt.y());
            } else {
                // Zigzag between
                path.lineTo(extension, 0.0f);
                path.lineTo(extension, tgt.y() * 0.5);
                path.lineTo(tgt.x() - extension, tgt.y() * 0.5);
                path.lineTo(tgt.x() - extension, tgt.y());
            }
        }
    }

    // Other cases
    else
    {
        if (tgt.x() >= 0.0f)
            // Source and target facing to crossing point
            if (tgt.y() * tgtdir.y() < 0.0f) {
                path.lineTo(tgt.x(), 0.0f);
            } else {
                path.lineTo(tgt.x() * 0.5f, 0.0f);
                path.lineTo(tgt.x() * 0.5f, tgt.y() + tgtdir.y());
                path.lineTo(tgt + tgtdir);
            }
       else
            if (tgt.y() * tgtdir.y() < 0.0f) {
                path.lineTo(extension, 0.0f);
                path.lineTo(extension, tgt.y() * 0.5f);
                path.lineTo(tgt.x(), tgt.y() * 0.5f);
            } else {
                path.lineTo(extension, 0.0f);
                path.lineTo(extension, tgt.y() + tgtdir.y());
                path.lineTo(tgt + tgtdir);
            }
    }

    // End path and traspose it back to scene coordinates
    path.lineTo(tgt);
    return transform.inverted().map(path);
}

void DrawnWire::updatePath()
{
    if (mConnectedInput) {
        mTo = mapFromItem(mConnectedInput, mConnectedInput->connectionPoint());
        if (mDragging)
            mFrom = mDragpoint;
    }

    if (mConnectedOutput) {
        mFrom = mapFromItem(mConnectedOutput, mConnectedOutput->connectionPoint());
        if (mDragging)
            mTo = mDragpoint;
    }

    // TODO: improve that (maybe some more cases, just use an empty path or put it in path())
    if (!mDragging && (!mConnectedInput || !mConnectedOutput)) {
        mBoundingRect = QRectF(0, 0, 0, 0);
        mPath = QPainterPath();
        update();
        return;
    }

    mPath = path();
    float margin = GuiStyle::wWire();
    prepareGeometryChange();
    mBoundingRect = mPath.boundingRect().marginsAdded(QMargins(margin, margin, margin, margin));
    update();
}

QPainterPath DrawnWire::shape() const
{
    QPainterPathStroker stroker;
    stroker.setWidth(0.3f); // TODO: Put that in a setting (distance around wire to select them)
    return stroker.createStroke(mPath);
}

void DrawnWire::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    if (mDragging) {
        painter->setPen(QPen(GuiStyle::cWireConnecting(), GuiStyle::wWire()));
    } else if (isSelected()) {
        painter->setPen(QPen(GuiStyle::cWireSelected(), GuiStyle::wWire()));
    } else {
        painter->setPen(QPen(GuiStyle::cWire(), GuiStyle::wWire()));
    }

    painter->drawPath(mPath);
}
