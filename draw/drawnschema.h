#ifndef DRAWNSCHEMA_H
#define DRAWNSCHEMA_H
#include "drawnitem.h"
#include <map>
#include <memory>

class CoreSchema;
class DrawnModule;
class DrawnModuleFactory;
class DrawnPlug;

class DrawnSchema : public DrawnItem
{
public:
    DrawnSchema(CoreSchema *coreSchema);
    CoreSchema *core() { return mCoreSchema; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    DrawnModule *newModule(std::string name, std::string type);

    void highlightConnectable(DrawnPlug * plug);
    void unHighlight();

protected:
    CoreSchema *mCoreSchema;
    DrawnModuleFactory *mModuleFactory;
    std::map<std::string, std::unique_ptr<DrawnModule>> mModules;
};

#endif // DRAWNSCHEMA_H
