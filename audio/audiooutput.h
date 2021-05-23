#ifndef AUDIOOUTPUT_H
#define AUDIOOUTPUT_H
class CoreMachine;

class AudioOutput
{
public:
    AudioOutput(CoreMachine *machine);
protected:
    CoreMachine *mMachine;
};

#endif // AUDIOOUTPUT_H
