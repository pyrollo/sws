#include "coremodulefactory.h"
#include "coreexceptions.h"
#include "modules/coremoduleadd.h"
#include "modules/coremoduleconstant.h"
#include "modules/coremoduleinput.h"
#include "modules/coremoduleoutput.h"

class CoreSchema;

CoreModuleFactory::CoreModuleFactory(CoreSchema *schema) :
    mSchema(schema)
{
    mFactories["add"] = [](CoreSchema *schema)      { return new CoreModuleAdd(schema); };
    mFactories["constant"] = [](CoreSchema *schema) { return new CoreModuleConstant(schema); };
    mFactories["input"] = [](CoreSchema *schema)    { return new CoreModuleInput(schema); };
    mFactories["output"] = [](CoreSchema *schema)   { return new CoreModuleOutput(schema); };
}

CoreModule *CoreModuleFactory::newModule(std::string type)
{
    try {
        return mFactories.at(type)(mSchema);
    } catch(const std::out_of_range&) {
        throw CoreUnknownTypeEx(type);
    }
}
