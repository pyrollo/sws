#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
class CoreSchema;
class CoreMachine;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiMainWindow; }
QT_END_NAMESPACE

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuiMainWindow(QWidget *parent = nullptr);
    ~GuiMainWindow();
    void handleButtonStartStop();

    void updateInputsList();
    void updateOutputsList();
private:
    Ui::GuiMainWindow *ui;
    CoreSchema *mCoreSchema;
    CoreMachine *mCoreMachine;
};
#endif // GUIMAINWINDOW_H
