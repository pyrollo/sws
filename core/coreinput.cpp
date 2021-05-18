#include "coreinput.h"
#include "coreoutput.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"

CoreInput::CoreInput(CoreModule *module, CoreValue defaultValue) :
    CorePlug(module), mDefaultValue(defaultValue), mConnectedTo(nullptr)
{
}

CoreInput::~CoreInput()
{
    if (mConnectedTo)
        disconnect(mConnectedTo);
}

CoreValue CoreInput::value() const {
    if (mConnectedTo)
        return mConnectedTo->value();
    else
        return mDefaultValue;
}

void CoreInput::listConnectedModules(std::unordered_set<CoreModule *> &list) const
{
    if (mConnectedTo)
        mConnectedTo->module()->listUpstream(list);
}

bool CoreInput::isUpstream(CoreModule *module) const
{
    if (mConnectedTo)
        return mConnectedTo->module()->isUpstream(module);

    return false;
}

void CoreInput::connect(CoreOutput *output)
{
    if (mConnectedTo == output)
        return;

    if (mConnectedTo)
        throw CoreAlreadyConnectedEx();

    if (module()->isDownstream(output->module()))
        throw CoreLoopConnectionEx();

    mConnectedTo = output;
    output->connect(this);
    mModule->schema()->unprepare();
}

void CoreInput::disconnect(CoreOutput *output)
{
    if (mConnectedTo == output) {
        mConnectedTo = nullptr;
        output->disconnect(this);
        mModule->schema()->unprepare();
    }
}

