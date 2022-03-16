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
#include "drawnicon.h"

#include "core/coremodule.h"
#include "core/coreexceptions.h"
#include "core/coremodulefactory.h"

#include <QPainter>

DrawnModule::DrawnModule(std::string type, DrawnSchema *schema):
    DrawnItem(type, schema), mCoreModule(nullptr)
{
    if (mSchema) {
        setFlags(flags()|ItemIsMovable);

        // TODO: Missing some mechanism to ensure certain modules have their core stuff created
        try {
            mCoreModule = mSchema->core()->newModule(type);
        } catch (CoreUnknownTypeEx &) {}
    }
}

DrawnModule::~DrawnModule()
{
    for (auto it : mInputs)
        delete it.second;

    for (auto it : mOutputs)
        delete it.second;

    if (mCoreModule)
        delete mCoreModule;
}

void DrawnModule::setStyle(QPainter *painter, QColor bgColor, QColor fgColor)
{
    QColor background = bgColor;
    QColor foreground = fgColor;

    if (isSelected()) {
        background = Style::cBackgroundSelected();
        foreground = Style::cForegroundSelected();
    }

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QBrush(foreground), Style::wModule()));
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

//    connect(this, SIGNAL(positionChanged()), input, SIGNAL(positionChanged()));
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

//    connect(this, SIGNAL(positionChanged()), output, SIGNAL(positionChanged()));
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
