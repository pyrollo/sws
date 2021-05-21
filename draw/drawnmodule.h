#ifndef DRAWNMODULE_H
#define DRAWNMODULE_H
#include "drawnitem.h"
#include "drawninput.h"
#include "drawnoutput.h"
#include <map>
//#include <memory>

class DrawSchema;
class DrawnInput;
class DrawnOutput;
class CoreModule;
class QPainter;
class QMouseEvent;

#define MODULE_TYPE(TYPE) \
public: \
    virtual const char *getType() const { return mType; } \
    static constexpr char *mType = (char *)TYPE;

class DrawnModule : public DrawnItem
{
public:
    ~DrawnModule();
    virtual const char *getType() const { return ""; }
    DrawnSchema *schema() { return mSchema; }
    CoreModule *core() { return mCoreModule; }

    DrawnInput  *input(std::string name);
    DrawnOutput *output(std::string name);

    void unHighlightPlugs();
    void hightlightInputs();
    void hightlightOutputs();

    void setPenAndBrush(QPainter *painter);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected:
    DrawnSchema *mSchema;
    CoreModule *mCoreModule;

    std::map<std::string, DrawnInput *> mInputs;
    std::map<std::string, DrawnOutput *> mOutputs;

    DrawnModule(DrawnSchema *schema = nullptr, CoreModule *coreModule = nullptr);

    virtual DrawnInput *newInput(std::string name);
    virtual DrawnOutput *newOutput(std::string name);
};


#endif // GRAPHICMODULE_H
