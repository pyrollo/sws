#ifndef FILEDESERIALIZER_H
#define FILEDESERIALIZER_H
#include <string>
#include <QDomDocument>

class DrawnSchema;
class QByteArray;

class FileBadFileFormat : public std::exception
{
public:
    virtual const char* what() const throw() { return "Bad file format"; }
};

class FileDeserializer
{
public:
    FileDeserializer(const QByteArray &data);
    DrawnSchema *deserializeToDrawnSchema();
protected:
    QDomDocument mDocument;
};

#endif // FILEDESERIALIZER_H
