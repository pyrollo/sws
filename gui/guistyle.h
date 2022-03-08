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

#ifndef GUISTYLE_H
#define GUISTYLE_H

#include <QColor>
#include <QBrush>
#include <QPen>
#include <QFont>

class GuiStyle
{
public:
    // Fonts
    static QFont fModule() { return QFont("SansSerif", 5); }

    // Line width
    static float wModule() { return 0.1f; }
    static float wPlug()   { return 0.05f; }
    static float wWire()   { return 0.1f; }

    // Colors
    static QColor cSceneBackground()    { return QColor("#4B4B64"); }
    static QColor cForeground()         { return QColor("#448"); }
    static QColor cBackground()         { return QColor("#224"); }
    static QColor cForegroundSelected() { return QColor("#884"); }
    static QColor cBackgroundSelected() { return QColor("#442"); }
    static QColor cHighlighted()        { return QColor("#484"); }
    static QColor cWire()               { return QColor("#66C"); }
    static QColor cWireSelected()       { return QColor("#884"); }
    static QColor cWireConnecting()     { return QColor("#66C"); }
};

#endif // GUISTYLE_H
