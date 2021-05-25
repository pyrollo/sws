#ifndef COREINPUT_H
#define COREINPUT_H
#include "coreplug.h"
#include <unordered_set>

class CoreOutput;
class CoreModule;

class CoreInput : public CorePlug
{
public:
    CoreInput(CoreModule *module, CoreValue defaultValue);
    ~CoreInput();

    CoreValue value() const;

    void listConnectedModules(std::unordered_set<CoreModule *> &list) const;
    bool isUpstream(CoreModule *module) const;
    bool isConnected() const { return mConnectedTo != nullptr; }
    CoreModule *connectedModule() const;
    CoreOutput *connectedOutput() const { return mConnectedTo; }

    // Internal use only
    void halfConnect(CoreOutput *output);
    void halfDisconnect(CoreOutput *output);

protected:
    CoreValue mDefaultValue;
    CoreOutput *mConnectedTo;

};

#endif // COREINPUT_H
