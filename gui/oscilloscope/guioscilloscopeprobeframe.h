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

#ifndef GUIOSCILLOSCOPEPROBEFRAME_H
#define GUIOSCILLOSCOPEPROBEFRAME_H

#include <QFrame>

class GuiSchemaView;
class GuiOscilloscopeDisplay;
class GuiOscilloscopeProbe;
class ProbeShemaInteraction;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiOscilloscopeProbeFrame; }
QT_END_NAMESPACE

class GuiOscilloscopeProbeFrame : public QFrame
{
    Q_OBJECT
    friend ProbeShemaInteraction;

public:
    GuiOscilloscopeProbeFrame(GuiOscilloscopeDisplay *parent, GuiSchemaView *view);
    ~GuiOscilloscopeProbeFrame();

    GuiOscilloscopeProbe *getProbe() { return mProbe; }

public slots:
    void handleEnable(bool checked);
    void handleChangeColor();
    void handleChangePlug(bool checked);
    void handleDelete();
    void handleScaleDialValueDelta(int delta);
    void handleOffsetDialValueDelta(int delta);

protected:
    void turnOffChangeProbeButton();
    void refreshScaleAndOffset();

private:
    Ui::GuiOscilloscopeProbeFrame *ui;
    GuiOscilloscopeDisplay *mDisplay;
    GuiSchemaView *mView;

    ProbeShemaInteraction *mProbeInteraction;
    GuiOscilloscopeProbe *mProbe;

    int mScaleExp;
    int mScaleValue;
    int mOffsetValue;
};

#endif // GUIOSCILLOSCOPEPROBEFRAME_H
