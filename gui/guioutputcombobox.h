#ifndef GUIOUTPUTCOMBOBOX_H
#define GUIOUTPUTCOMBOBOX_H
#include <QComboBox>
class DrawnSchema;

class GuiOutputComboBox : public QComboBox
{
public:
    GuiOutputComboBox(QWidget *parent = nullptr);
    void setSchema(DrawnSchema *schema);

public slots:
    void outputsChanged();

protected:
    DrawnSchema *mSchema;
};

#endif // GUIOUTPUTCOMBOBOX_H
