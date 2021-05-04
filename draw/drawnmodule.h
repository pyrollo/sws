#ifndef DRAWNMODULE_H
#define DRAWNMODULE_H
#include "drawnitem.h"
#include "drawninput.h"
#include "drawnoutput.h"
#include <map>
#include <memory>

class DrawSchema;
class DrawnInput;
class DrawnOutput;
class CoreModule;

class DrawnModule : public DrawnItem
{
public:
    DrawnSchema *schema() { return mSchema; }
    CoreModule *core() { return mCoreModule; }

    DrawnInput  *input(std::string name);
    DrawnOutput *output(std::string name);

    void unHighlightPlugs();
    void hightlightInputs();
    void hightlightOutputs();

protected:
    DrawnSchema *mSchema;
    CoreModule *mCoreModule;

    std::map<std::string, std::unique_ptr<DrawnInput>> mInputs;
    std::map<std::string, std::unique_ptr<DrawnOutput>> mOutputs;

    DrawnModule(DrawnSchema *schema, CoreModule *coreModule);

    virtual DrawnInput *newInput(std::string name);
    virtual DrawnOutput *newOutput(std::string name);

};


#endif // GRAPHICMODULE_H
