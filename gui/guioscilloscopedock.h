#ifndef GUIOSCILLOSCOPEDOCK_H
#define GUIOSCILLOSCOPEDOCK_H

#include <QDockWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class GuiOscilloscopeDock; }
QT_END_NAMESPACE

class GuiSchemaView;
class DrawnPlug;
class ProbeShemaInteraction;

class GuiOscilloscopeDock : public QDockWidget
{
    Q_OBJECT

    friend ProbeShemaInteraction;

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
    void turnOffProbeButton();
    Ui::GuiOscilloscopeDock *ui;
    GuiSchemaView *mView;
    ProbeShemaInteraction *mProbeInteraction;
};

#endif // GUIOSCILLOSCOPEDOCK_H
