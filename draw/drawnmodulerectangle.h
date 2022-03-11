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

#ifndef DRAWNMODULERECTANGLE_H
#define DRAWNMODULERECTANGLE_H
#include "drawnmodule.h"

class DrawnModuleRectangle : public DrawnModule
{
public:
    DrawnModuleRectangle(std::string type, DrawnSchema *parentSchema, CoreModule *coreModule);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    void newInput(std::string name, DrawnPlug::Orientation orientation);
    void newOutput(std::string name, DrawnPlug::Orientation orientation);
    //void newSeparator(DrawnPlug::Orientation orientation);

protected:
    float mWidth;
    float mHeight;

    std::vector<DrawnPlug *> mPlugs[4];

    void addPlug(DrawnPlug *plug, DrawnPlug::Orientation orientation);
    void repositionPlugs(DrawnPlug::Orientation orientation);
};

#endif // DRAWNMODULERECTANGLE_H
