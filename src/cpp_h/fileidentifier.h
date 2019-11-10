#ifndef FILEIDENTIFIER_H
#define FILEIDENTIFIER_H

#include <QString>
#include <QDataStream>
#include <QFile>

class FileIdentifier
{
public:
    FileIdentifier();

    QStringList identifyFileFromFileSystem(const QString &path);
    QStringList identifyFileFromString(const QString &file);

private:
    QString readBytes(QDataStream &fStr, int lenght);
    QStringList fileTypeSelector(const QString &bytes);
    QString cutQString(const int &from, const int &lenghtCuttedString, const QString &string);
};

#endif // FILEIDENTIFIER_H
