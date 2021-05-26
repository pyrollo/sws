#include "guimodulelibraryscene.h"
#include "guistyle.h"
#include "draw/drawnmodulefactory.h"
#include "draw/drawnmodule.h"

GuiModuleLibraryScene::GuiModuleLibraryScene(QObject *parent):
    QGraphicsScene(parent), mFactory(nullptr)
{
    setBackgroundBrush(GuiStyle::bBackground());
}

void GuiModuleLibraryScene::setFactory(DrawnModuleFactory *factory)
{
    if (mFactory == factory)
        return;

    mFactory = factory;

    clear();

    if (mFactory)
    {
        float y = 1.0f;
        for (auto moduletype: mFactory->listModules()) {
            DrawnModule *module = mFactory->newModule(moduletype);
            QRectF rect = module->boundingRect();
            module->moveBy(-0.5 * rect.width(), y);
            y += rect.height() + 1.0f;
            addItem(module);
        }
    }

    QRectF rect = itemsBoundingRect().marginsAdded(QMarginsF(0.5f, 0.5f, 0.5f, 0.5f));
    setSceneRect(rect);
    update();
}
