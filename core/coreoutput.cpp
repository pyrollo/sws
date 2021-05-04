#include "coreoutput.h"
#include "coreinput.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"

CoreOutput::CoreOutput(CoreModule *module) :
    CorePlug(module)
{
}

CoreOutput::~CoreOutput()
{
    for (const auto& connectedTo: mConnectedTo)
        disconnect(connectedTo);
}

void CoreOutput::listConnectedModules(std::unordered_set<CoreModule *> &list)
{
    for (const auto& connectedTo: mConnectedTo)
        connectedTo->module()->listDownstream(list);
}

bool CoreOutput::isDownstream(CoreModule *module)
{
    for (const auto& connectedTo: mConnectedTo)
        if (connectedTo->module()->isDownstream(module))
            return true;

    return false;
}

void CoreOutput::connect(CoreInput *input)
{
    if (mConnectedTo.find(input) != mConnectedTo.end())
        return;

    if (module()->isUpstream(input->module()))
        throw CoreLoopConnectionEx();

    mConnectedTo.insert(input);
    input->connect(this);
    mModule->schema()->unprepare();
}

void CoreOutput::disconnect(CoreInput *input)
{
    if (mConnectedTo.erase(input)) {
        input->disconnect(this);
        mModule->schema()->unprepare();
    }
}

