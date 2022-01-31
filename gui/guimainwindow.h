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

#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
#include "core/coremachine.h"

class QSettings;
class DrawnSchema;
class AudioFifoBuffer;
class QAudioOutput;
class GuiSchemaScene;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiMainWindow; }
QT_END_NAMESPACE

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuiMainWindow(QSettings *settings, QWidget *parent = nullptr);
    ~GuiMainWindow();

    bool changeSchema(DrawnSchema *schema);
    DrawnSchema *getSchema() { return mSchema; }

signals:
    void schemaChanged(DrawnSchema *schema);

public slots:
    void handleOscilloscope();

protected:
    Ui::GuiMainWindow *ui;
    QSettings *mSettings;
    DrawnSchema *mSchema;
    CoreMachine mCoreMachine;

    AudioFifoBuffer *mAudioOutputBuffer;
    QAudioOutput *mAudioOutput;

    QString mCurrentFilePath;

};
#endif // GUIMAINWINDOW_H
