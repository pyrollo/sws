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
#include "draw/drawnitem.h"
#include "draw/style.h"
#include "draw/modules/drawnmoduleerror.h"
#include "draw/drawncomment.h"

#include "core/coreschema.h"
#include "core/coremodule.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"
#include "core/modules/coremoduleconstant.h"

#include "value/string.h"

FileSerializer::FileSerializer(DrawnSchema *schema):
    mSchema(schema)
{
}

bool FileSerializer::serializable()
{
    // Disable serialization of schema with errors
    // (wont work well and will lose module internal data)
    // TODO: Should error modules hold any module data?
    for (auto item: mSchema->items())
        if (dynamic_cast<DrawnModuleError *>(item))
            return false;
    return true;
}

void FileSerializer::setPositionAttributes(QDomElement &xelement, DrawnItem *item)
{
    xelement.setAttribute("x", int(item->pos().x() / Style::sGrid()));
    xelement.setAttribute("y", int(item->pos().y() / Style::sGrid()));
}

QString FileSerializer::serialize()
{
    if (!serializable())
        throw(new FileSerializerErrorModules());

    QDomDocument xdoc("sws-schema");
    QDomElement xschema = xdoc.createElement("schema");
    xdoc.appendChild(xschema);

    // Arbitrary order modules to give them ids
    std::map<DrawnItem *, int> drawnModules;
    std::map<CoreModule *, int> coreModules;

    // Map core and drawn modules to generated IDs for this file
    int id = 1;
    for (auto item: mSchema->items()) {
        DrawnModule *module = dynamic_cast<DrawnModule *>(item);
        if (module && module->core()) {
            drawnModules[item] = id;
            coreModules[module->core()] = id;
        }
        id++;
    }

    // Core part
    // ---------

    QDomElement xcore = xdoc.createElement("core");
    xschema.appendChild(xcore);

    // Modules
    for (auto module: drawnModules) {
        QDomElement xmodule = xdoc.createElement("module");
        xcore.appendChild(xmodule);
        xmodule.setAttribute("id", QString::number(module.second));
        xmodule.setAttribute("type", QString::fromStdString(module.first->getType()));

        // Some module type specific stuff
        if (module.first->getType() == "constant")
            xmodule.setAttribute("value", valueToQString(
                ((CoreModuleConstant *)module.first->core())->getValue()));
    }

    // Connections
    for (auto module: coreModules) {
        for (auto input: module.first->inputs()) {
            CoreOutput *fromOutput = input.second->connectedOutput();
            if (!fromOutput)
                continue;

            std::string fromOutputName = "";
            for (auto output: fromOutput->module()->outputs())
                if (output.second == fromOutput)
                    fromOutputName = output.first;

            QDomElement xconnect = xdoc.createElement("connect");
            xcore.appendChild(xconnect);

            QDomElement xfrom = xdoc.createElement("from");
            xconnect.appendChild(xfrom);
            xfrom.setAttribute("module", QString::number(coreModules[fromOutput->module()]));
            xfrom.setAttribute("output", QString::fromStdString(fromOutputName));

            QDomElement xto = xdoc.createElement("to");
            xconnect.appendChild(xto);
            xto.setAttribute("module", QString::number(module.second));
            xto.setAttribute("input", QString::fromStdString(input.first));
        }
    }

    // Draw Part
    // ---------

    QDomElement xdraw = xdoc.createElement("draw");
    xschema.appendChild(xdraw);

    // Modules
    for (auto module : drawnModules) {
        QDomElement xmodule = xdoc.createElement("place-module");
        xdraw.appendChild(xmodule);
        xmodule.setAttribute("id", QString::number(module.second));
        setPositionAttributes(xmodule, module.first);
    }

    // Decorations
    for (auto item: mSchema->items()) {
        if (drawnModules.find(item) != drawnModules.end())
            continue;

        DrawnComment *comment = dynamic_cast<DrawnComment *>(item);
        if (comment) {
            QDomElement xcomment = xdoc.createElement("comment");
            xdraw.appendChild(xcomment);
            setPositionAttributes(xcomment, comment);
            xcomment.appendChild(xdoc.createTextNode(comment->getText()));
        }
    }

    return xdoc.toString();
}
