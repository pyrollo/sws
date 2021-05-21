#include "drawnitem.h"
#include "drawnmodule.h"
#include "drawnschema.h"
#include "drawninput.h"
#include "drawnoutput.h"
#include "gui/guistyle.h"
#include "core/coremodule.h"
#include "core/coreexceptions.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QPixmap>

DrawnModule::DrawnModule(DrawnSchema *schema, CoreModule *coreModule):
    DrawnItem(schema, 1.0f), mSchema(schema), mCoreModule(coreModule)
{
    if (mSchema)
        setFlags(flags()|ItemIsSelectable|ItemIsMovable);
    else
        setFlags(flags()|ItemIsSelectable);
}

DrawnModule::~DrawnModule() {
    for (auto it : mInputs)
        delete it.second;

    for (auto it : mOutputs)
        delete it.second;

    if (mSchema)
        mSchema->removeModule(this);

    if (mCoreModule)
        delete mCoreModule;
}

DrawnInput *DrawnModule::newInput(std::string name)
{
    DrawnInput *input;
    if (mCoreModule)
        input = new DrawnInput(this, mCoreModule->input(name));
    else
        input = new DrawnInput(this);

    connect(this, SIGNAL(positionChanged()), input, SIGNAL(positionChanged()));
    mInputs[name] = input;
    return input;
}

DrawnOutput *DrawnModule::newOutput(std::string name)
{
    DrawnOutput *output;
    if (mCoreModule)
        output = new DrawnOutput(this, mCoreModule->output(name));
    else
        output = new DrawnOutput(this);

    connect(this, SIGNAL(positionChanged()), output, SIGNAL(positionChanged()));
    mOutputs[name] = output;
    return output;
}

DrawnInput *DrawnModule::input(std::string name)
{
    try {
        return mInputs.at(name);
    } catch(const std::out_of_range&) {
        throw CoreUnknownInputEx(name);
    }
}

DrawnOutput *DrawnModule::output(std::string name)
{
    try {
        return mOutputs.at(name);
    } catch(const std::out_of_range&) {
        throw CoreUnknownOutputEx(name);
    }
}

void DrawnModule::hightlightInputs()
{
    if (mCoreModule)
        for (auto it : mInputs)
            if (!it.second->core()->isConnected())
                it.second->setHighlighted(true);
}

void DrawnModule::hightlightOutputs()
{
    if (mCoreModule)
        for (auto it : mOutputs)
            it.second->setHighlighted(true);
}

void DrawnModule::unHighlightPlugs()
{
    if (mCoreModule) {
        for (auto it : mInputs) {
            it.second->setHighlighted(false);
        }
        for (auto it : mOutputs) {
            it.second->setHighlighted(false);
        }
    }
}

void DrawnModule::setPenAndBrush(QPainter *painter)
{
    if (isSelected()) {
        painter->setPen(GuiStyle::pModuleSelected());
        painter->setBrush(GuiStyle::bModuleSelected());
    } else {
        painter->setPen(GuiStyle::pModule());
        painter->setBrush(GuiStyle::bModule());
    }
}

void DrawnModule::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (mSchema)
        return;

    if (event->button() == Qt::LeftButton) {

        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData();
        mimeData->setData("sws/moduletype", QByteArray::fromStdString(getType()));
        drag->setMimeData(mimeData);

        QRectF rect = boundingRect();
        QPixmap pix(rect.width()*20, rect.height()*20);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setTransform(QTransform().scale(20,20));
        paint(&painter, nullptr);
        for (auto it: mInputs)
            it.second->paint(&painter, nullptr);
        for (auto it: mOutputs)
            it.second->paint(&painter, nullptr);
        painter.end();
        drag->setPixmap(pix);

        Qt::DropAction dropAction = drag->exec();
    }
}
