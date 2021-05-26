#ifndef GUIMODULELIBRARYSCENE_H
#define GUIMODULELIBRARYSCENE_H
#include <QGraphicsScene>

class DrawnModuleFactory;

class GuiModuleLibraryScene : public QGraphicsScene
{
public:
    GuiModuleLibraryScene(QObject *parent = nullptr);
    void setFactory(DrawnModuleFactory *factory);

protected:
    DrawnModuleFactory *mFactory;
};

#endif // GUIMODULELIBRARYSCENE_H
