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

#ifndef GUISCHEMAVIEW_H
#define GUISCHEMAVIEW_H
#include "guischemascene.h"
#include <QGraphicsView>

class DrawnSchema;

class GuiSchemaView : public QGraphicsView
{
public:
    GuiSchemaView(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent* event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

    void setSchema(DrawnSchema *schema) { mScene.setSchema(schema); }
    void setProbeWidget(QLabel *widget) { mScene.setProbeWidget(widget); }

protected:
    GuiSchemaScene mScene;
};

#endif // GUISCHEMAVIEW_H
