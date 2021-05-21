#ifndef DRAWNSCHEMA_H
#define DRAWNSCHEMA_H
#include "drawnitem.h"
#include <unordered_set>

class CoreSchema;
class DrawnModule;
class DrawnModuleFactory;
class DrawnPlug;

class DrawnSchema : public DrawnItem
{
    Q_OBJECT
public:
    DrawnSchema(CoreSchema *coreSchema);
    ~DrawnSchema();

    CoreSchema *core() { return mCoreSchema; }
    DrawnModuleFactory *getModuleFactory() { return mModuleFactory; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    DrawnModule *newModule(std::string type);
    void removeModule(DrawnModule *module);

    void highlightConnectable(DrawnPlug * plug);
    void unHighlight();

    void notifyInputsChanged() { emit inputsChanged(); }
    void notifyOutputsChanged() { emit outputsChanged(); }

signals:
    void inputsChanged();
    void outputsChanged();

protected:
    CoreSchema *mCoreSchema;
    DrawnModuleFactory *mModuleFactory;
    std::unordered_set<DrawnModule *>mModules;
};

#endif // DRAWNSCHEMA_H
