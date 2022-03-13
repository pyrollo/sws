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

#include "guimodulelibraryscene.h"

#include "draw/style.h"
#include "draw/drawnitemfactory.h"
#include "draw/drawnmodule.h"

#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QPainter>

GuiModuleLibraryScene::GuiModuleLibraryScene(QObject *parent):
    QGraphicsScene(parent), mFactory(nullptr)
{
    setBackgroundBrush(Style::cSceneBackground());
}

void GuiModuleLibraryScene::setFactory(DrawnItemFactory *factory)
{
    if (mFactory == factory)
        return;

    mFactory = factory;

    clear();

    if (mFactory)
    {
        float y = 1.0f;
        for (auto type: mFactory->listItems()) {
            DrawnItem *item = mFactory->newItem(type);
            QRectF rect = item->boundingRect();
            item->moveBy(-0.5 * rect.width(), y);
            y += rect.height() + 1.0f;
            addItem(item);
        }
    }

    QRectF rect = itemsBoundingRect().marginsAdded(QMarginsF(0.5f, 0.5f, 0.5f, 0.5f));
    setSceneRect(rect);
    update();
}

void GuiModuleLibraryScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {

        // Find first ancestor item under mouse
        DrawnItem *item = (DrawnItem *)itemAt(event->scenePos(), QTransform());
        if (!item)
            return;

        while (item->parent())
            item = (DrawnItem *)item->parent();

        // Prepare dragging if found
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setData("sws/itemtype", QByteArray::fromStdString(item->getType()));
        drag->setMimeData(mimeData);

        // Create an image of module
        QRectF rect = item->boundingRect();

        DrawnItem *fakeItem = mFactory->newItem(item->getType());
        QGraphicsScene scene(rect);
        scene.addItem(fakeItem);

        QPixmap pix(rect.width() * 20, rect.height() * 20);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        scene.render(&painter, pix.rect(), rect);
        painter.end();
        delete fakeItem;

        // Start dragging
        drag->setPixmap(pix);
        drag->exec();
    }
}
