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

#ifndef GUIMODULELIBRARYVIEW_H
#define GUIMODULELIBRARYVIEW_H
#include <QGraphicsView>
#include "guimodulelibraryscene.h"

class DrawnItemFactory;
class GuiModuleLibraryScene;

class GuiModuleLibraryView : public QGraphicsView
{
public:
    GuiModuleLibraryView(QWidget *parent = nullptr);
    void setFactory(DrawnItemFactory *factory);
    float getScale() const { return mScale; }
protected:
    GuiModuleLibraryScene mScene;
    float mScale;
};

#endif // GUIMODULELIBRARYVIEW_H
