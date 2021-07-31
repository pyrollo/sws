#include "value.h"
#include <cmath>

#define PRECISION 1000000

// Constructors

Value::Value(): value(0)
{}

Value::Value(const double v)
{
    setFromDouble(v);
}

Value::Value(const std::string s)
{
    setFromString(s);
}

Value::Value(long int val): value(val)
{}

// Double conversion
void Value::setFromDouble(const double v) {
     value = PRECISION * v;
}

Value& Value::operator=(const double v) {
    setFromDouble(v);
    return *this;
}

double Value::toDouble() const
{
    return (double)value/PRECISION;
}

// String conversion
void Value::setFromString(const std::string str) {
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


Value& Value::operator =(std::string str) {
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

// Operations

Value Value::operator +(Value op)
{
    Value result;
    result.value = value + op.value;
    return result;
}

Value Value::operator *(Value op)
{
    Value result;
    // TODO: check if something more accurate can be done
    // ( op1 / sqr(PRECISION) * op2 / sqr(PRECISION) ?)
    result.value = value * op.value / PRECISION;
    return result;
}

/*
Value& Value::operator /(Value div)
{
    Value result;
    result.value = value / div.value * PRECISION;
    return &result;
}
*/
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

Value Value::moduloOne()
{
    if (value>0)
        return Value(value%PRECISION);
    else
        return Value((value+1)%PRECISION+PRECISION-1);
}

/*
    value min(value op1, value op2)
    {
        return (op1<op2)?op1:op2;
    }

    value max(value op1, value op2)
    {
        return (op1>op2)?op1:op2;
    }
*/
Value Value::limit(Value min, Value max)
{
    Value result;
    result.value = (value>max.value)?max.value:(value<min.value)?min.value:value;
    return result;
}
