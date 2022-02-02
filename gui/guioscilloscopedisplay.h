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
#include <set>

class DisplayBuffer;
class OscilloscopeBuffer;
class OscilloscopeSampleInt;
class DrawnPlug;
class GuiOscilloscopeProbeFrame;

class GuiOscilloscopeDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit GuiOscilloscopeDisplay(QWidget *parent = nullptr);
    ~GuiOscilloscopeDisplay();

    void addProbe(GuiOscilloscopeProbeFrame* probe) { probes.insert(probe); }
    void removeProbe(GuiOscilloscopeProbeFrame* probe) { probes.erase(probe); }

signals:
    void resized(QResizeEvent *);

private:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void resizeBuffer();

    OscilloscopeBuffer *mSampleBuffer;
    DrawnPlug *mProbedPlug;

    QTimer *mTimer;
    float mRefreshRate;

    std::set<GuiOscilloscopeProbeFrame *> probes;
signals:
};

#endif // GUIOSCILLOSCOPEDISPLAY_H
