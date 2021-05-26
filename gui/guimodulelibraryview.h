#ifndef GUIMODULELIBRARYVIEW_H
#define GUIMODULELIBRARYVIEW_H
#include <QGraphicsView>
#include "guimodulelibraryscene.h"

class DrawnModuleFactory;
class GuiModuleLibraryScene;

class GuiModuleLibraryView : public QGraphicsView
{
public:
    GuiModuleLibraryView(QWidget *parent = nullptr);
    void setFactory(DrawnModuleFactory *factory);
    float getScale() const { return mScale; }
protected:
    GuiModuleLibraryScene mScene;
    float mScale;
};

#endif // GUIMODULELIBRARYVIEW_H
