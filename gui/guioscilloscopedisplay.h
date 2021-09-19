#ifndef GUIOSCILLOSCOPEDISPLAY_H
#define GUIOSCILLOSCOPEDISPLAY_H

#include <QWidget>

class OscilloscopeBuffer;

class GuiOscilloscopeDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GuiOscilloscopeDisplay(QWidget *parent = nullptr);
    ~GuiOscilloscopeDisplay();
    OscilloscopeBuffer *getSampleBuffer() { return mSampleBuffer; }
protected:
    void paintEvent(QPaintEvent *);

    OscilloscopeBuffer *mSampleBuffer;
    int *mIntBuffer;

    QTimer *mTimer;
signals:
};

#endif // GUIOSCILLOSCOPEDISPLAY_H
