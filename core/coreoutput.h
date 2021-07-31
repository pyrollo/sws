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

    Value value() const { return mValue; }
    void setValue(Value value) { mValue = value; }

    void listConnectedModules(std::unordered_set<CoreModule *> &list);
    bool isDownstream(CoreModule *module) const;

    // Internal use only
    void halfConnect(CoreInput *input);
    void halfDisconnect(CoreInput *input);

protected:
    Value mValue;
    std::unordered_set<CoreInput *> mConnectedTo;
};

#endif // COREOUTPUT_H
