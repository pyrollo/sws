#ifndef GUISCHEMASCENE_H
#define GUISCHEMASCENE_H
#include <QGraphicsScene>
#include "core/core.h"

class DrawnSchema;
class QLabel;

class GuiSchemaScene : public QGraphicsScene
{
public:
    GuiSchemaScene();
    void keyPressEvent(QKeyEvent *keyEvent);

    void removeSchema();
    void setSchema(DrawnSchema *schema);
    DrawnSchema *schema() const { return mSchema; }

    void setProbeWidget(QLabel *widget);
    void setProbe(QString label, CoreValue value);
    void clearProbe();
protected:
    DrawnSchema *mSchema;
    QLabel *mProbeWidget;
};

#endif // GUISCHEMASCENE_H
