#ifndef GUIMAINWINDOW_H
#define GUIMAINWINDOW_H

#include <QMainWindow>
class CoreSchema;

QT_BEGIN_NAMESPACE
namespace Ui { class GuiMainWindow; }
QT_END_NAMESPACE

class GuiMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    GuiMainWindow(QWidget *parent = nullptr);
    ~GuiMainWindow();
    void handleButtonStep();

private:
    Ui::GuiMainWindow *ui;
    CoreSchema *mCoreSchema;
};
#endif // GUIMAINWINDOW_H
