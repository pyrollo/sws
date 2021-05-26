#include "guimodulelibraryview.h"
#include "guimodulelibraryscene.h"

GuiModuleLibraryView::GuiModuleLibraryView(QWidget *parent):
    QGraphicsView(parent), mScene(), mScale(1.0f)
{
    setScene(&mScene);
}

void GuiModuleLibraryView::setFactory(DrawnModuleFactory *factory)
{
    mScene.setFactory(factory);

    if (mScene.width() > 0) {
        mScale = rect().width() / mScene.width();
        setTransform(QTransform().scale(mScale, mScale));
    }
}
