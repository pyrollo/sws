#include "coremachine.h"
#include "coremodule.h"
#include "coreschema.h"
#include <chrono>
#include <cmath>

CoreMachine::CoreMachine(CoreSchema *schema, CoreValue stepTime):
    mSchema(schema), mStepTime(stepTime), mThread(nullptr), mRunning(false)
{
}

void CoreMachine::run()
{
    std::chrono::time_point<std::chrono::steady_clock> last, now;
    int steps;
    double nanoHzFrequency = 0.000000001f / mStepTime;

    last = std::chrono::steady_clock::now();

    while (mRunning) {
        now = std::chrono::steady_clock::now();
        steps = int(round(nanoHzFrequency * std::chrono::nanoseconds(now - last).count()));
        last = now;
        while (steps-- > 0) {
            // TODO: Catch exception and stop machine
            mSchema->setTime(mSchema->getTime() + mStepTime);
            mSchema->step();
        }

        // TODO: Manage 10ms period at class level
        std::this_thread::sleep_until(last + std::chrono::milliseconds(10));
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
