#include "guischemascene.h"
#include "guistyle.h"
#include "draw/drawnschema.h"
#include <QPainter>
#include <QKeyEvent>
#include <QLabel>
#include <QTextStream>

GuiSchemaScene::GuiSchemaScene(QObject *parent):
    QGraphicsScene(-10, -10, 20, 20, parent), mSchema(nullptr), mProbeWidget(nullptr)
{
    setBackgroundBrush(GuiStyle::bBackground());
}

void GuiSchemaScene::keyPressEvent(QKeyEvent *event)
{
    if (!mSchema)
        return;

    if (event->key() == Qt::Key_Delete)
        mSchema->deleteSelected();
}

void GuiSchemaScene::setSchema(DrawnSchema *schema)
{
    if (schema == mSchema)
        return;

    if (mSchema)
        removeItem(mSchema);

    mSchema = schema;
    if (mSchema)
        addItem(mSchema);

    update();
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
