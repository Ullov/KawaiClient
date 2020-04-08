#ifndef NATIVEFS_H
#define NATIVEFS_H

#include "kawaiconverter.h"
#include <QFile>
#include <QIODevice>
#include <QDataStream>
#include <QDir>

class NativeFs
{
public:
    NativeFs();

    bool open(const QString &path, const QIODevice::OpenMode &flags);
    bool seek(const qint64 &pos);
    qint64 size();
    qint64 pos();
    template<typename T>
    void write(const T &data);
    template<typename T>
    T read(const qint64 &lenght);
    template<typename T>
    T read();
    static bool writeFile(const QByteArray &data, const QString &directory, const QString &fileName, const QIODevice::OpenMode &flags = QIODevice::WriteOnly);
    static void makePath(const QString &path);
    static bool fileExist(const QString &path);
    static bool dirExist(const QString &path);
    template<typename T>
    static T readFile(const QString &directory, const QString &fileName, const QIODevice::OpenMode &flags = QIODevice::ReadOnly);
    QDataStream fileStream;

private:
    QFile *file;
};

#endif // NATIVEFS_H
