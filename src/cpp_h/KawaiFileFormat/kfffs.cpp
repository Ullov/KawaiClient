#include "kfffs.h"

#include <QDataStream>
#include <cmath>

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

void Kff::Fs::appendVoidClusters(const qint64 lenght, Stream &kffStream)
{
    qint64 finalLenght = (clearClustersPos.size() * Stream::contentLenght) - lenght;
    if (finalLenght > 0)
    {
        qint64 firstNewClusterPos = fileInNativeFs->size();
        qint64 newClustersNumber = std::ceil((double)finalLenght / (double)Stream::contentLenght);
        fileInNativeFs->resize(Stream::clusterLenght * newClustersNumber);
        for (int i = 0; i < newClustersNumber; i++)
        {
            clearClustersPos.append(firstNewClusterPos + ((Stream::clusterLenght) * i));
        }
    }

    for (int i = 0; i < std::ceil((double)lenght / (double)Stream::contentLenght); i++)
    {
        kffStream.addClusterPos(clearClustersPos[0]);
        clearClustersPos.pop_front();
    }
}
