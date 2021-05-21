#ifndef GUISCHEMAVIEW_H
#define GUISCHEMAVIEW_H
#include <QGraphicsView>

class GuiSchemaScene;

class GuiSchemaView : public QGraphicsView
{
public:
    GuiSchemaView(QWidget *parent);

    void setScene(GuiSchemaScene *scene);

    void wheelEvent(QWheelEvent* event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

protected:
    GuiSchemaScene *mSchemaScene;
};

#endif // GUISCHEMAVIEW_H
