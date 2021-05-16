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
    mSchema->removeModule(this);
    delete mCoreModule;
}

DrawnInput *DrawnModule::newInput(std::string name)
{
    DrawnInput *input = new DrawnInput(this, core()->input(name));
    connect(this, SIGNAL(positionChanged()), input, SIGNAL(positionChanged()));
    mInputs[name] = std::unique_ptr<DrawnInput>(input);
    return input;
}

DrawnOutput *DrawnModule::newOutput(std::string name)
{
    DrawnOutput *output = new DrawnOutput(this, core()->output(name));
    connect(this, SIGNAL(positionChanged()), output, SIGNAL(positionChanged()));
    mOutputs[name] = std::unique_ptr<DrawnOutput>(output);
    return output;
}

DrawnInput *DrawnModule::input(std::string name)
{
    try {
        return mInputs.at(name).get();
    } catch(const std::out_of_range&) {
        throw CoreUnknownInputEx(name);
    }
}

DrawnOutput *DrawnModule::output(std::string name)
{
    try {
        return mOutputs.at(name).get();
    } catch(const std::out_of_range&) {
        throw CoreUnknownOutputEx(name);
    }
}

void DrawnModule::hightlightInputs()
{
    for (auto it = mInputs.begin(); it != mInputs.end(); it++) {
        it->second->setHighlighted(true);
    }
}

void DrawnModule::hightlightOutputs()
{
    for (auto it = mOutputs.begin(); it != mOutputs.end(); it++) {
        it->second->setHighlighted(true);
    }
}

void DrawnModule::unHighlightPlugs()
{
    for (auto it = mInputs.begin(); it != mInputs.end(); it++) {
        it->second->setHighlighted(false);
    }
    for (auto it = mOutputs.begin(); it != mOutputs.end(); it++) {
        it->second->setHighlighted(false);
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
