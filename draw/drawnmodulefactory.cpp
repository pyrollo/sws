#include "drawnmodulefactory.h"
#include "modules/drawnmoduleadd.h"
class CoreModule;

DrawnModuleFactory::DrawnModuleFactory(DrawnSchema *schema) :
    mSchema(schema)
{
    mFactories["add"] = [](DrawnSchema *schema, CoreModule *coreModule)      { return new DrawnModuleAdd(schema, coreModule); };
}

DrawnModule *DrawnModuleFactory::newModule(std::string type, CoreModule *coreModule)
{
    return mFactories.at(type)(mSchema, coreModule);
}
