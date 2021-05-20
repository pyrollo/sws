#ifndef DRAWNSCHEMA_H
#define DRAWNSCHEMA_H
#include "drawnitem.h"
#include <map>

class CoreSchema;
class DrawnModule;
class DrawnModuleFactory;
class DrawnPlug;

class DrawnSchema : public DrawnItem
{
public:
    DrawnSchema(CoreSchema *coreSchema);
    ~DrawnSchema();

    CoreSchema *core() { return mCoreSchema; }
    DrawnModuleFactory *getModuleFactory() { return mModuleFactory; }

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr);
    DrawnModule *newModule(std::string name, std::string type);
    void removeModule(DrawnModule *module);

    void highlightConnectable(DrawnPlug * plug);
    void unHighlight();

protected:
    CoreSchema *mCoreSchema;
    DrawnModuleFactory *mModuleFactory;
    std::map<std::string, DrawnModule *> mModules;
};

#endif // DRAWNSCHEMA_H
