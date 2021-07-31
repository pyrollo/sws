#ifndef COREMACHINE_H
#define COREMACHINE_H
#include "value/value.h"
#include <thread>
#include <mutex>
#include <time.h>

class CoreModule;
class CoreSchema;

class CoreMachine
{
public:
    CoreMachine();

    void setSchema(CoreSchema *schema);
    void setStepTime(Value stepTime);

    void start();
    void stop();
    bool isRunning() { return mRunning; }

protected:
    CoreSchema *mSchema;
    Value mStepTime;

    std::thread *mThread;
    bool mRunning;
    std::mutex mThreadControlMutex;

    void run();
};

#endif // COREMACHINE_H
