#include "guioutputcombobox.h"
#include "draw/drawnschema.h"
#include "core/coreschema.h"

GuiOutputComboBox::GuiOutputComboBox(QWidget *parent):
    QComboBox(parent), mSchema(nullptr)
{
    insertItem(0, QString("<None>"));
}

void GuiOutputComboBox::outputsChanged()
{
    if (!mSchema || !mSchema->core())
        return;

    for (int index = count(); index > 0; index--)
        removeItem(index);

    int index = 1;
    for (auto it : mSchema->core()->outputs())
        insertItem(index++, QString::fromStdString(it.first));

}

void GuiOutputComboBox::setSchema(DrawnSchema *schema)
{
    if (mSchema) {
        disconnect(mSchema, &DrawnSchema::outputsChanged, this, &GuiOutputComboBox::outputsChanged);
    }
    mSchema = schema;
    if (mSchema) {
        connect(mSchema, &DrawnSchema::outputsChanged, this, &GuiOutputComboBox::outputsChanged);
        outputsChanged();
    }
}
