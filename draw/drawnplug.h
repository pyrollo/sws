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

#ifndef DRAWNPLUG_H
#define DRAWNPLUG_H
#include "drawnitem.h"
#include <unordered_set>

class DrawnWire;
class DrawnModule;
class CorePlug;

class DrawnPlug : public DrawnItem
{
public:
    enum Orientation { left = 0, top, right, bottom };

    DrawnPlug(DrawnModule *parentModule, CorePlug *corePlug = nullptr);
    ~DrawnPlug();

    DrawnModule *module() { return mModule; }

    CorePlug *core() { return mCorePlug; }

    virtual bool pluggable() = 0;
    bool connected();

    QRectF boundingRect() const;
    QPointF connectionPoint() const { return QPointF(0, 0); }

    void setOrientation(Orientation orientation);
    Orientation getOrientation() { return mOrientation; }

    void setHighlighted(bool highlighted);
    void setConnecting(bool connecting);

    void addConnectedWire(DrawnWire *wire);
    void removeConnectedWire(DrawnWire *wire);

    bool hasSameOrientation(DrawnPlug *plug);
    bool hasOppositeOrientation(DrawnPlug *plug);

    static Orientation oppositeOrientation(Orientation orientation);
    static int angleFromOrientation(Orientation orientation);
    static Orientation rotateOrientation(Orientation orientation, Orientation by);
    static void rotatePoint(QPointF &point, Orientation by);
    static void unrotatePoint(QPointF &point, Orientation by);

protected:
    const float plugSize = 0.3f;

    DrawnModule *mModule;
    CorePlug *mCorePlug;
    Orientation mOrientation;
    bool mHighlighted;
    bool mConnecting;
    std::unordered_set<DrawnWire *>mConnectedWires;

    void setStyle(QPainter *painter);
};

#endif // DRAWNPLUG_H
