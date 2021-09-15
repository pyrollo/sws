/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "guioutputcombobox.h"
#include "draw/drawnschema.h"
#include "core/coreschema.h"
#include "core/modules/coremoduleoutput.h"
#include "audio/audiofifobuffer.h"

GuiOutputComboBox::GuiOutputComboBox(QWidget *parent):
    QComboBox(parent), mSchema(nullptr), mAudioBuffer(nullptr), mSelectedOutput(nullptr)
{
    insertItem(0, QString("<None>"));
    connect(this, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &GuiOutputComboBox::onIndexChanged);
}
void GuiOutputComboBox::populate()
{
    CoreModuleOutput *selected = mSelectedOutput;
    setCurrentIndex(0);

    for (int index = count(); index > 0; index--)
        removeItem(index);

    if (!mSchema || !mSchema->core())
        return;

    int index = 1;
    for (auto it : mSchema->core()->outputs()) {
        insertItem(index, QString::fromStdString(it.first));
        if (mSchema->core()->output(it.first) == selected)
            setCurrentIndex(index);
        index++;
    }
}

void GuiOutputComboBox::outputsChanged()
{
    populate();
}

void GuiOutputComboBox::setSchema(DrawnSchema *schema)
{
    if (mSchema) {
        disconnect(mSchema, &DrawnSchema::outputsChanged, this, &GuiOutputComboBox::outputsChanged);
    }
    mSchema = schema;
    if (mSchema) {
        connect(mSchema, &DrawnSchema::outputsChanged, this, &GuiOutputComboBox::outputsChanged);
        populate();
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

    if (index) {
        mSelectedOutput = mSchema->core()->output(currentText().toStdString());
        mSchema->core()->connectReadingBuffer(mAudioBuffer, mSelectedOutput->plug());
    } else {
        mSelectedOutput = nullptr;
        mSchema->core()->disconnectReadingBuffer(mAudioBuffer);
    }
}
