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

#ifndef DRAWNMODULE_H
#define DRAWNMODULE_H

#include "drawnitem.h"
#include "style.h"

#include <map>

class DrawSchema;
class DrawnInput;
class DrawnOutput;
class CoreModule;
class QPainter;
class QMouseEvent;
class QSvgRenderer;

class DrawnModuleIcon;

class DrawnModule : public DrawnItem
{
    Q_OBJECT
public:
    virtual ~DrawnModule();
    CoreModule *core() override { return mCoreModule; }

    virtual DrawnInput  *input(std::string name);
    virtual DrawnOutput *output(std::string name);

    void unHighlightPlugs();
    void highlightPluggableInputs();
    void highlightProbeableInputs();
    void highlightPluggableOutputs();
    void highlightProbeableOutputs();

protected:
    CoreModule *mCoreModule;

    std::map<std::string, DrawnInput *> mInputs;
    std::map<std::string, DrawnOutput *> mOutputs;

    DrawnModule(std::string type, DrawnSchema *schema = nullptr);

    virtual DrawnInput *newInput(std::string name);
    virtual DrawnOutput *newOutput(std::string name);

    void setStyle(QPainter *painter, QColor bgColor, QColor fgColor);
    virtual void setStyle(QPainter *painter) { setStyle(painter,  Style::cBackground(), Style::cForeground()); }
};


#endif // GRAPHICMODULE_H
