#ifndef DRAWNMODULEADD_H
#define DRAWNMODULEADD_H
#include "../drawnmodulerectangle.h"
#include <string>

class DrawnSchema;

class DrawnModuleAdd : public DrawnModuleRectangle
{
public:
    DrawnModuleAdd(DrawnSchema *parentSchema, CoreModule *coreModule);
};

#endif // DRAWNMODULEADD_H
