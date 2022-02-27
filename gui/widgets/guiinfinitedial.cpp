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

#include "guiinfinitedial.h"
#include <QApplication>

GuiInfiniteDial::GuiInfiniteDial(QWidget *parent):
    QDial(parent), mLastValue(0)
{
    setValue(0);
    setWrapping(true);
    connect(this, QOverload<int>::of(&QDial::valueChanged), this, &GuiInfiniteDial::handleValueChanged);

}
void GuiInfiniteDial::handleValueChanged(int value)
{
    int delta = value - mLastValue;
    mLastValue = value;

    if (delta * 2 > maximum())
        delta -= maximum();
    if (delta * 2 < -maximum())
        delta += maximum();

    emit valueDelta(delta);
}

QSize GuiInfiniteDial::sizeHint() const
{
    return QSize(30, 30).expandedTo(QApplication::globalStrut());
}

QSize GuiInfiniteDial::minimumSizeHint() const
{
    return QSize(30, 30).expandedTo(QApplication::globalStrut());
}
