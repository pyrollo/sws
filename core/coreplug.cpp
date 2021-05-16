#include "coreplug.h"
#include "coremodule.h"
#include "coreexceptions.h"

CorePlug::CorePlug(CoreModule *module) :
    mModule(module)
{

}

void CorePlug::checkConnection(CorePlug *plug)
{
    if (!module()->schema() || !plug->module()->schema())
        throw CoreNoSchemaEx();

    if (module()->schema() != plug->module()->schema())
        throw CoreNotSameSchemaEx();
}
