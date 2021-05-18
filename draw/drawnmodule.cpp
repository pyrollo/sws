#include "drawnitem.h"
#include "drawnmodule.h"
#include "drawnschema.h"
#include "drawninput.h"
#include "drawnoutput.h"
#include "../gui/guistyle.h"
#include "../core/coremodule.h"
#include "../core/coreexceptions.h"
#include <QPainter>

DrawnModule::DrawnModule(DrawnSchema *schema, CoreModule *coreModule):
    DrawnItem(schema, 1.0f), mSchema(schema), mCoreModule(coreModule)
{
    setFlags(flags()|ItemIsSelectable|ItemIsMovable);
}

DrawnModule::~DrawnModule() {
    for (auto it : mInputs)
        delete it.second;

    for (auto it : mOutputs)
        delete it.second;

    mSchema->removeModule(this);
    delete mCoreModule;
}

DrawnInput *DrawnModule::newInput(std::string name)
{
    DrawnInput *input = new DrawnInput(this, core()->input(name));
    connect(this, SIGNAL(positionChanged()), input, SIGNAL(positionChanged()));
    mInputs[name] = input;
    return input;
}

DrawnOutput *DrawnModule::newOutput(std::string name)
{
    DrawnOutput *output = new DrawnOutput(this, core()->output(name));
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

void DrawnModule::hightlightInputs()
{
    for (auto it : mInputs)
        if (!it.second->core()->isConnected())
            it.second->setHighlighted(true);
}

void DrawnModule::hightlightOutputs()
{
    for (auto it : mOutputs)
        it.second->setHighlighted(true);
}

void DrawnModule::unHighlightPlugs()
{
    for (auto it : mInputs) {
        it.second->setHighlighted(false);
    }
    for (auto it : mOutputs) {
        it.second->setHighlighted(false);
    }
}

void DrawnModule::setPenAndBrush(QPainter *painter)
{
    if (isSelected()) {
        painter->setPen(GuiStyle::pModuleSelected());
        painter->setBrush(GuiStyle::bModuleSelected());
    } else {
        painter->setPen(GuiStyle::pModule());
        painter->setBrush(GuiStyle::bModule());
    }
}
