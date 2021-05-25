#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
class CoreSchema;
class CoreMachine;
class DrawnSchema;
class AudioFifoBuffer;
class QAudioOutput;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiMainWindow; }
QT_END_NAMESPACE

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuiMainWindow(QWidget *parent = nullptr);
    ~GuiMainWindow();
public slots:
    void handleButtonStartStop();
    void handleFileNew();
    void handleFileOpen();
    void handleFileSave();
    void handleFileSaveAs();
    void handleFileQuit();
private:
    Ui::GuiMainWindow *ui;
    DrawnSchema *mSchema;
    CoreSchema *mCoreSchema;
    CoreMachine *mCoreMachine;
    AudioFifoBuffer *mAudioOutputBuffer;
    QAudioOutput *mAudioOutput;

    QString mCurrentFilePath;
};
#endif // GUIMAINWINDOW_H
