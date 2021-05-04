#include "drawnmoduleadd.h"
#include "../../core/coreschema.h"
#include <QPainter>

DrawnModuleAdd::DrawnModuleAdd(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 2.0f, 2.0f)
{
    newInput("operand1", left, 0.5f);
    newInput("operand2", left, 1.5f);
    newOutput("result", right, 1.0f);
}
