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

#include "fileserializer.h"
#include "draw/drawnschema.h"
#include "draw/drawnmodule.h"
#include "core/coreschema.h"
#include "core/coremodule.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"
#include "core/modules/coremoduleconstant.h"
#include "value/string.h"

#include <QtXml>

FileSerializer::FileSerializer(DrawnSchema *schema):
    mSchema(schema)
{
}

QString FileSerializer::serialize()
{
    QDomDocument xdoc("xxx");
    QDomElement xschema = xdoc.createElement("schema");
    xdoc.appendChild(xschema);

    // Arbitrary order modules to give them ids
    std::map<DrawnModule *, int> drawnModules;
    std::map<CoreModule *, int> coreModules;

    // Map core and drawn modules to generated IDs for this file
    int id = 1;
    for (auto module: mSchema->modules()) {
        drawnModules[module] = id;
        coreModules[module->core()] = id;
        id++;
    }

    // Create module elements
    for (auto module: mSchema->modules()) {
        QDomElement xmodule = xdoc.createElement("module");
        xschema.appendChild(xmodule);
        xmodule.setAttribute("id", QString::number(drawnModules[module]));
        xmodule.setAttribute("type", QString::fromStdString(module->getType()));

        // Some module type specific stuff
        if (strcmp(module->getType(), "constant") == 0) {
            QDomElement xinternal = xdoc.createElement("internal");
            xmodule.appendChild(xinternal);
            xinternal.setAttribute("value", valueToQString(
                    ((CoreModuleConstant *)module->core())->getValue()));
        }

        // GUI specific stuff
        QDomElement xgui = xdoc.createElement("gui");
        xmodule.appendChild(xgui);

        // setAttributes(float) looks buggy : it uses locale decimal separator instead of dot and adds extra digits
        QString buffer;
        buffer.setNum(module->pos().x());
        xgui.setAttribute("x", buffer);
        buffer.setNum(module->pos().y());
        xgui.setAttribute("y", buffer);
    }

    // Create connect elements
    for (auto toModule: mSchema->core()->modules()) {
        for (auto it: toModule->inputs()) {
            CoreOutput *fromOutput = it.second->connectedOutput();
            if (!fromOutput)
                continue;
            CoreModule *fromModule = fromOutput->module();
            std::string fromOutputName = "";
            for (auto it: fromModule->outputs())
                if (it.second == fromOutput)
                    fromOutputName = it.first;

            QDomElement xconnect = xdoc.createElement("connect");
            xschema.appendChild(xconnect);
            QDomElement xfrom = xdoc.createElement("from");
            xconnect.appendChild(xfrom);
            QDomElement xto = xdoc.createElement("to");
            xconnect.appendChild(xto);
            xfrom.setAttribute("module", QString::number(coreModules[fromModule]));
            xfrom.setAttribute("output", QString::fromStdString(fromOutputName));
            xto.setAttribute("module", QString::number(coreModules[toModule]));
            xto.setAttribute("input", QString::fromStdString(it.first));
        }
    }

    // Create input elements
    for (auto it: mSchema->core()->inputs()) {
        QDomElement xinput = xdoc.createElement("input");
        xschema.appendChild(xinput);
        xinput.setAttribute("module", coreModules[(CoreModule *)it.second]);
        xinput.setAttribute("name", QString::fromStdString(it.first));
    }

    // Create output elements
    for (auto it: mSchema->core()->outputs()) {
        QDomElement xinput = xdoc.createElement("output");
        xschema.appendChild(xinput);
        xinput.setAttribute("module", coreModules[(CoreModule *)it.second]);
        xinput.setAttribute("name", QString::fromStdString(it.first));
    }

    return xdoc.toString();
}
