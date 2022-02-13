#include "guivaluelistspinbox.h"
#include <QLineEdit>

GuiValueListSpinBox::GuiValueListSpinBox(QWidget *parent):
    QSpinBox(parent)
{
    setRange(0, 0);
    lineEdit()->setReadOnly(true);
}

QString GuiValueListSpinBox::textFromValue(int val) const {
    if (val < mValues.size())
        return mValues[val].first;
    return QString("");
}

void GuiValueListSpinBox::addValue(QString label, float value) {
    mValues.push_back(std::pair<QString, float>{label, value});
    setRange(0, mValues.size() - 1);
}
