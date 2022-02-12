#ifndef GUIVALUELISTSPINBOX_H
#define GUIVALUELISTSPINBOX_H

#include <QAbstractSpinBox>

class GuiValueListSpinBox : public QAbstractSpinBox
{
    Q_OBJECT
public:
    GuiValueListSpinBox(QWidget *parent);

    void addValue(QString label, float value) {
        mValues.push_back(std::pair<QString, float>{label, value});
    }
    void updateText();
    void stepBy(int steps);
    QAbstractSpinBox::StepEnabled stepEnabled() const;
private:
    std::vector<std::pair<QString, float>> mValues;
    int mCurrentIndex;

};

#endif // GUIVALUELISTSPINBOX_H
