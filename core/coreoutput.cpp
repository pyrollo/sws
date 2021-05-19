#include "coreoutput.h"
#include "coreinput.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"

CoreOutput::CoreOutput(CoreModule *module) :
    CorePlug(module), mValue(0)
{
}

CoreOutput::~CoreOutput()
{
    for (const auto& connectedTo: mConnectedTo)
        mModule->schema()->disconnect(connectedTo, this);
}

void CoreOutput::listConnectedModules(std::unordered_set<CoreModule *> &list)
{
    for (const auto& connectedTo: mConnectedTo)
        connectedTo->module()->listDownstream(list);
}

bool CoreOutput::isDownstream(CoreModule *module) const
{
    for (const auto& connectedTo: mConnectedTo)
        if (connectedTo->module()->isDownstream(module))
            return true;

    return false;
}

void CoreOutput::halfConnect(CoreInput *input)
{
    auto result = mConnectedTo.insert(input);
    if (!result.second)
        throw CoreAlreadyConnectedEx();
}

void CoreOutput::halfDisconnect(CoreInput *input)
{
    if (!mConnectedTo.erase(input))
        throw CoreNotConnectedEx();
}

