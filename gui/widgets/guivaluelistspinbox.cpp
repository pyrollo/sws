#include "guivaluelistspinbox.h"
#include <QLineEdit>

GuiValueListSpinBox::GuiValueListSpinBox(QWidget *parent):
    QAbstractSpinBox(parent), mCurrentIndex(0)
{
    addValue(QString("1s"), 1.0f);
    addValue(QString("2s"), 2.0f);
    addValue(QString("5s"), 5.0f);
    addValue(QString("10s"), 10.0f);

    lineEdit()->setReadOnly(true);
    updateText();
}

void GuiValueListSpinBox::updateText()
{
    if (mValues.empty())
        lineEdit()->clear();
    else
        lineEdit()->setText(mValues[mCurrentIndex].first);
}

void GuiValueListSpinBox::stepBy(int steps)
{
    mCurrentIndex = mCurrentIndex + steps;
    if (mCurrentIndex < 0)
        mCurrentIndex = 0;
    if (mCurrentIndex >= int(mValues.size()))
        mCurrentIndex = int(mValues.size() - 1);

    updateText();
}

QAbstractSpinBox::StepEnabled GuiValueListSpinBox::stepEnabled() const
{
    QAbstractSpinBox::StepEnabled flags;

    if (mCurrentIndex > 0)
        flags |= QAbstractSpinBox::StepDownEnabled;
    if (mCurrentIndex < int(mValues.size() - 1))
        flags |= QAbstractSpinBox::StepUpEnabled;

    return flags;
}
