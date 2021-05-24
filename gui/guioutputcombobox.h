#ifndef GUIOUTPUTCOMBOBOX_H
#define GUIOUTPUTCOMBOBOX_H
#include <QComboBox>
class DrawnSchema;

// Sound stuff that should go elsewhere later
class AudioFifoBuffer;

class GuiOutputComboBox : public QComboBox
{
public:
    GuiOutputComboBox(QWidget *parent = nullptr);
    void setSchema(DrawnSchema *schema);
    void setAudioBuffer(AudioFifoBuffer *buffer);
public slots:
    void outputsChanged();
    void onIndexChanged(int index);

protected:
    DrawnSchema *mSchema;

    // Sound stuff that should go elsewhere later
    AudioFifoBuffer *mAudioBuffer;
};

#endif // GUIOUTPUTCOMBOBOX_H
