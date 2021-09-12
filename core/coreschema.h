#ifndef CORESCHEMA_H
#define CORESCHEMA_H
#include "value/value.h"
#include <string>
#include <map>
#include <vector>
#include <unordered_set>
#include <mutex>

class CoreModuleFactory;
class CoreModule;
class CoreInput;
class CoreOutput;
class CorePlug;
class CoreModuleOutput;
class CoreModuleInput;
class CoreSampleBuffer;

class CoreSchema
{
public:
    CoreSchema();

    CoreModule *newModule(std::string type);
    void addModule(CoreModule *module);
    void removeModule(CoreModule *module);
    void unprepare() { mPrepared = false; }
    void step();

    void connect(CoreInput *input, CoreOutput *output);
    void disconnect(CoreInput *input, CoreOutput *output);

    Value getTime() { return mTime; }
    void setTime(Value time) { mTime = time; }

    void setInputName(CoreModuleInput *module, std::string name);
    const std::map<std::string, CoreModuleInput *> &inputs() { return mInputs; }
    CoreModuleInput *input(std::string name) { return mInputs.at(name); }

    void setOutputName(CoreModuleOutput *module, std::string name);
    const std::map<std::string, CoreModuleOutput *> &outputs() { return mOutputs; }
    CoreModuleOutput *output(std::string name) { return mOutputs.at(name); }

    const std::unordered_set<CoreModule *> &modules() { return mModules; }

    void connectReadingBuffer(CoreSampleBuffer *buffer, CorePlug *plug);
    void disconnectReadingBuffer(CoreSampleBuffer *buffer);

protected:
    CoreModuleFactory *mModuleFactory;

    std::unordered_set<CoreModule *> mModules;
    std::map<std::string, CoreModuleInput *> mInputs;
    std::map<std::string, CoreModuleOutput *> mOutputs;

    Value mTime;

    std::vector<CoreModule *> mScheduledModules;
    bool mPrepared;
    std::mutex mStepMutex;

    bool queuable(CoreModule *module, std::unordered_set<CoreModule *> &unscheduledModules);

    std::mutex mBuffersMutex;
    std::map<CoreSampleBuffer *, std::pair<CoreModule *, CorePlug *>> mReadingBuffers;

};

#endif // CORESCHEMA_H
