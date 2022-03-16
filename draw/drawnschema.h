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

#include "interactions/defaultinteraction.h"
#include "core/coreschema.h"

#include <unordered_set>
#include <QGraphicsObject>

class DrawnItem;
class DrawnItemFactory;
class DrawnInteractive;
class DrawnModule;
class DrawnPlug;
class DrawnSchemaInteraction;

class DrawnSchema : public QGraphicsObject
{
    Q_OBJECT
public:
    DrawnSchema();
    ~DrawnSchema();

    CoreSchema *core() { return &mCoreSchema; }
    DrawnItemFactory *getItemFactory() { return mItemFactory; }

    // Interaction management
    void startInteraction(DrawnSchemaInteraction *interaction);
    void endInteraction();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *emitter);
    void mousePressEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *emitter);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *emitter);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawnInteractive *emitter);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    const std::unordered_set<DrawnItem *> &items() { return mItems; }
    DrawnItem *newItem(std::string type);
    void removeItem(DrawnItem *item);

    void highlightConnectable(DrawnPlug * plug);
    void highlightProbeable();
    void unHighlight();

    void notifyInputsChanged() { emit inputsChanged(); }
    void notifyOutputsChanged() { emit outputsChanged(); }

    void deleteSelected();

signals:
    void inputsChanged();
    void outputsChanged();

protected:
    CoreSchema mCoreSchema;
    DrawnItemFactory *mItemFactory;

    std::unordered_set<DrawnItem *> mItems;
    std::unordered_set<DrawnModule *> mModules;

    DefaultInteraction mDefaultInteraction;
    DrawnSchemaInteraction *mInteraction;
};

#endif // DRAWNSCHEMA_H
