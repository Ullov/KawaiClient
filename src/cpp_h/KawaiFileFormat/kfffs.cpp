#include "kfffs.h"

Kff::Fs::Fs(const QString &path, const QString &fileName)
{
    fileInNativeFs = new KTools::File();
    fileInNativeFs->open(path + '/' + fileName, QIODevice::ReadWrite);
    fileInNativeFs->seek(0);
    fileInNativeFs->write(signature);
    appendInodes();
}

void Kff::Fs::appendInodes()
{
    fileInNativeFs->seek(inodesBlockStart + (inodesNumber * 16));
    QByteArray voidInode;
    QDataStream str(&voidInode, QIODevice::WriteOnly);
    qint64 null = -1;
    str << null;
    voidInode.resize(16);
    for (qint64 i = 0; i < inodesAppendNumber; i++)
    {
        fileInNativeFs->write(voidInode);
        ++inodesNumber;
    }
    dataBlockStart = inodesBlockStart + (inodesNumber * 16);
}

template<>
Kff::Stream Kff::Fs::create<Kff::Stream>()
{
    return Kff::Stream(*fileInNativeFs, dataBlockStart, inodesBlockStart);
}
