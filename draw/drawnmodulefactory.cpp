#include "drawnmodulefactory.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduleadd.h"
#include "modules/drawnmodulemultiply.h"

DrawnModuleFactory::DrawnModuleFactory(DrawnSchema *schema) :
    mSchema(schema)
{
    mFactories["constant"] = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleConstant(schema, coreModule); };
    mFactories["add"]      = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleAdd(schema, coreModule); };
    mFactories["multiply"] = [](DrawnSchema *schema, CoreModule *coreModule) { return new DrawnModuleMultiply(schema, coreModule); };
}

DrawnModule *DrawnModuleFactory::newModule(std::string type, CoreModule *coreModule)
{
    return mFactories.at(type)(mSchema, coreModule);
}
