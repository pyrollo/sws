#include "guioutputcombobox.h"
#include "draw/drawnschema.h"
#include "core/coreschema.h"
#include "core/modules/coremoduleoutput.h"
#include "audio/audiofifobuffer.h"

GuiOutputComboBox::GuiOutputComboBox(QWidget *parent):
    QComboBox(parent), mSchema(nullptr), mAudioBuffer(nullptr)
{
    insertItem(0, QString("<None>"));
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GuiOutputComboBox::onIndexChanged);
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

void GuiOutputComboBox::setAudioBuffer(AudioFifoBuffer *buffer)
{
    mAudioBuffer = buffer;
    if (!mAudioBuffer || !mSchema)
        setCurrentIndex(0);
}


void GuiOutputComboBox::onIndexChanged(int index)
{
    if ((!mAudioBuffer || !mSchema) && index != 0) {
        setCurrentIndex(0);
        return;
    }

    if (index)
        mSchema->core()->output(currentText().toStdString())->writeToBuffer(mAudioBuffer);
    else
        mAudioBuffer->setWriter(nullptr);
}
