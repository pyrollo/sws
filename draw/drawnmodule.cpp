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

#include "drawnmodule.h"
#include "drawnitem.h"
#include "drawnschema.h"
#include "drawninput.h"
#include "drawnoutput.h"
#include "gui/guistyle.h"

#include "core/coremodule.h"
#include "core/coreexceptions.h"

#include <QSvgRenderer>
#include <QPainter>
#include <QGraphicsEffect>

class DrawnModuleIconEffect : public QGraphicsEffect
{
public:
    DrawnModuleIconEffect(QObject *parent = nullptr):
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

class DrawnModuleIcon: public QGraphicsItem
{
public:
    DrawnModuleIcon(DrawnModule *parent, const QString &filename):
        QGraphicsItem(parent), mRenderer(filename)
    {
        setAcceptedMouseButtons(Qt::NoButton);
        mEffect = new DrawnModuleIconEffect();
        setGraphicsEffect(mEffect); // Takes ownership
    }

    ~DrawnModuleIcon()
    {}

    QRectF boundingRect() const
    {
        return QRectF(0.3f, 0.3f, 1.4f, 1.4f);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
    {
        mRenderer.render(painter, boundingRect());
    }

    void setForeground(QColor color) { mEffect->setForeground(color); }
    void setBackground(QColor color) { mEffect->setBackground(color); }

protected:
    QSvgRenderer mRenderer;
    DrawnModuleIconEffect *mEffect;
};

DrawnModule::DrawnModule(DrawnSchema *schema, CoreModule *coreModule):
    DrawnItem(schema, 1.0f), mCoreModule(coreModule), mIcon(nullptr)
{
    if (mSchema)
        setFlags(flags()|ItemIsSelectable|ItemIsMovable);
    else
        setFlags(flags()|ItemIsSelectable);
}

DrawnModule::~DrawnModule() {
    if (mSchema)
        mSchema->removeModule(this);

    if (mIcon)
        delete mIcon;

    for (auto it : mInputs)
        delete it.second;

    for (auto it : mOutputs)
        delete it.second;

    if (mCoreModule)
        delete mCoreModule;
}

void DrawnModule::setIconSvgFile(const QString &filename)
{
    if (mIcon)
        delete mIcon;

    mIcon = new DrawnModuleIcon(this, filename);
}

void DrawnModule::setStyle(QPainter *painter)
{
    QColor background = GuiStyle::cBackground();
    QColor foreground = GuiStyle::cForeground();

    if (isSelected()) {
        background = GuiStyle::cBackgroundSelected();
        foreground = GuiStyle::cForegroundSelected();
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QBrush(foreground), GuiStyle::wModule()));
    painter->setBrush(QBrush(background));

    if (mIcon) {
        mIcon->setBackground(background);
        mIcon->setForeground(foreground);
    }
}

DrawnInput *DrawnModule::newInput(std::string name)
{
    DrawnInput *input;
    if (mCoreModule)
        input = new DrawnInput(this, mCoreModule->input(name));
    else
        input = new DrawnInput(this);

    connect(this, SIGNAL(positionChanged()), input, SIGNAL(positionChanged()));
    mInputs[name] = input;
    return input;
}

DrawnOutput *DrawnModule::newOutput(std::string name)
{
    DrawnOutput *output;
    if (mCoreModule)
        output = new DrawnOutput(this, mCoreModule->output(name));
    else
        output = new DrawnOutput(this);

    connect(this, SIGNAL(positionChanged()), output, SIGNAL(positionChanged()));
    mOutputs[name] = output;
    return output;
}

DrawnInput *DrawnModule::input(std::string name)
{
    try {
        return mInputs.at(name);
    } catch(const std::out_of_range&) {
        throw CoreUnknownInputEx(name);
    }
}

DrawnOutput *DrawnModule::output(std::string name)
{
    try {
        return mOutputs.at(name);
    } catch(const std::out_of_range&) {
        throw CoreUnknownOutputEx(name);
    }
}

void DrawnModule::highlightPluggableInputs()
{
    if (mCoreModule)
        for (auto it : mInputs)
            if (it.second->pluggable())
                it.second->setHighlighted(true);
}

void DrawnModule::highlightProbeableInputs()
{
    if (mCoreModule)
        for (auto it : mInputs)
            it.second->setHighlighted(true);
}

void DrawnModule::highlightPluggableOutputs()
{
    if (mCoreModule)
        for (auto it : mOutputs)
            if (it.second->pluggable())
                it.second->setHighlighted(true);
}

void DrawnModule::highlightProbeableOutputs()
{
    if (mCoreModule)
        for (auto it : mOutputs)
            it.second->setHighlighted(true);
}

void DrawnModule::unHighlightPlugs()
{
    if (mCoreModule) {
        for (auto it : mInputs) {
            it.second->setHighlighted(false);
            it.second->setConnecting(false);
        }
        for (auto it : mOutputs) {
            it.second->setHighlighted(false);
            it.second->setConnecting(false);
        }
    }
}
