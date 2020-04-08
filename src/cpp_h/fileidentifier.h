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
    QStringList identifyFileFromString(const QByteArray &file);

private:
    QByteArray readBytes(QDataStream &fStr, int lenght);
    QStringList fileTypeSelector(const QByteArray &bytes);
    QByteArray cutQString(const int &from, const int &lenghtCuttedString, const QByteArray &string);
};

#endif // FILEIDENTIFIER_H
