#include "coremachine.h"
#include "coremodule.h"
#include "coreschema.h"
#include <chrono>

CoreMachine::CoreMachine(CoreSchema *schema, CoreValue stepTime):
    mSchema(schema), mStepTime(stepTime), mThread(nullptr), mRunning(false)
{
}

void CoreMachine::run()
{
    while (mRunning) {
        // TODO: Catch exception and stop machine
        mSchema->setTime(mSchema->getTime() + mStepTime);
        mSchema->step();
        // TODO: Improve this to a regulated duration
        std::this_thread::sleep_for(std::chrono::milliseconds(int(mStepTime*1000)));
    }
}

void CoreMachine::start()
{
    std::lock_guard<std::mutex> lock(mThreadControlMutex);

    if (!mSchema)
        return;

    mRunning = true;
    mThread = new std::thread(&CoreMachine::run, this);
}

void CoreMachine::stop()
{
    std::lock_guard<std::mutex> lock(mThreadControlMutex);

    if (!mRunning)
        return;

    mRunning = false;
    mThread->join();
    delete mThread;
    mThread = nullptr;
}
