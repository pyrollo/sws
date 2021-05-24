#include "audiooutput.h"
#include "core/coremachine.h"
#include <QAudioDeviceInfo>

AudioOutput::AudioOutput(CoreMachine *machine):
    mMachine(machine)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
    QAudioFormat format = device.preferredFormat();

    printf("Prefered format:\n\tSample rate=%d\n\tSample size=%d\n\tChannels=%d", format.sampleRate(), format.sampleSize(), format.channelCount());

    printf("\n\nSupported rates:");
    for (auto rate : device.supportedSampleRates())
        printf("%d, ", rate);
    printf("\n\nSupported sample sizes: ");
    for (auto size : device.supportedSampleSizes())
        printf("%d, ", size);

    fflush(stdout);
//    QAudioDeviceInfo::isFormatSupported(const QAudioFormat &settings) const;

}
