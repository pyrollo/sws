#ifndef DRAWNSTYLE_H
#define DRAWNSTYLE_H

#include <QColor>
#include <QFont>

class Style
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

#endif // DRAWNSTYLE_H
