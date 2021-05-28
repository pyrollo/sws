#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
#include "core/coremachine.h"

class DrawnSchema;
class AudioFifoBuffer;
class QAudioOutput;
class GuiSchemaScene;

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
    void handleFileNew();
    void handleFileOpen();
    void handleFileSave();
    void handleFileSaveAs();
    void handleFileQuit();
protected:
    Ui::GuiMainWindow *ui;
    DrawnSchema *mSchema;
    CoreMachine mCoreMachine;

    AudioFifoBuffer *mAudioOutputBuffer;
    QAudioOutput *mAudioOutput;

    QString mCurrentFilePath;

    bool changeSchema(DrawnSchema *schema);
};
#endif // GUIMAINWINDOW_H
