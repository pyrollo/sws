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

#ifndef GUIOUTPUTCOMBOBOX_H
#define GUIOUTPUTCOMBOBOX_H
#include <QComboBox>

class DrawnSchema;
class CoreModuleOutput;
class OscilloscopeBuffer;

// Sound stuff that should go elsewhere later
class AudioFifoBuffer;

class GuiOutputComboBox : public QComboBox
{
public:
    GuiOutputComboBox(QWidget *parent = nullptr);
    void setSchema(DrawnSchema *schema);
    void setAudioBuffer(AudioFifoBuffer *buffer);
    void setOscilloscopeBuffer(OscilloscopeBuffer *buffer);
public slots:
    void outputsChanged();
    void onIndexChanged(int index);

protected:
    DrawnSchema *mSchema;

    // Sound stuff that should go elsewhere later
    AudioFifoBuffer *mAudioBuffer;

    //
    OscilloscopeBuffer *mOscilloscopeBuffer;

    // Last selected output
    CoreModuleOutput *mSelectedOutput;

    void populate();
    void connectBuffer();
};

#endif // GUIOUTPUTCOMBOBOX_H
