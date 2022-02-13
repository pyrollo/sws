#include "guioscilloscopeprobeframe.h"
#include "ui_guioscilloscopeprobeframe.h"

#include "guioscilloscopedisplay.h"
#include "guioscilloscopeprobe.h"

#include "gui/guischemaview.h"

#include "draw/drawnschema.h"
#include "draw/drawnschemainteraction.h"
#include "draw/drawnplug.h"

#include <QGraphicsSceneMouseEvent>


// Interaction with schema view when selecting what to probe
class ProbeShemaInteraction : public DrawnSchemaInteraction {
public:

    ProbeShemaInteraction(DrawnSchema *schema, GuiOscilloscopeProbeFrame *probeFrame):
        DrawnSchemaInteraction(schema), mProbeFrame(probeFrame)
    {}

    ~ProbeShemaInteraction()
    {}

    void init() override
    {
        mSchema->highlightProbeable();
    }

    void terminate() override
    {
        mSchema->unHighlight();
        delete this;
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e, DrawnItem *item) override
    {
        DrawnPlug *plug = dynamic_cast<DrawnPlug *>(item);
        if (!plug)
            return;

        mProbeFrame->getProbe()->probePlug(plug);
        mProbeFrame->turnOffChangeProbeButton(); // This will end interaction with schema
        e->accept();
    }

protected:
    GuiOscilloscopeProbeFrame *mProbeFrame;
};

// GuiOscilloscopeProbeFrame class

GuiOscilloscopeProbeFrame::GuiOscilloscopeProbeFrame(GuiOscilloscopeDisplay *parent, GuiSchemaView *view):
        QFrame(parent), ui(new Ui::GuiOscilloscopeProbeFrame), mDisplay(parent),
        mView(view), mProbeInteraction(nullptr)
{
    ui->setupUi(this);

    mProbe = new GuiOscilloscopeProbe();

    mDisplay->addProbe(mProbe);

    connect(ui->enableButton, &QAbstractButton::toggled, this, &GuiOscilloscopeProbeFrame::handleEnable);
    connect(ui->changeColorButton, &QAbstractButton::pressed, this, &GuiOscilloscopeProbeFrame::handleChangeColor);
    connect(ui->changePlugButton, &QAbstractButton::toggled, this, &GuiOscilloscopeProbeFrame::handleChangePlug);
    connect(ui->deleteButton, &QAbstractButton::pressed, this, &GuiOscilloscopeProbeFrame::handleDelete);

    handleEnable(ui->enableButton->checkState());
    handleChangeColor();
}

GuiOscilloscopeProbeFrame::~GuiOscilloscopeProbeFrame()
{
    if (mProbeInteraction)
        // TODO: Sure there is a schema ? -> Interaction should be aware of schema
        mView->schema()->endInteraction();

    mDisplay->removeProbe(mProbe);
    delete mProbe;

    delete ui;
}

void GuiOscilloscopeProbeFrame::turnOffChangeProbeButton()
{
    ui->changePlugButton->setChecked(false);
    mView->schema()->endInteraction();
    mProbeInteraction = nullptr;
}

void GuiOscilloscopeProbeFrame::handleEnable(bool checked)
{
    mProbe->setEnabled(checked);
}

void GuiOscilloscopeProbeFrame::handleChangeColor()
{
    mProbe->setColor(ui->changeColorButton->getColor());
}

void GuiOscilloscopeProbeFrame::handleChangePlug(bool checked) {
    // Three cases: no schema, schema probing, schema not probing...

    if (mView->schema()) {
        if (checked) {
            mProbeInteraction = new ProbeShemaInteraction(mView->schema(), this);
            mView->schema()->startInteraction(mProbeInteraction);
        } else {
            if (mProbeInteraction) {
                mView->schema()->endInteraction();
                mProbeInteraction = nullptr;
            }
        }
    }
}

void GuiOscilloscopeProbeFrame::handleDelete()
{
    delete this;
}


