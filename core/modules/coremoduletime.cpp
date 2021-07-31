#include "coremoduletime.h"
#include "core/coreoutput.h"
#include "core/coreschema.h"

CoreModuleTime::CoreModuleTime(CoreSchema *schema) :
    CoreModule(schema)
{
    mOutputTime =newOutput("time");
}

void CoreModuleTime::step()
{
    if (mSchema)
        mOutputTime->setValue(mSchema->getTime());
}
