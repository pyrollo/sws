/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include "coremachine.h"
#include "coremodule.h"
#include "coreschema.h"
#include "coreexceptions.h"
#include <chrono>
#include <cmath>

CoreMachine::CoreMachine():
    mSchema(nullptr), mStepTime(1.0), mThread(nullptr), mRunning(false)
{
}

void CoreMachine::setStepTime(Value stepTime)
{
    std::lock_guard<std::mutex> lock(mThreadControlMutex);

    if (mRunning)
        throw CoreMachinIsRunningEx();

    mStepTime = stepTime;
}

void CoreMachine::setSchema(CoreSchema *schema)
{
    std::lock_guard<std::mutex> lock(mThreadControlMutex);

    if (mRunning)
        throw CoreMachinIsRunningEx();

    mSchema = schema;
}

void CoreMachine::run()
{
    std::chrono::time_point<std::chrono::steady_clock> last, now;
    int steps;
    double nanoHzFrequency = 0.000000001f / mStepTime.toDouble();

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
