#include "nativefs.h"

NativeFs::NativeFs() {}

bool NativeFs::open(const QString &path, const QIODevice::OpenMode &flags)
{
    file = new QFile(path);
    if (file->open(flags))
    {
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
    file->write(KawaiConverter::toByteArray<T>(data));
}

template<>
void NativeFs::write(const QByteArray &data)
{
    file->write(data);
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

bool NativeFs::writeFile(const QByteArray &data, const QString &directory, const QString &fileName, const QIODevice::OpenMode &flags)
{
    makePath(directory);
    QFile file(directory + '\\' + fileName);
    if (file.open(flags))
    {
        file.write(data);
    }
    else
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void NativeFs::makePath(const QString &path)
{
    QDir dir = QDir(path);
    bool qexi = dir.exists();
    if (!qexi)
        qexi = dir.mkpath("."); // if derictory does not exist make it
}

bool NativeFs::fileExist(const QString &path)
{
    QFileInfo checkFile(path);
    if (checkFile.exists() && checkFile.isFile())
        return true;
    else
        return false;
}

bool NativeFs::dirExist(const QString &path)
{
    QFileInfo checkFile(path);
    if (checkFile.exists() && checkFile.isDir())
        return true;
    else
        return false;
}

bool NativeFs::toEnd()
{
   return seek(size());
}

bool NativeFs::atEnd()
{
    return file->atEnd();
}

bool NativeFs::resize(const qint64 &localSize)
{
    return file->resize(localSize);
}

template<typename T>
T NativeFs::readFile(const QString &directory, const QString &fileName, const QIODevice::OpenMode &flags)
{
    if (!fileExist(directory + '\\' + fileName))
        return T();

    QFile rFile(directory + '\\' + fileName);
    if (!rFile.open(flags))
        return T();

    if (typeid (T) != typeid (QByteArray))
        return KawaiConverter::byteArrayToT<T>(rFile.readAll());

    return rFile.readAll();
}

template void NativeFs::write<qint16>(const qint16&);
template void NativeFs::write<qint64>(const qint64&);

template qint8 NativeFs::read<qint8>(const qint64&);
template qint16 NativeFs::read<qint16>(const qint64&);
template qint64 NativeFs::read<qint64>(const qint64&);
template QByteArray NativeFs::read<QByteArray>(const qint64&);

template qint64 NativeFs::read<qint64>();
template quint64 NativeFs::read<quint64>();
template qint16 NativeFs::read<qint16>();

template QString NativeFs::readFile<QString>(const QString&, const QString&, const QIODevice::OpenMode&);
template QByteArray NativeFs::readFile<QByteArray>(const QString&, const QString&, const QIODevice::OpenMode&);
