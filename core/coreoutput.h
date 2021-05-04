#ifndef COREOUTPUT_H
#define COREOUTPUT_H

#include <unordered_set>
#include "coreplug.h"

class CoreInput;

class CoreOutput : public CorePlug
{
public:
    CoreOutput(CoreModule *module);
    ~CoreOutput();

    CoreValue value() const { return mValue; }
    void setValue(CoreValue value) { mValue = value; }

    void listConnectedModules(std::unordered_set<CoreModule *> &list);
    bool isDownstream(CoreModule *module);

    void connect(CoreInput *input);
    void disconnect(CoreInput *input);

    bool isConnected() { return mConnectedTo.size() > 0; }

protected:
    CoreValue mValue;
    std::unordered_set<CoreInput *> mConnectedTo;
};

#endif // COREOUTPUT_H
