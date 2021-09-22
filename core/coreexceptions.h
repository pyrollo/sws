/*
Short Waves System - A numeric modular synthetizer
Copyright (C) 2021 Pierre-Yves Rollo <dev@pyrollo.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
    explicit CoreUnknownTypeEx(const std::string& type) {
        mMsg = "Unknown type \"" + type + "\".";
    }
};

class CoreMachinIsRunningEx: public CoreException
{
public:
    CoreMachinIsRunningEx() {
        mMsg = "Machine is running, operation forbidden.";
    }
};


class CoreUnknownModuleEx: public CoreException
{
public:
    explicit CoreUnknownModuleEx(const std::string& name) {
        mMsg = "Unknown module \"" + name + "\".";
    }
};

class CoreUnknownInputEx: public CoreException
{
public:
    explicit CoreUnknownInputEx(const std::string& name) {
        mMsg = "Unknown input \"" + name + "\".";
    }
};

class CoreUnknownOutputEx: public CoreException
{
public:
    explicit CoreUnknownOutputEx(const std::string& name) {
        mMsg = "Unknown output \"" + name + "\".";
    }
};

class CoreDuplicateNameEx: public CoreException
{
public:
    explicit CoreDuplicateNameEx(const std::string& name) {
        mMsg = "Name \"" + name + "\" already in use.";
    }
};

class CoreNoSchemaEx: public CoreException
{
public:
    CoreNoSchemaEx() {
        mMsg = "No schema, schema needed.";
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
