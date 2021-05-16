#ifndef GUISCHEMASCENE_H
#define GUISCHEMASCENE_H
#include <QGraphicsScene>

class DrawnSchema;

class GuiSchemaScene : public QGraphicsScene
{
public:
    GuiSchemaScene();
    void drawBackground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *keyEvent);

    void removeSchema();
    void setSchema(DrawnSchema *schema);
protected:
    DrawnSchema *mSchema;
};

#endif // GUISCHEMASCENE_H
