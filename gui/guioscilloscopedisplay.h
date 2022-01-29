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

#ifndef GUIOSCILLOSCOPEDISPLAY_H
#define GUIOSCILLOSCOPEDISPLAY_H

#include <QWidget>

class OscilloscopeBuffer;
class DrawnPlug;

class GuiOscilloscopeDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GuiOscilloscopeDisplay(QWidget *parent = nullptr);
    ~GuiOscilloscopeDisplay();
    OscilloscopeBuffer *getSampleBuffer() { return mSampleBuffer; }

    void probePlug(DrawnPlug *plug);

protected:
    void paintEvent(QPaintEvent *);

    OscilloscopeBuffer *mSampleBuffer;
    int *mIntBuffer;
    DrawnPlug *mProbedPlug;

    QTimer *mTimer;
signals:
};

#endif // GUIOSCILLOSCOPEDISPLAY_H
