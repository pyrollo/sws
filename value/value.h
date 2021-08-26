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
