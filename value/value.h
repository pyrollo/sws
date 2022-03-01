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

#ifndef VALUE_H
#define VALUE_H
#include <string>

class Value
{
public:

    // Constants
    static const int decimals = 6; // Value precison in decimals

    // Constructors

    Value();
    Value(const double v);
    Value(const std::string &str);

    // Conversions

    Value& operator =(const double v);
    Value& operator =(const int v);
    Value& operator =(const std::string &str);

    std::string toString() const;
    double toDouble() const;
    int toInt() const;
    short toShort() const;

    int toInt(const Value &scale, const Value &offset) const { return ((*this) * scale + offset).toInt(); }
    int toShort(const Value &scale, const Value &offset) const { return ((*this) * scale + offset).toShort(); }

    // Comparisons

    bool operator <(const Value &v);
    bool operator <=(const Value &v);
    bool operator >(const Value &v);
    bool operator >=(const Value &v);
    bool operator ==(const Value &v);
    bool operator !=(const Value &v);

    // Operations

    Value operator +(const Value op) const;
    Value operator *(const Value op) const;
    Value operator /(const Value op) const;

    Value modulo(Value div) const;
    Value moduloOne() const;
    Value limit(Value min, Value max) const;

private:
    long int value;

    void setFromDouble(const double v);
    void setFromString(const std::string &str);
    void setFromInt(const int val);
};

#endif // VALUE_H
