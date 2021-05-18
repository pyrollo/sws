#ifndef COREMODULE_H
#define COREMODULE_H

#include "core.h"
#include "coreinput.h"
#include "coreoutput.h"
#include <map>
#include <vector>
#include <memory>
#include <string>

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

    const std::vector<CoreModule *> inputConnectedModules() const;

protected:
    CoreInput  *newInput(std::string name, CoreValue defaultValue);
    CoreOutput *newOutput(std::string name);

    CoreSchema *mSchema;
    std::map<std::string, std::unique_ptr<CoreInput>> mInputs;
    std::map<std::string, std::unique_ptr<CoreOutput>> mOutputs;
};

#endif // COREMODULE_H
