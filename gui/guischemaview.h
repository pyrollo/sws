#ifndef GUISCHEMAVIEW_H
#define GUISCHEMAVIEW_H
#include "guischemascene.h"
#include <QGraphicsView>

class DrawnSchema;

class GuiSchemaView : public QGraphicsView
{
public:
    GuiSchemaView(QWidget *parent = nullptr);

    void wheelEvent(QWheelEvent* event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);

    void setSchema(DrawnSchema *schema) { mScene.setSchema(schema); }
    void setProbeWidget(QLabel *widget) { mScene.setProbeWidget(widget); }

protected:
    GuiSchemaScene mScene;
};

#endif // GUISCHEMAVIEW_H
