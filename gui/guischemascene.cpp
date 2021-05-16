#include "guischemascene.h"
#include "guistyle.h"
#include "../draw/drawnschema.h"
#include <QPainter>
#include <QKeyEvent>

GuiSchemaScene::GuiSchemaScene():
    QGraphicsScene(-1000, -1000, 2000, 2000), mSchema(nullptr)
{
}

void GuiSchemaScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QRectF visible = rect.intersected(sceneRect());
    painter->fillRect(visible, GuiStyle::bBackground());
}

void GuiSchemaScene::keyPressEvent(QKeyEvent *event)
{
    if (!mSchema)
        return;

    if (event->key() == Qt::Key_Backspace)
        mSchema->deleteSelected();
}

void GuiSchemaScene::removeSchema()
{
    if (!mSchema)
        return;

    removeItem(mSchema);
    mSchema = nullptr;
}

void GuiSchemaScene::setSchema(DrawnSchema *schema)
{
    removeSchema();

    if (!schema)
        return;

    mSchema = schema;
    addItem(mSchema);
}
