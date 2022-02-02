#include "guioscilloscopeprobeframe.h"
#include "ui_guioscilloscopeprobeframe.h"

#include "guioscilloscopedisplay.h"
#include "guischemaview.h"

#include "draw/drawnschema.h"
#include "draw/drawnschemainteraction.h"
#include "draw/drawnplug.h"

#include "core/coresamplebuffer.h"
#include "utils/resizeablerollingbuffer.h"
#include "utils/rollingbuffer.h"

#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>
#include <QImage>

// Display buffer
// TODO: Should be resizeable and rewindable
class DisplayBuffer : public RollingBuffer<int>
{
public:
    DisplayBuffer(size_t size): RollingBuffer<int>(size) {}
};

// Oscilloscope sample buffer
class OscilloscopeBuffer : public ResizeableRollingBuffer<Value>, public CoreSampleBuffer
{
public:
    OscilloscopeBuffer(): ResizeableRollingBuffer<Value>() {}

    void writeSample(Value sample) override { push(sample); }
    Value readSample() override { return Value(.0f); } // Nothing to read here
};

// Interaction with schema view when selecting what to probe
class ProbeShemaInteraction : public DrawnSchemaInteraction {
public:

    ProbeShemaInteraction(DrawnSchema *schema, GuiOscilloscopeProbeFrame *probeWidget):
        DrawnSchemaInteraction(schema), mProbeWidget(probeWidget)
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

        mProbeWidget->setProbedPlug(plug);
        mProbeWidget->turnOffChangeProbeButton(); // This will end interaction with schema
        e->accept();
    }

protected:
    GuiOscilloscopeProbeFrame *mProbeWidget;
};

// GuiOscilloscopeProbeFrame class

GuiOscilloscopeProbeFrame::GuiOscilloscopeProbeFrame(GuiOscilloscopeDisplay *parent, GuiSchemaView *view):
        QFrame(parent), ui(new Ui::GuiOscilloscopeProbeFrame), mDisplay(parent),
        mView(view), mDisplayBuffer(nullptr), mProbedPlug(nullptr)
{
    mSampleBuffer = new OscilloscopeBuffer();
    mSampleBuffer->resize(parent->width());
    // --> Should be adapted to sample rate and refresh rate.
    // Sample buffer should contain sample produced between two displays.
    // If display is 50hz, take 25Hz in account. If sample rate is ~50KHz, then
    // 2000 max samples is enough for all cases.

    ui->setupUi(this);

    mDisplay->addProbe(this);

    connect(ui->enableButton, &QAbstractButton::toggled, this, &GuiOscilloscopeProbeFrame::handleEnable);
    connect(ui->changeColorButton, &QAbstractButton::pressed, this, &GuiOscilloscopeProbeFrame::handleChangeColor);
    connect(ui->changePlugButton, &QAbstractButton::toggled, this, &GuiOscilloscopeProbeFrame::handleChangePlug);
    connect(ui->deleteButton, &QAbstractButton::pressed, this, &GuiOscilloscopeProbeFrame::handleDelete);

    connect(parent, &GuiOscilloscopeDisplay::resized, this, &GuiOscilloscopeProbeFrame::displayResized);
}

GuiOscilloscopeProbeFrame::~GuiOscilloscopeProbeFrame()
{
    if (mProbeInteraction)
        // TODO: Sure there is a schema ? -> Interaction should be aware of schema
        mView->schema()->endInteraction();

    setProbedPlug(nullptr);

    mDisplay->removeProbe(this);

    delete mSampleBuffer;
    delete ui;
}


void GuiOscilloscopeProbeFrame::setProbedPlug(DrawnPlug *plug)
{
    if (mProbedPlug)
        mProbedPlug->schema()->core()->disconnectReadingBuffer(mSampleBuffer);

    mProbedPlug = plug;

    if (mProbedPlug)
        mProbedPlug->schema()->core()->connectReadingBuffer(mSampleBuffer, mProbedPlug->core());
}

void GuiOscilloscopeProbeFrame::turnOffChangeProbeButton()
{
    ui->changePlugButton->setChecked(false);
}

void GuiOscilloscopeProbeFrame::displayResized(QResizeEvent *e)
{
    size_t newsize = e->size().width();

    // TODO: Should not be resized (see constructor)
    mSampleBuffer->resize(newsize);

    // TODO: Should use a resizeable buffer capable of rewind
    size_t oldsize = (mDisplayBuffer)?mDisplayBuffer->size():0;

    if (oldsize == newsize)
        return;

    DisplayBuffer* oldbuffer = mDisplayBuffer;
    mDisplayBuffer = new DisplayBuffer(newsize);

    // Fill unset part of buffer with zeros
    int zero = size().height()*0.5f;
    size_t fill = newsize;
    if (oldbuffer)
    {
        if (oldbuffer->length() < newsize)
            fill = newsize - oldbuffer->length();
        else
            fill = 0;
    }
    while (fill--)
        mDisplayBuffer->push(zero);

    // Copy existing stuff from old buffer to new buffer
    if (!oldbuffer)
        return;

    oldbuffer->rewind();
    while (!oldbuffer->underflow())
        mDisplayBuffer->push(oldbuffer->pop());

    delete oldbuffer;
}

void GuiOscilloscopeProbeFrame::handleEnable(bool checked)
{
    // TODO: To be implemented
    printf("Enable %s\n", (checked)?"true":"false"); fflush(stdout);
}

void GuiOscilloscopeProbeFrame::handleChangeColor()
{
    // TODO: To be implemented
    printf("Change color\n"); fflush(stdout);
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

void GuiOscilloscopeProbeFrame::drawTo(QImage *image)
{
    int ymax = mDisplay->size().height();
    Value scale(100.0f);
    Value offset(ymax*0.5f);

    // Copy and convert new samples
    while (!mSampleBuffer->underflow())
        mDisplayBuffer->push(mSampleBuffer->pop().toInt(scale, offset));

    mDisplayBuffer->rewind();

    QColor color = Qt::white;

    int y;
    for (int x = 0; x < width(); x ++)
    {
        y = mDisplayBuffer->pop();
        // TODO: Manage bar representation if several samples
        if (y >= 0 && y < ymax)
            // TODO: Manage composition
            image->setPixelColor(x, y, color);
    }
}
