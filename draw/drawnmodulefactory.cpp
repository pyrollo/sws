#include "drawnmodulefactory.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "modules/drawnmoduleadd.h"
#include "modules/drawnmodulemultiply.h"

DrawnModuleFactory::DrawnModuleFactory()
{
    mFactories["constant"] = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleConstant(schema, coreModule); };
    mFactories["input"]    = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleInput(schema, coreModule); };
    mFactories["output"]   = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleOutput(schema, coreModule); };
    mFactories["add"]      = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleAdd(schema, coreModule); };
    mFactories["multiply"] = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleMultiply(schema, coreModule); };
}

DrawnModule *DrawnModuleFactory::newModule(std::string type, DrawnSchema *schema, CoreModule *coreModule)
{
    return mFactories.at(type)(schema, coreModule);
}

std::vector<std::string> DrawnModuleFactory::listModules()
{
    std::vector<std::string> result;
    for (auto it: mFactories)
        result.push_back(it.first);

    return result;
}
