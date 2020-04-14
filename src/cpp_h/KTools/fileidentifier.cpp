#include "fileidentifier.h"

FileIdentifier::FileIdentifier() {}

QStringList FileIdentifier::identifyFileFromFileSystem(const QString &path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QDataStream fStr(&file);
    QByteArray fileSignature = readBytes(fStr, 20);
    QStringList fileType = fileTypeSelector(fileSignature);
    return fileType;
}

QStringList FileIdentifier::identifyFileFromString(const QByteArray &file)
{
    QByteArray fileSignature = cutQString(0, 20, file);
    QStringList fileType = fileTypeSelector(fileSignature);
    return fileType;
}

QByteArray FileIdentifier::readBytes(QDataStream &fStr, int lenght)
{
    char *s = new char[lenght + 1];
    fStr.readRawData(s, lenght);
    QByteArray result = s;
    delete [] s;
    return result;
}

QStringList FileIdentifier::fileTypeSelector(const QByteArray &bytes)
{
    QStringList result;
    QStringList stringsForEquations;
    stringsForEquations.push_back("");
    for (int i = 1; i < bytes.length(); i++)
        stringsForEquations.push_back(cutQString(0, i, bytes));

    if (stringsForEquations[4] == "\xFF\xD8\xFF\xDB" || stringsForEquations[12] == "\xFF\xD8\xFF\xE0\x00\x10\x4A\x46\x49\x46\x00\x01" || stringsForEquations[4] == "\xFF\xD8\xFF\xEE")
    {
        result.push_back(".jpg");
        result.push_back("JPEG image file");
    }
    else if (stringsForEquations[8] == "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A")
    {
        result.push_back(".png");
        result.push_back("PNG image file");
    }
    else if (stringsForEquations[6] == "\x47\x49\x46\x38\x37\x61" || stringsForEquations[6] == "\x47\x49\x46\x38\x39\x61")
    {
        result.push_back(".gif");
        result.push_back("GIF image file");
    }
    else if (stringsForEquations[4] == "\x49\x49\x2A\x00" || stringsForEquations[4] == "\x4D\x4D\x00\x2A")
    {
        result.push_back(".tiff");
        result.push_back("TIFF image file");
    }
    else
    {
        result.push_back("");
        result.push_back("Unknown file format");
    }
    return result;
}

QByteArray FileIdentifier::cutQString(const int &from, const int &lenghtCuttedString, const QByteArray &string)
{
    return string.mid(from, lenghtCuttedString);
}