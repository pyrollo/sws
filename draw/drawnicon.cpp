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

#include "drawnicon.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QGraphicsEffect>
#include <QGraphicsItem>

class DrawnIconEffect : public QGraphicsEffect
{
public:
    DrawnIconEffect(QObject *parent = nullptr):
        QGraphicsEffect(parent), mBackgroundColor(Qt::white), mForegroundColor(Qt::black)
    {}

    void setForeground(QColor color) { mForegroundColor = color; }
    void setBackground(QColor color) { mBackgroundColor = color; }

    void draw(QPainter *painter) override {
        painter->save();
        QPoint offset;
        QPixmap pixmap;

        if (sourceIsPixmap()) {
            pixmap = sourcePixmap(Qt::LogicalCoordinates, &offset);
        } else {
            pixmap = sourcePixmap(Qt::DeviceCoordinates, &offset);
            painter->setWorldTransform(QTransform());
        }

        int oR = mForegroundColor.red();
        int oG = mForegroundColor.green();
        int oB = mForegroundColor.blue();

        int mR = mBackgroundColor.red() - oR;
        int mG = mBackgroundColor.green() - oG;
        int mB = mBackgroundColor.blue() - oB;

        QImage image = pixmap.toImage();

        unsigned int *data = (unsigned int *)image.bits();

        int pixels = image.width() * image.height();
        for (int i = 0; i < pixels; ++i) {
            int a = qAlpha(data[i]);
            int v = qGray(data[i]);
            data[i] = qPremultiply(qRgba(oR + mR * v / 255, oG + mG * v / 255, oB + mB * v / 255, a));
        }

        painter->drawImage(offset, image);
        painter->restore();
    }

private:
    QColor mBackgroundColor;
    QColor mForegroundColor;
};

DrawnIcon::DrawnIcon(QGraphicsItem *parent, const QString &filename):
    QGraphicsItem(parent), mRenderer(filename)
{
    setAcceptedMouseButtons(Qt::NoButton);
    mEffect = new DrawnIconEffect();
    setGraphicsEffect(mEffect); // Takes ownership
}

DrawnIcon::~DrawnIcon()
{}

QRectF DrawnIcon::boundingRect() const
{
    const float size = 1.4f;
    return QRectF(-size * 0.5f, -size * 0.5f, size, size);
}

void DrawnIcon::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    mRenderer.render(painter, boundingRect());
}

void DrawnIcon::setForeground(QColor color)
{
    mEffect->setForeground(color);
}

void DrawnIcon::setBackground(QColor color)
{
    mEffect->setBackground(color);
}
