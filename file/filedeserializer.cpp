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

#include "filedeserializer.h"
#include "draw/drawnschema.h"
#include "draw/drawnmodule.h"
#include "draw/drawnwire.h"
#include "draw/drawncomment.h"
#include "draw/style.h"
#include "draw/modules/drawnmoduleinput.h"
#include "draw/modules/drawnmoduleoutput.h"
#include "core/coreschema.h"
#include "core/coremodule.h"
#include "core/modules/coremoduleconstant.h"
//#include "core/modules/coremoduleinput.h"
//#include "core/modules/coremoduleoutput.h"
#include "value/string.h"

#include <QtXml>


FileDeserializer::FileDeserializer(const QByteArray &data)
{
    // TODO: Add validation againts schema

    if (!mDocument.setContent(data, true))
        throw FileBadFileFormat();
}

void FileDeserializer::setPositionFromAttributes(QDomElement &xelement, DrawnItem *item)
{
    item->setPos(
        Style::sGrid() * xelement.attribute("x").toInt(),
        Style::sGrid() * xelement.attribute("y").toInt()
    );
}

DrawnSchema *FileDeserializer::deserializeToDrawnSchema()
{
    DrawnSchema *schema = new DrawnSchema();
    std::map<QString, DrawnItem *> drawnItems;
    QDomNodeList xfound;

    QDomElement xroot = mDocument.documentElement();
    QDomElement xschema = xroot.firstChildElement("schema");
    if (xschema.isNull())
        throw FileBadFileFormat();

    // Core
    // ----

    QDomElement xcore = xschema.firstChildElement("core");
    if (xcore.isNull())
        throw FileBadFileFormat();

    for (int index = 0; index < xcore.childNodes().count(); index++) {
        QDomNode xnode = xcore.childNodes().at(index);
        if (xnode.isElement()) {
            QDomElement xelement = xnode.toElement();
            if (xelement.tagName() == "module") {
                DrawnItem *item = schema->newItem(xelement.attribute("type").toStdString());
                drawnItems[xelement.attribute("id")] = item;

                // Some module type specific stuff
                if (item->getType() == "constant")
                    ((CoreModuleConstant *)item->core())->setValue(valueFromQString(xelement.attribute("value")));
            }
            if (xelement.tagName() == "connect") {
                QDomElement xfrom = xelement.elementsByTagName("from").at(0).toElement();
                QDomElement xto = xelement.elementsByTagName("to").at(0).toElement();

                try {
                    DrawnModule *from = (DrawnModule *)drawnItems.at(xfrom.attribute("module"));
                    DrawnModule *to = (DrawnModule *)drawnItems.at(xto.attribute("module"));
                    DrawnWire *wire = new DrawnWire(schema);
                    wire->connectTo(from->output(xfrom.attribute("output").toStdString()));
                    wire->connectTo(to->input(xto.attribute("input").toStdString()));
                } catch(std::exception &) {
                    throw FileBadFileFormat();
                }
            }
        }
    }

    // Draw
    // ----

    QDomElement xdraw = xschema.firstChildElement("draw");
    if (xdraw.isNull())
        throw FileBadFileFormat();

    for (int index = 0; index < xcore.childNodes().count(); index++) {
        QDomNode xnode = xcore.childNodes().at(index);
        if (xnode.isElement()) {
            QDomElement xelement = xnode.toElement();
            if (xelement.tagName() == "place-module") {
                DrawnItem *item = drawnItems.at(xelement.attribute("module"));
                setPositionFromAttributes(xelement, item);
            }

            if (xelement.tagName() == "comment") {
                DrawnComment *comment = (DrawnComment *)schema->newItem("comment");
                comment->setText(xelement.text());
                setPositionFromAttributes(xelement, comment);
            }
        }
    }

    return schema;
}

