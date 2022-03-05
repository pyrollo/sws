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

#ifndef GUIOSCILLOSCOPEDOCK_H
#define GUIOSCILLOSCOPEDOCK_H

#include <QDockWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GuiOscilloscopeDock; }
QT_END_NAMESPACE

class GuiSchemaView;

class GuiOscilloscopeDock : public QDockWidget
{
    Q_OBJECT

public:
    explicit GuiOscilloscopeDock(GuiSchemaView *view, int sampleRate);
    ~GuiOscilloscopeDock();
    void closeEvent(QCloseEvent *);

public slots:
    void handleSchemaChange();
    void handleAddProbe();
    void handleTimeValueChanged(int);

protected:
    Ui::GuiOscilloscopeDock *ui;
    GuiSchemaView *mView;
    int mSampleRate;
};

#endif // GUIOSCILLOSCOPEDOCK_H
