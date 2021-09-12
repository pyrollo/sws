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
    // Pens
    static QPen pModule()          { return QPen(QColor("#448"), .1); }
    static QPen pModuleSelected()  { return QPen(QColor("#884"), .1); }
    static QPen pPlug()            { return QPen(QColor("#448"), .05); }
    static QPen pPlugSelected()    { return QPen(QColor("#884"), .05); }
    static QPen pPlugConnecting()  { return QPen(QColor("#6A6"), .05); }
    static QPen pPlugConnected()   { return QPen(QColor("#448"), .05); }
    static QPen pPlugConnectable() { return QPen(QColor("#8F8"), .05); }
    static QPen pWire()            { return QPen(QColor("#66C"), .1); } // Qt::SolidLine, Qt::FlatCap); }
    static QPen pWireSelected()    { return QPen(QColor("#884"), .1); }
    static QPen pWireConnecting()  { return QPen(QColor("#6A6"), .1); }

    // Brushes
    static QBrush bBackground()      { return QBrush(QColor("#4B4B64")); }
    static QBrush bModule()          { return QBrush(QColor("#224")); }
    static QBrush bModuleSelected()  { return QBrush(QColor("#442")); }
    static QBrush bPlug()            { return QBrush(QColor("#224")); }
    static QBrush bPlugSelected()    { return QBrush(QColor("#442")); }
    static QBrush bPlugConnecting()  { return QBrush(QColor("#484")); }
    static QBrush bPlugConnectable() { return QBrush(QColor("#484")); }
    static QBrush bPlugConnected()   { return QBrush(QColor("#66C")); }
    static QBrush bWireSelected()    { return QBrush(QColor("#884")); } //Plug color when selected wire plugged in

    // Fonts
    static QFont fModule() { return QFont("SansSerif", 5); }
};

#endif // GUISTYLE_H
