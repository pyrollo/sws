#include "guioscilloscope.h"
#include "oscilloscopebuffer.h"

#include <QPainter>
#include <QTimer>
#include <algorithm>
GuiOscilloscope::GuiOscilloscope(QWidget *parent) : QWidget(parent)
{
    mSampleBuffer = new OscilloscopeBuffer(300);
    mIntBuffer = new int[mSampleBuffer->size()];

    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, this, QOverload<>::of(&QWidget::update));
    mTimer->setInterval(50);
    mTimer->setSingleShot(false);
    mTimer->start();
}

GuiOscilloscope::~GuiOscilloscope()
{
    mTimer->stop();
    delete mTimer;
    delete mSampleBuffer;
    delete mIntBuffer;
}

void GuiOscilloscope::paintEvent(QPaintEvent *) {
    QPainter painter(this);

    int width = std::min(size().width(), (int)mSampleBuffer->size());

    painter.setPen(Qt::white);
    painter.fillRect(QRectF(QPointF(), size()), Qt::black);

    mSampleBuffer->copyTo(mIntBuffer, Value(100.0f), Value(size().height()*0.5f));

    for (int x = 0; x < width; x ++)
        painter.drawPoint(x, mIntBuffer[x]);
}
