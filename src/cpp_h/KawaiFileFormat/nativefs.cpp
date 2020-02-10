#include "nativefs.h"

NativeFs::NativeFs() {}

bool NativeFs::open(const QString &path, const QIODevice::OpenMode &flags)
{
    file = new QFile(path);
    if (file->open(flags))
    {
        fileStream = new QDataStream(file);
        return true;
    }
    else
        return false;
}

bool NativeFs::seek(const qint64 &pos)
{
    return file->seek(pos);
}

qint64 NativeFs::size()
{
    return file->size();
}

qint64 NativeFs::pos()
{
    return file->pos();
}

template<typename T>
void NativeFs::write(const T &data)
{
    fileStream << data;
}

template<typename T>
T NativeFs::read(const qint64 &lenght)
{
    return KawaiConverter::byteArrayToT<T>(file->read(lenght));
}

template<typename T>
T NativeFs::read()
{
    return KawaiConverter::byteArrayToT<T>(file->read(sizeof(T)));
}
