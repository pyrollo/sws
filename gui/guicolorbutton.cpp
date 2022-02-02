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

#include "guicolorbutton.h"
#include <QPainter>

GuiColorButton::GuiColorButton(QWidget *parent):
        QPushButton(parent)
{
    mColors.push_back(Qt::red);
    mColors.push_back(Qt::green);
    mColors.push_back(Qt::blue);
    mColors.push_back(Qt::yellow);
    mColors.push_back(Qt::magenta);
    mColors.push_back(Qt::cyan);

    mColor = mColors.front();

    // Connect this push button's pressed() signal.
    connect(this, &QPushButton::pressed, this, &GuiColorButton::buttonPressed);
}

GuiColorButton::~GuiColorButton()
{
}

void GuiColorButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);

    QPainter p(this);
    int w = width();
    int h = height();

    p.setPen( QPen( Qt::black, 0, Qt::SolidLine ) );
    p.drawRect(3, 3, w - 7, h - 7);
    p.fillRect(QRect(4, 4, w - 8, h - 8), QBrush(mColor));

}

void GuiColorButton::buttonPressed()
{
    // Find and set to next color
    for (auto it=mColors.begin(); it != mColors.end(); ++it)
    {
        if (*it == mColor) {
            it++;
            if (it == mColors.end())
                mColor = mColors.front();
            else
                mColor = *it;
            break;
        }
    }
    update();
    emit colorChanged(mColor);
}

