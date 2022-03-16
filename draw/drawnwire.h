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

#ifndef DRAWNWIRE_H
#define DRAWNWIRE_H

#include <QGraphicsObject>
#include "drawnschema.h"

class DrawnOutput;
class DrawnInput;
class DrawnPlug;

class DrawnWire : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit DrawnWire(QGraphicsObject *parent);
    ~DrawnWire();

    QRectF boundingRect() const override { return mBoundingRect; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void connectTo(DrawnOutput *output);
    void connectTo(DrawnInput *input);
    void connectTo(DrawnPlug *plug);

    void drag(QPointF scenePoint);
    void endDrag();
    bool isValid() { return mConnectedOutput && mConnectedInput; }

    Q_SLOT void endpointsmoved();

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    QPainterPath shape() const;

protected:
    QRectF mBoundingRect;

    bool mDragging;
    QPointF mDragpoint;

    QPointF mFrom, mTo;

    DrawnOutput *mConnectedOutput;
    DrawnInput *mConnectedInput;

    QPainterPath mPath;

    QTransform transformFromPlug(DrawnPlug* plug) const;
    QTransform rotateFromPlug(DrawnPlug* plug) const;

    void updatePath();
    bool isDrawable() const;
    QPainterPath path() const;

};

#endif // DRAWNWIRE_H
