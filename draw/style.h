#ifndef DRAWNSTYLE_H
#define DRAWNSTYLE_H

#include <QColor>
#include <QFont>
#include <QFontDatabase>

class Style
{
public:
    // Fonts
    static QFont fModule()  { return getfont(5); }

    // Line width
    static qreal wModule() { return 1.0f; }
    static qreal wPlug()   { return 0.5f; }
    static qreal wWire()   { return 1.0f; }

    // Dimensions
    static qreal sGrid()   { return 10.0f; }
    static qreal sPlug()   { return 3.0f; }
    static qreal sIcon()   { return 14.0f; }

    // Colors
    static QColor cSceneBackground()    { return QColor("#4B4B64"); }
    static QColor cForeground()         { return QColor("#448"); }
    static QColor cBackground()         { return QColor("#224"); }
    static QColor cForegroundSelected() { return QColor("#884"); }
    static QColor cBackgroundSelected() { return QColor("#442"); }
    static QColor cForegroundError()    { return QColor("#A44"); }
    static QColor cBackgroundError()    { return QColor("#622"); }
    static QColor cHighlighted()        { return QColor("#484"); }
    static QColor cWire()               { return QColor("#66C"); }
    static QColor cWireSelected()       { return QColor("#884"); }
    static QColor cWireConnecting()     { return QColor("#6C6"); }

private:
    static QFont getfont(int size) {
        static QString family;
        if (family == "")
        {
            int id = QFontDatabase::addApplicationFont(":/fonts/Monoid-Retina-Tight-0-NoCalt.ttf");
            family = QFontDatabase::applicationFontFamilies(id).at(0);
        }
        return QFont(family, size);
    }
};



#endif // DRAWNSTYLE_H
