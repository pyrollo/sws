#ifndef COREMODULEFACTORY_H
#define COREMODULEFACTORY_H
#include <functional>
#include <map>

class CoreModule;
class CoreSchema;

class CoreModuleFactory
{
public:
    CoreModuleFactory(CoreSchema *schema);
    CoreModule *newModule(std::string type);
protected:
    CoreSchema *mSchema;
    std::map<std::string, std::function<CoreModule *(CoreSchema *schema)>> mFactories;
};

#endif // COREMODULEFACTORY_H
