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

#ifndef GUISCHEMASCENE_H
#define GUISCHEMASCENE_H
#include <QGraphicsScene>
#include "value/value.h"

class DrawnSchema;
class QLabel;

class GuiSchemaScene : public QGraphicsScene
{
public:
    GuiSchemaScene(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent *keyEvent);

    void setSchema(DrawnSchema *schema);
    DrawnSchema *schema() const { return mSchema; }

    void deleteSelected();

protected:
    DrawnSchema *mSchema;
};

#endif // GUISCHEMASCENE_H
