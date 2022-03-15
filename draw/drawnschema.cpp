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

#include "drawnschema.h"

#include "drawnitem.h"
#include "drawnitemfactory.h"
#include "drawnschemainteraction.h"
#include "drawnmodule.h"

#include "core/coreschema.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"
#include "core/coremodule.h"
#include "core/coreexceptions.h"

#include <QPainter>

DrawnSchema::DrawnSchema() :
    QGraphicsItem(nullptr), mCoreSchema(),
    mDefaultInteraction(this), mInteraction(&mDefaultInteraction)
{
    mItemFactory = new DrawnItemFactory();
    // TODO: Not sure this is the best place for populating
    populateFactory(mItemFactory);
}

DrawnSchema::~DrawnSchema()
{
    while (mItems.size())
        delete *(mItems.begin());

    delete mItemFactory;
}

void DrawnSchema::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void)(painter); (void)(option); (void)(widget);
}

QRectF DrawnSchema::boundingRect() const
{
    return QRectF(-1000, -1000, 2000, 2000);
}

void DrawnSchema::startInteraction(DrawnSchemaInteraction *interaction)
{
    mInteraction->terminate();
    mInteraction = interaction;
    mInteraction->init();
}
void DrawnSchema::endInteraction()
{
    startInteraction(&mDefaultInteraction);
}

void DrawnSchema::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item)
{
    mInteraction->mouseDoubleClickEvent(event, item);
}

void DrawnSchema::mousePressEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item)
{
    mInteraction->mousePressEvent(event, item);
}

void DrawnSchema::mouseMoveEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item)
{
    mInteraction->mouseMoveEvent(event, item);
}

void DrawnSchema::mouseReleaseEvent(QGraphicsSceneMouseEvent *event, DrawnItem *item)
{
    mInteraction->mouseReleaseEvent(event, item);
}

DrawnItem *DrawnSchema::newItem(std::string type)
{
    DrawnItem *item = mItemFactory->newItem(type, this);
    mItems.insert(item);

    if (item->core()) {
        DrawnModule *module = dynamic_cast<DrawnModule *>(item);
        if (module) // Should be true
            mModules.insert(module);
    }

    return item;
}

// Should be called only from item destructor
void DrawnSchema::removeItem(DrawnItem *item) {
    if (item->core()) {
        core()->removeModule(item->core());
        mModules.erase((DrawnModule *)item);
    }

    mItems.erase(item);
}

void DrawnSchema::highlightConnectable(DrawnPlug * plug)
{
    std::unordered_set<CoreModule *> list;

    DrawnInput *input = dynamic_cast<DrawnInput *>(plug);
    if (input) {
        input->core()->module()->listDownstream(list);
        for (auto module : mModules)
            if (list.find(module->core()) == list.end())
                module->highlightPluggableOutputs();
    }

    DrawnOutput *output = dynamic_cast<DrawnOutput *>(plug);
    if (output) {
        output->core()->module()->listUpstream(list);
        for (auto module : mModules)
             if (list.find(module->core()) == list.end())
                module->highlightPluggableInputs();
    }

    plug->setConnecting(true);
}

void DrawnSchema::highlightProbeable()
{
    for (auto module : mModules) {
        module->highlightProbeableInputs();
        module->highlightProbeableOutputs();
    }
}

void DrawnSchema::unHighlight()
{
    for (auto module : mModules)
        module->unHighlightPlugs();
}

