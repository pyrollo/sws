#ifndef COREEXCEPTIONS_H
#define COREEXCEPTIONS_H
#include <string>
#include <exception>

class CoreException: public std::exception
{
public:
    virtual const char* what() const throw() { return mMsg.c_str(); }
    std::string mMsg;
};
/*
class CoreDuplicateNameEx: public CoreException
{
public:
    CoreDuplicateNameEx(std::string name) {
        mMsg = "Name \"" + name + "\" already in use.";
    }
};
*/
class CoreUnknownTypeEx: public CoreException
{
public:
    CoreUnknownTypeEx(std::string type) {
        mMsg = "Unknown type \"" + type + "\".";
    }
};

class CoreUnknownModuleEx: public CoreException
{
public:
    CoreUnknownModuleEx(std::string name) {
        mMsg = "Unknown module \"" + name + "\".";
    }
};

class CoreUnknownInputEx: public CoreException
{
public:
    CoreUnknownInputEx(std::string name) {
        mMsg = "Unknown input \"" + name + "\".";
    }
};

class CoreUnknownOutputEx: public CoreException
{
public:
    CoreUnknownOutputEx(std::string name) {
        mMsg = "Unknown output \"" + name + "\".";
    }
};

class CoreNotSameSchemaEx: public CoreException
{
public:
    CoreNotSameSchemaEx() {
        mMsg = "Not the same schema.";
    }
};

class CoreAlreadyConnectedEx: public CoreException
{
public:
    CoreAlreadyConnectedEx() {
        mMsg = "Plug already connected.";
    }
};

class CoreNotConnectedEx: public CoreException
{
public:
    CoreNotConnectedEx() {
        mMsg = "Plug not connected.";
    }
};


class CoreLoopConnectionEx: public CoreException
{
public:
    CoreLoopConnectionEx() {
        mMsg = "Connection creates a loop.";
    }
};

class CoreCantScheduleModulesEx: public CoreException
{
public:
    CoreCantScheduleModulesEx() {
        mMsg = "Unable to schedule modules in schema, must have problematic connections.";
    }
};

#endif // COREEXCEPTIONS_H
