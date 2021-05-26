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
