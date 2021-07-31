#ifndef VALUESTRING_H
#define VALUESTRING_H
#include <QString>
#include "value.h"

inline QString valueToQString(const Value v)
{
    return QString::fromStdString(v.toString());
}

inline Value valueFromQString(const QString s)
{
    return Value(s.toStdString());
}

#endif // VALUESTRING_H
