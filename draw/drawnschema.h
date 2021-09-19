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

#ifndef DRAWNSCHEMA_H
#define DRAWNSCHEMA_H
#include "drawnitem.h"
#include "core/coreschema.h"
#include <unordered_set>

class DrawnModule;
class DrawnModuleFactory;
class DrawnPlug;
class Prober;

class DrawnSchema : public DrawnItem
{
    Q_OBJECT
public:
    DrawnSchema();
    ~DrawnSchema();

    CoreSchema *core() { return &mCoreSchema; }
    DrawnModuleFactory *getModuleFactory() { return mModuleFactory; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    DrawnModule *newModule(std::string type);
    void removeModule(DrawnModule *module);

    void highlightConnectable(DrawnPlug * plug);
    void highlightProbeable();
    void unHighlight();

    void setProber(Prober *prober)  { mProber = prober; }
    Prober *getProber() { return mProber; }

    void notifyInputsChanged() { emit inputsChanged(); }
    void notifyOutputsChanged() { emit outputsChanged(); }

    const std::unordered_set<DrawnModule *> &modules() { return mModules; }

signals:
    void inputsChanged();
    void outputsChanged();

protected:
    CoreSchema mCoreSchema;
    DrawnModuleFactory *mModuleFactory;
    std::unordered_set<DrawnModule *> mModules;
    Prober *mProber;

};

#endif // DRAWNSCHEMA_H
