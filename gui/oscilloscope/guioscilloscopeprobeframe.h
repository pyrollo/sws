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
#include <QColor>
#include "value/value.h"

class GuiOscilloscopeDisplay;
class GuiSchemaView;
class OscilloscopeBuffer;
class DisplayBuffer;
class ProbeShemaInteraction;
class DrawnPlug;
class QResizeEvent;
class QImage;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiOscilloscopeProbeFrame; }
QT_END_NAMESPACE

struct GuiOscilloscopeProbeSample
{
    int min;
    int max;
};

class GuiOscilloscopeProbeFrame : public QFrame
{
    friend ProbeShemaInteraction;

public:
    GuiOscilloscopeProbeFrame(GuiOscilloscopeDisplay *parent, GuiSchemaView *view);
    ~GuiOscilloscopeProbeFrame();

    void drawTo(QImage *image);

public slots:
    void handleEnable(bool checked);
    void handleChangeColor();
    void handleChangePlug(bool checked);
    void handleDelete();
    void displayResized(QResizeEvent *e);
protected:
    void setProbedPlug(DrawnPlug *plug);
    void turnOffChangeProbeButton();

private:
    Ui::GuiOscilloscopeProbeFrame *ui;
    GuiOscilloscopeDisplay *mDisplay;
    GuiSchemaView *mView;

    ProbeShemaInteraction *mProbeInteraction;
    DrawnPlug *mProbedPlug;
    OscilloscopeBuffer *mSampleBuffer;

    DisplayBuffer *mDisplayBuffer;

    QColor mColor;
    Value mScale;
    Value mOffset;

    // Draw variables
    int mLast;
    float mPeriod;
    float mSampleRatio;
    GuiOscilloscopeProbeSample mCurrentSample;

};

#endif // GUIOSCILLOSCOPEPROBEFRAME_H
