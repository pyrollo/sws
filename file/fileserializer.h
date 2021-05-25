#ifndef FILESERIALIZER_H
#define FILESERIALIZER_H
#include <QString>

class DrawnSchema;

class FileSerializer
{
public:
    FileSerializer(DrawnSchema *schema);
    QString serialize();
protected:
    DrawnSchema *mSchema;
};

#endif // FILESERIALIZER_H
