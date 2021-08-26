#ifndef GUIOSCILLOSCOPE_H
#define GUIOSCILLOSCOPE_H

#include <QWidget>

class OscilloscopeBuffer;

class GuiOscilloscope : public QWidget
{
    Q_OBJECT
public:
    explicit GuiOscilloscope(QWidget *parent = nullptr);
    ~GuiOscilloscope();
    OscilloscopeBuffer *getSampleBuffer() { return mSampleBuffer; }
protected:
    void paintEvent(QPaintEvent *);

    OscilloscopeBuffer *mSampleBuffer;
    int *mIntBuffer;

    QTimer *mTimer;
signals:
};

#endif // GUIOSCILLOSCOPE_H
