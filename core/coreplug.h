#ifndef COREPLUG_H
#define COREPLUG_H
#include "value/value.h"

class CoreModule;

class CorePlug
{
public:
    CorePlug(CoreModule *module);
    virtual ~CorePlug() {}

    virtual Value value() const = 0;
    CoreModule *module() const { return mModule; }

protected:
    CoreModule *mModule;
};

#endif // COREPLUG_H
