#ifndef NATIVEFS_H
#define NATIVEFS_H

#include "kawaiconverter.h"
#include <QFile>
#include <QIODevice>
#include <QDataStream>

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

private:
    QFile *file;
    QDataStream *fileStream;
};

#endif // NATIVEFS_H
