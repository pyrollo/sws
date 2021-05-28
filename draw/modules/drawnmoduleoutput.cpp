#include "drawnmoduleoutput.h"
#include "../drawnschema.h"
#include "gui/guistyle.h"
#include "core/modules/coremoduleoutput.h"
#include "core/coreschema.h"
#include <QPainter>
#include <QInputDialog>


DrawnModuleOutput::DrawnModuleOutput(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 4.0f, 2.0f), mName("")
{
    newInput("value", DrawnPlug::left, 1.0f);
}

DrawnModuleOutput::~DrawnModuleOutput()
{
    if (core() && mSchema) {
        mSchema->core()->setOutputName(core(), "");
        mSchema->notifyOutputsChanged();
    }
}

void DrawnModuleOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(mWidth, 0.0f);
    path.arcTo(mWidth - (mHeight - 0.8f) * 0.5f, 0.4f, mHeight - 0.8f, mHeight - 0.8f, 90, 180);
    path.lineTo(mWidth, mHeight);
    path.lineTo(0.0f, mHeight);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);

    painter->setFont(GuiStyle::fModule());
    QRectF textRect(1.0f, 1.0f, 31.0f, 18.0f);

    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, mCoreModule?mName:"Output");
}

// TODO : Factorize DrawnModuleInput and DrawnModuleOutput
void DrawnModuleOutput::setName(QString name) {
    if (name == mName)
        return;

    mName = name;
    mSchema->core()->setOutputName(core(), mName.toStdString());
    schema()->notifyInputsChanged();
    update();
}

void DrawnModuleOutput::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!mCoreModule) {
        DrawnModuleRectangle::mouseDoubleClickEvent(event);
        return;
    }

    bool ok;
    QString name = QInputDialog::getText(nullptr, "Output module", "Exported name:",
            QLineEdit::Normal, mName, &ok);
    if (ok)
        setName(name);
}
