#include "drawnmoduleinput.h"
#include "../drawnschema.h"
#include "gui/guistyle.h"
#include "core/modules/coremoduleinput.h"
#include "core/coreschema.h"
#include <QPainter>
#include <QInputDialog>

DrawnModuleInput::DrawnModuleInput(DrawnSchema *parentSchema, CoreModule *coreModule):
    DrawnModuleRectangle(parentSchema, coreModule, 4.0f, 2.0f), mName("")
{
    newOutput("value", DrawnPlug::right, 1.0f);
}

DrawnModuleInput::~DrawnModuleInput()
{
    if (mCoreModule && mSchema) {
            mSchema->core()->setInputName(core(), "");
            mSchema->notifyInputsChanged();
    }
}

void DrawnModuleInput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    (void)(option); (void)(widget);

    setPenAndBrush(painter);

    QPainterPath path;
    path.moveTo(0.0f, 0.0f);
    path.lineTo(mWidth, 0.0f);
    path.lineTo(mWidth, mHeight);
    path.lineTo(0.0f, mHeight);
    path.lineTo(0.0f, mHeight - 0.4f);
    path.lineTo(mHeight * 0.5f - 0.4f, mHeight * 0.5f);
    path.lineTo(0.0f, 0.4f);
    path.lineTo(0.0f, 0.0f);
    painter->drawPath(path);

    painter->setFont(GuiStyle::fModule());
    QRectF textRect(8.0f, 1.0f, 31.0f, 18.0f);

    QString name = QString::fromStdString(mCoreModule?mName:"Input");

    painter->setTransform(QTransform::fromScale(0.1f, 0.1f), true);
    painter->drawText(textRect, Qt::AlignLeft | Qt::AlignVCenter, name);
}

void DrawnModuleInput::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (!mCoreModule) {
        DrawnModuleRectangle::mouseDoubleClickEvent(event);
        return;
    }

    bool ok;
    std::string name = QInputDialog::getText(nullptr, "Input module", "Exported name:",
            QLineEdit::Normal, QString::fromStdString(mName), &ok).toStdString();
    if (ok && name != mName) {
        mSchema->core()->setInputName(core(), name);
        mName = name;
        schema()->notifyInputsChanged();
        update();
    }
}
