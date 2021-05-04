#ifndef DRAWNMODULEFACTORY_H
#define DRAWNMODULEFACTORY_H

#include <functional>
#include <map>

class DrawnModule;
class DrawnSchema;
class CoreModule;

class DrawnModuleFactory
{
public:
    DrawnModuleFactory(DrawnSchema *schema);
    DrawnModule *newModule(std::string type, CoreModule *coreModule);
protected:
    DrawnSchema *mSchema;
    std::map<std::string, std::function<DrawnModule *(DrawnSchema *schema, CoreModule *coreModule)>> mFactories;
};

#endif // DRAWNMODULEFACTORY_H
