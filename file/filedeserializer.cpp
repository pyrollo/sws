#include "filedeserializer.h"
#include "draw/drawnschema.h"
#include "draw/drawnmodule.h"
#include "draw/drawnwire.h"
#include "draw/modules/drawnmoduleinput.h"
#include "draw/modules/drawnmoduleoutput.h"
#include "core/coreschema.h"
#include "core/coremodule.h"
#include "core/modules/coremoduleconstant.h"
//#include "core/modules/coremoduleinput.h"
//#include "core/modules/coremoduleoutput.h"

#include <QtXml>


FileDeserializer::FileDeserializer(const QByteArray &data)
{
    // TODO: Add validation againts schema

    if (!mDocument.setContent(data, true))
        throw FileBadFileFormat();
}

DrawnSchema *FileDeserializer::deserializeToDrawnSchema()
{
    DrawnSchema *schema = new DrawnSchema();
    std::map<QString, DrawnModule *> drawnModules;
    QDomNodeList xfound;

    QDomElement xroot = mDocument.documentElement();
    for (int index = 0; index < xroot.childNodes().count(); index++) {
        QDomNode xnode = xroot.childNodes().at(index);
        if (xnode.isElement()) {
            QDomElement xelement = xnode.toElement();
            if (xelement.tagName() == "module") {
                DrawnModule *module = schema->newModule(xelement.attribute("type").toStdString());
                drawnModules[xelement.attribute("id")] = module;

                // Some module type specific stuff
                xfound = xelement.elementsByTagName("internal");
                if (xfound.count()) {
                    if (strcmp(module->getType(), "constant") == 0) {
                        QDomElement xinternal = xfound.at(0).toElement();
                        ((CoreModuleConstant *)module->core())->setValue(xinternal.attribute("value").toFloat());
                    }
                }
                // GUI Specific stuff
                xfound = xelement.elementsByTagName("gui");
                if (xfound.count()) {
                    QDomElement xgui = xfound.at(0).toElement();
                    module->moveBy(xgui.attribute("x").toFloat(), xgui.attribute("y").toFloat());
                }
            }
            if (xelement.tagName() == "connect") {
                QDomElement xfrom = xelement.elementsByTagName("from").at(0).toElement();
                QDomElement xto = xelement.elementsByTagName("to").at(0).toElement();

                try {
                    DrawnModule *from = drawnModules.at(xfrom.attribute("module"));
                    DrawnModule *to   = drawnModules.at(xto.attribute("module"));
                    DrawnWire *wire = new DrawnWire(schema);
                    wire->connectTo(from->output(xfrom.attribute("output").toStdString()));
                    wire->connectTo(to->input(xto.attribute("input").toStdString()));
                } catch(std::exception &e) {
                    throw FileBadFileFormat();
                }
            }
            if (xelement.tagName() == "input") {
                try {
                    DrawnModuleInput *module = (DrawnModuleInput *)drawnModules.at(xelement.attribute("module"));
                    module->setName(xelement.attribute("name"));
                } catch(std::exception &e) {
                    throw FileBadFileFormat();
                }
            }
            if (xelement.tagName() == "output") {
                try {
                    DrawnModuleOutput *module = (DrawnModuleOutput *)drawnModules.at(xelement.attribute("module"));
                    module->setName(xelement.attribute("name"));
                } catch(std::exception &e) {
                    throw FileBadFileFormat();
                }

            }
        }
    }

    return schema;
}

