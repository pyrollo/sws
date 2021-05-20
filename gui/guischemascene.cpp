#include "guischemascene.h"
#include "guistyle.h"
#include "../draw/drawnschema.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QTextStream>

GuiSchemaScene::GuiSchemaScene():
    QGraphicsScene(-1000, -1000, 2000, 2000), mSchema(nullptr), mProbeWidget(nullptr)
{
    setBackgroundBrush(GuiStyle::bBackground());
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

void GuiSchemaScene::setProbeWidget(QLabel *widget)
{
    mProbeWidget = widget;
    clearProbe();
}

void GuiSchemaScene::setProbe(QString label, CoreValue value)
{
    if (!mProbeWidget)
        return;

    QString text;
    QTextStream(&text) << label << ": " << value;
    mProbeWidget->setText(text);
}

void GuiSchemaScene::clearProbe()
{
    if (!mProbeWidget)
        return;

    mProbeWidget->setText("");
}
