#ifndef GUIVALUELISTSPINBOX_H
#define GUIVALUELISTSPINBOX_H

#include <QSpinBox>

class GuiValueListSpinBox : public QSpinBox
{
    Q_OBJECT
public:
    GuiValueListSpinBox(QWidget *parent);

    QString textFromValue(int val) const override;
    void addValue(QString label, float value);

private:
    std::vector<std::pair<QString, float>> mValues;
};

#endif // GUIVALUELISTSPINBOX_H
