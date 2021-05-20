#ifndef DRAWNMODULEFACTORY_H
#define DRAWNMODULEFACTORY_H

#include <functional>
#include <map>
#include <vector>

class DrawnModule;
class DrawnSchema;
class CoreModule;

class DrawnModuleFactory
{
public:
    DrawnModuleFactory();
    DrawnModule *newModule(std::string type, DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);
    std::vector<std::string> listModules();
protected:
    std::map<std::string, std::function<DrawnModule *(DrawnSchema *schema, CoreModule *coreModule)>> mFactories;
};

#endif // DRAWNMODULEFACTORY_H
