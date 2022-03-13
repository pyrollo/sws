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
#include "interactions/defaultinteraction.h"
#include "core/coreschema.h"
#include <unordered_set>

class DrawnModule;
class DrawnItemFactory;
class DrawnPlug;
class DrawnSchemaInteraction;

class DrawnSchema : public DrawnItem
{
    Q_OBJECT
public:
    DrawnSchema();
    ~DrawnSchema();

    DrawnSchema *schema() override { return this; }

    CoreSchema *core() { return &mCoreSchema; }
    DrawnItemFactory *getItemFactory() { return mItemFactory; }

    // Interaction management
    void startInteraction(DrawnSchemaInteraction *interaction);
    void endInteraction();
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item);
    void mousePressEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);

    DrawnItem *newItem(std::string type);

    const std::unordered_set<DrawnModule *> &modules() { return mModules; }
    DrawnModule *newModule(std::string type);
    void removeModule(DrawnModule *item);

    const std::unordered_set<DrawnDecoration *> &decorations() { return mDecorations; }
    DrawnDecoration *newDecoration(std::string type);
    void removeDecoration(DrawnDecoration *item);

    void highlightConnectable(DrawnPlug * plug);
    void highlightProbeable();
    void unHighlight();

    void notifyInputsChanged() { emit inputsChanged(); }
    void notifyOutputsChanged() { emit outputsChanged(); }


signals:
    void inputsChanged();
    void outputsChanged();

protected:
    CoreSchema mCoreSchema;
    DrawnItemFactory *mItemFactory;
    std::unordered_set<DrawnModule *> mModules;
    std::unordered_set<DrawnDecoration *> mDecorations;
    DefaultInteraction mDefaultInteraction;
    DrawnSchemaInteraction *mInteraction;
};

#endif // DRAWNSCHEMA_H
