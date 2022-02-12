#include "guioscilloscopeprobeframe.h"
#include "ui_guioscilloscopeprobeframe.h"

#include "guioscilloscopedisplay.h"
#include "gui/guischemaview.h"

#include "draw/drawnschema.h"
#include "draw/drawnschemainteraction.h"
#include "draw/drawnplug.h"

#include "core/coresamplebuffer.h"
#include "utils/resizeablerollingbuffer.h"
#include "utils/rollingbuffer.h"

#include <QGraphicsSceneMouseEvent>
#include <QResizeEvent>
#include <QImage>
#include <QRgb>

// Display buffer
// TODO: Should be resizeable and rewindable
class DisplayBuffer : public RollingBuffer<GuiOscilloscopeProbeSample>
{
public:
    DisplayBuffer(size_t size): RollingBuffer<GuiOscilloscopeProbeSample>(size) {}
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
        mView(view), mProbeInteraction(nullptr), mProbedPlug(nullptr),
        mDisplayBuffer(nullptr), mLast(0), mPeriod(0.0f), mSampleRatio(1.0f), mCurrentSample({0, 0})
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

    handleChangeColor();
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
    GuiOscilloscopeProbeSample zero = {int(size().height()*0.5f), int(size().height()*0.5f)};

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
    mColor = ui->changeColorButton->getColor();
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

void addPixel(QImage *image, int x, int y, QColor &color)
{
    QRgb *line = (QRgb*)image->scanLine(y);
    QRgb pixel = line[x];
    // Here is the color composition rule (basic 'lighten only' thing for now)
    line[x] = qRgb(
        std::max(qRed(pixel), color.red()),
        std::max(qGreen(pixel), color.green()),
        std::max(qBlue(pixel), color.blue())
    );
}

void GuiOscilloscopeProbeFrame::drawTo(QImage *image)
{

    // TODO: Move that in class members
    Value scale(100.0f);
    Value offset(mDisplay->size().height()*0.5f);

    // Convert and merge new core samples to display samples
    while (!mSampleBuffer->underflow()) {
        mLast = mSampleBuffer->pop().toInt(scale, offset);

        if (mCurrentSample.min > mLast)
            mCurrentSample.min = mLast;
        if (mCurrentSample.max < mLast)
            mCurrentSample.max = mLast;

        mPeriod += 1.0f;
        if (mPeriod > mSampleRatio) {
            mDisplayBuffer->push(mCurrentSample);
            mPeriod -= mSampleRatio;
            mCurrentSample.min = mLast;
            mCurrentSample.max = mLast;
        }
    }

    mDisplayBuffer->rewind();

    QColor color;
    int ylimit = mDisplay->size().height() - 1;
    for (int x = 0; x < width(); x ++)
    {
        auto sample = mDisplayBuffer->pop();
        sample.min = (sample.min > 0)?sample.min:0;
        sample.max = (sample.max < ylimit)?sample.max:ylimit;
        if (sample.min <= ylimit && sample.max >= 0) {
            color = mColor.darker(100 + (sample.max-sample.min) * 5);
            for (int y = sample.min; y <= sample.max; y++)
                addPixel(image, x, y, color);
        }
    }
}
