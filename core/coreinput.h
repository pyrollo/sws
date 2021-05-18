#ifndef COREINPUT_H
#define COREINPUT_H

#include "coreplug.h"
#include <unordered_set>

class CoreOutput;

class CoreInput : public CorePlug
{
public:
    CoreInput(CoreModule *module, CoreValue defaultValue);
    ~CoreInput();

    CoreValue value() const;

    void listConnectedModules(std::unordered_set<CoreModule *> &list);
    bool isUpstream(CoreModule *module);

    void connect(CoreOutput *input);
    void disconnect(CoreOutput *input);

    bool isConnected() const { return mConnectedTo != nullptr; }

protected:
    CoreValue mDefaultValue;
    CoreOutput *mConnectedTo;
};

#endif // COREINPUT_H
