#include "fileserializer.h"
#include "draw/drawnschema.h"
#include "draw/drawnmodule.h"
#include "core/coreschema.h"
#include "core/coremodule.h"
#include "core/coreinput.h"
#include "core/coreoutput.h"

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

        QDomElement xgui = xdoc.createElement("gui");
        xmodule.appendChild(xgui);
        xgui.setAttribute("x", module->pos().x());
        xgui.setAttribute("y", module->pos().y());
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
