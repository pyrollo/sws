#ifndef COREMACHINE_H
#define COREMACHINE_H
#include "core.h"
#include <thread>
#include <mutex>
#include <time.h>

class CoreModule;
class CoreSchema;

class CoreMachine
{
public:
    CoreMachine(CoreSchema *schema, CoreValue stepTime);
    void start();
    void stop();
    bool isRunning() { return mRunning; }

protected:
    CoreSchema *mSchema;
    CoreValue mStepTime;

    std::thread *mThread;
    bool mRunning;
    std::mutex mThreadControlMutex;

    void run();
};

#endif // COREMACHINE_H
