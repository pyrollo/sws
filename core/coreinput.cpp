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
        mModule->schema()->disconnect(this, mConnectedTo);
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

void CoreInput::halfConnect(CoreOutput *output)
{
    if (mConnectedTo != nullptr)
        throw CoreAlreadyConnectedEx();

    mConnectedTo = output;
}

void CoreInput::halfDisconnect(CoreOutput *output)
{
    if (mConnectedTo != output)
        throw CoreNotConnectedEx();

    mConnectedTo = nullptr;
}

