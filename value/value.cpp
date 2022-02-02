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

#include "value.h"
#include <cmath>
#include <limits>

#define PRECISION 1000000
static Value invPrecision((double)1/PRECISION);

// Constructors

Value::Value(): value(0)
{}

Value::Value(const double v)
{
    setFromDouble(v);
}

Value::Value(const std::string &str)
{
    setFromString(str);
}

// Double conversions

void Value::setFromDouble(const double v) {
     value = PRECISION * v;
}

Value& Value::operator =(const double v) {
    setFromDouble(v);
    return *this;
}

double Value::toDouble() const
{
    return (double)value/PRECISION;
}

// Int conversions

void Value::setFromInt(const int v) {
    value = PRECISION * long(v);
}

Value& Value::operator =(const int v) {
    setFromInt(v);
    return *this;
}

int Value::toInt() const
{
    static Value max((double)std::numeric_limits<int>::max());
    static Value min((double)std::numeric_limits<int>::min());
    return (int)(limit(min, max) * invPrecision).value;
}

short Value::toShort() const
{
    static Value max((double)std::numeric_limits<short>::max());
    static Value min((double)std::numeric_limits<short>::min());
    return (short)(limit(min, max) * invPrecision).value;
}

// String conversions

void Value::setFromString(const std::string &str) {
    value = 0;
    bool negative = false;
    int precision = PRECISION;
    bool separator = false;
    bool sign = false;

    for (char const &c:str) {
        if (c >= '0' && c <= '9') {
            if (precision > 1) {
                value = value * 10 + c - '0';
                if (separator)
                    precision = precision / 10;
            }
            sign = true;
            continue;
        }
            if (c == '-' && !sign) {
                sign = true;
                negative = true;
                continue;
            }
            if (c == '+' && !sign) {
                sign = true;
                continue;
            }
            if (c == '.' && !separator) {
            separator = true;
            continue;
        }
        // Error
    }

    if (precision)
            value = value * precision;

    if (negative)
        value = - value;
}

Value& Value::operator =(const std::string &str) {
    setFromString(str);
    return *this;
}

std::string Value::toString() const
{
    long int v = value;

    std::string result = "";
    bool negative = v < 0;
    int precision = PRECISION;
    bool printall = false;

    if (negative)
        v = -v;

    while (v != 0 || precision > 1) {
        char c = '0' + v % 10;
        if (printall || c != '0') {
            printall = true;
            result.insert (0, 1, c);
        }
        v = v / 10;
        if (precision) {
            precision = precision / 10;
        }
        if (precision == 1) {
            if (printall)
                result.insert (0, 1, '.');
            printall = true;
        }
    }

    if (precision == 1)
            result.insert (0, 1, '0');

    if (negative)
        result.insert(0, 1, '-');

    return result;
}

// Comparisons

bool Value::operator <(const Value &v)
{
    return value < v.value;
}

bool Value::operator <=(const Value &v)
{
    return value <= v.value;
}

bool Value::operator >(const Value &v)
{
    return value > v.value;
}

bool Value::operator >=(const Value &v)
{
    return value >= v.value;
}

bool Value::operator ==(const Value &v)
{
    return value == v.value;
}

bool Value::operator !=(const Value &v)
{
    return value != v.value;
}

// Operations

Value Value::operator +(Value op) const
{
    Value result;
    result.value = value + op.value;
    return result;
}

Value Value::operator *(Value op) const
{
    Value result;
    // TODO: check if something more accurate can be done
    // ( op1 / sqr(PRECISION) * op2 / sqr(PRECISION) ?)
    result.value = value * op.value / PRECISION;
    return result;
}

Value Value::operator /(Value op) const
{
    Value result;
    result.value = value / op.value * PRECISION;
    return result;
}

/*
    value absolute(value op)
    {
        return (op>0)?op:-op;
    }

    value modulo(value op, value div)
    {
        return (op>0)?op%div:((op+1)%div+div-1);
    }
*/

Value Value::moduloOne() const
{
    Value result;
    if (value>0)
        result.value = value%PRECISION;
    else
        result.value = (value+1)%PRECISION+PRECISION-1;

    return result;
}

Value Value::limit(Value min, Value max) const
{
    Value result;
    result.value = (value>max.value)?max.value:(value<min.value)?min.value:value;
    return result;
}
