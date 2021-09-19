#ifndef GUIOSCILLOSCOPEDOCK_H
#define GUIOSCILLOSCOPEDOCK_H

#include <QDockWidget>
#include "prober.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GuiOscilloscopeDock; }
QT_END_NAMESPACE

class GuiSchemaView;
class DrawnPlug;

class GuiOscilloscopeDock : public QDockWidget, Prober
{
    Q_OBJECT

public:
    GuiOscilloscopeDock(GuiSchemaView *view);
    GuiOscilloscopeDock(const QString &title, GuiSchemaView *view);
    ~GuiOscilloscopeDock();
    void closeEvent(QCloseEvent *event);
    void setProbe(DrawnPlug *plug);
public slots:
    void handleSchemaChange();
    void handleProbe(bool checked);
protected:
    Ui::GuiOscilloscopeDock *ui;
    GuiSchemaView *mView;
};

#endif // GUIOSCILLOSCOPEDOCK_H
