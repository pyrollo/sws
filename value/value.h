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
    Value();
    Value(const double v);
    Value(const std::string s);

    // Conversions

    Value& operator =(const double v);
    Value& operator =(const std::string s);

    std::string toString() const;
    double toDouble() const;
    int toInt() const;
    short toShort() const;

    // Operations

    Value operator +(const Value op);
    Value operator *(const Value op);
//    Value& operator /(const Value div);

//    value& operator %(const value op1, const value op2);

    Value modulo(Value div) const;
    Value moduloOne() const;
    Value limit(Value min, Value max) const;

private:
    void setFromDouble(const double v);
    void setFromString(const std::string s);

    long int value;

    Value(long int val);

};

#endif // VALUE_H
