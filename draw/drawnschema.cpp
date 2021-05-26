#include "drawnschema.h"
#include "drawnmodule.h"
#include "drawnmodulefactory.h"
#include "../core/coreschema.h"
#include "../core/coreinput.h"
#include "../core/coreoutput.h"
#include "../core/coremodule.h"

#include <QPainter>

DrawnSchema::DrawnSchema() :
    DrawnItem(nullptr), mCoreSchema()
{
    mModuleFactory = new DrawnModuleFactory();
}

DrawnSchema::~DrawnSchema()
{
    while (mModules.size())
        delete *(mModules.begin());

    delete mModuleFactory;
}

void DrawnSchema::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    (void)(painter); (void)(option); (void)(widget);
}

QRectF DrawnSchema::boundingRect() const
{
    return QRectF(-1000, -1000, 2000, 2000);
}

DrawnModule *DrawnSchema::newModule(std::string type)
{
    CoreModule *coreModule = core()->newModule(type);
    DrawnModule *module = mModuleFactory->newModule(type, this, coreModule);
    if (module)
        mModules.insert(module);
    return module;
}

// Should be called only from module destructor
void DrawnSchema::removeModule(DrawnModule *module) {
    core()->removeModule(module->core());
    mModules.erase(module);
}

void DrawnSchema::highlightConnectable(DrawnPlug * plug)
{
    std::unordered_set<CoreModule *> list;

    DrawnInput *input = dynamic_cast<DrawnInput *>(plug);
    if (input) {
        input->core()->module()->listDownstream(list);
        for (auto module : mModules)
            if (list.find(module->core()) == list.end())
                module->hightlightOutputs();
    }

    DrawnOutput *output = dynamic_cast<DrawnOutput *>(plug);
    if (output) {
        output->core()->module()->listUpstream(list);
        for (auto module : mModules)
             if (list.find(module->core()) == list.end())
                module->hightlightInputs();
    }
}

void DrawnSchema::unHighlight()
{
    for (auto module : mModules)
        module->unHighlightPlugs();
}

