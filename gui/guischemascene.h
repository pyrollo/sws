#ifndef GUISCHEMASCENE_H
#define GUISCHEMASCENE_H
#include <QGraphicsScene>

class GuiSchemaScene : public QGraphicsScene
{
public:
    using QGraphicsScene::QGraphicsScene;

    void drawBackground(QPainter *painter, const QRectF &rect);

    int getGridSize() { return 1; };
};

#endif // GUISCHEMASCENE_H
