#ifndef FILEIDENTIFIER_H
#define FILEIDENTIFIER_H

#include "../KTools/nativefs.h"

class FileIdentifier
{
public:
    FileIdentifier();

    static QStringList identifyFileFromFileSystem(const QString &path);
    static QStringList identifyFileFromString(const QByteArray &file);

private:
    static QStringList fileTypeSelector(const QByteArray &bytes);
    static QByteArray cutQString(const int &from, const int &lenghtCuttedString, const QByteArray &string);
};

#endif // FILEIDENTIFIER_H
