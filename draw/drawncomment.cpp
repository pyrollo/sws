/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2022 Pierre-Yves Rollo <dev@pyrollo.com>

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

#include "drawncomment.h"
#include "drawnitem.h"
#include "style.h"

#include <QPainter>

DrawnComment::DrawnComment(DrawnSchema *parent):
    DrawnItem("comment", parent)
{
    mText = "Comment";
    mWidth = 10;
    mHeight = 1;
}

void DrawnComment::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QColor color = Style::cForeground();

    if (isSelected())
        color = Style::cForegroundSelected();

    painter->setPen(QPen(color, Qt::SolidPattern));
    painter->setFont(Style::fComment());
    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(boundingRect(), Qt::AlignLeft | Qt::AlignTop, mText);
}

QRectF DrawnComment::boundingRect() const
{
    return QRectF(0.0f, 0.0f, mWidth * Style::sGrid(), mHeight * Style::sGrid());
}

