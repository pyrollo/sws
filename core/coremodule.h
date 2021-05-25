#ifndef COREMODULE_H
#define COREMODULE_H
#include "core.h"
#include "coreinput.h"
#include "coreoutput.h"
#include <map>
#include <vector>
#include <memory>
#include <string>
#include <mutex>

class CoreSchema;

class CoreModule
{
public:
    CoreModule(CoreSchema *schema);
    virtual ~CoreModule();

    CoreSchema *schema() const { return mSchema; }

    virtual bool interconnected() const { return true; }
    virtual void step() = 0;

    CoreInput  *input(std::string name) const;
    CoreOutput *output(std::string name) const;

    void listUpstream(std::unordered_set<CoreModule *> &list);
    void listDownstream(std::unordered_set<CoreModule *> &list);

    bool isUpstream(CoreModule *module) const;
    bool isDownstream(CoreModule *module) const;

    const std::map<std::string, CoreInput *> inputs() const { return mInputs; }
    const std::map<std::string, CoreOutput *> outputs() const { return mOutputs; }

protected:
    CoreInput  *newInput(std::string name, CoreValue defaultValue);
    CoreOutput *newOutput(std::string name);

    CoreSchema *mSchema;
    std::map<std::string, CoreInput *> mInputs;
    std::map<std::string, CoreOutput *> mOutputs;
};

#endif // COREMODULE_H
