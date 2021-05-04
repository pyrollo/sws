#ifndef COREPLUG_H
#define COREPLUG_H

#include "core.h"

class CoreModule;

class CorePlug
{
public:
    CorePlug(CoreModule *module);
    virtual ~CorePlug() {}

    virtual CoreValue value() const = 0;
    CoreModule *module() const { return mModule; }

protected:
    CoreModule *mModule;
};

#endif // COREPLUG_H
