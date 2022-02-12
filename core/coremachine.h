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
    Value getStepTime() { return mStepTime; }

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
