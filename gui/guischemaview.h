#ifndef GUISCHEMAVIEW_H
#define GUISCHEMAVIEW_H
#include <QGraphicsView>

class GuiSchemaView : public QGraphicsView
{
public:
    GuiSchemaView(QWidget *parent);

    void wheelEvent(QWheelEvent* event);
};

#endif // GUISCHEMAVIEW_H
