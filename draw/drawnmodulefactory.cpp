#include "drawnmodulefactory.h"
#include "modules/drawnmoduleconstant.h"
#include "modules/drawnmoduletime.h"
#include "modules/drawnmoduleinput.h"
#include "modules/drawnmoduleoutput.h"
#include "modules/drawnmoduleclip.h"
#include "modules/drawnmoduleadd.h"
#include "modules/drawnmodulemultiply.h"

#define ADDMODULECLASS(CLASS) \
    mFactories[CLASS::mType] = [](DrawnSchema *schema, CoreModule *coreModule) { return new CLASS(schema, coreModule); };

DrawnModuleFactory::DrawnModuleFactory()
{
    ADDMODULECLASS(DrawnModuleConstant)
    ADDMODULECLASS(DrawnModuleTime)
    ADDMODULECLASS(DrawnModuleInput)
    ADDMODULECLASS(DrawnModuleOutput)
    ADDMODULECLASS(DrawnModuleClip)
    ADDMODULECLASS(DrawnModuleAdd)
    ADDMODULECLASS(DrawnModuleMultiply)
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
