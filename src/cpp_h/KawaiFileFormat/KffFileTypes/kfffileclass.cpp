#include "kfffileclass.h"

KffFileClass::KffFileClass() {}

bool KffFileClass::openFromNativeFs(const QString &path)
{
    nativeFs = new NativeFs();
    return nativeFs->open(path, QIODevice::Append | QIODevice::ReadWrite);
}

qint64 KffFileClass::write(const QByteArray &data)
{
    lastClusterAddress = -1;
    for (qint64 pos = data.size(); pos > 0; pos -= contentLenght)
    {
        QByteArray dataBlock;
        qint64 actualPos;
        if ((actualPos = pos - contentLenght) > 0)
            dataBlock = data.mid(actualPos, contentLenght);
        else
            dataBlock = data.mid(0, pos);
        writeCluster(dataBlock, lastClusterAddress);
    }
    return nativeFs->pos();
}

void KffFileClass::writeCluster(const QByteArray &data, const qint64 &nextCluster)
{
    qint16 currentClusterContentLenght = data.size();
    lastClusterAddress = scanForClearCluster();

    QByteArray cluster;
    appendByteArray(cluster, nextCluster);
    appendByteArray(cluster, data.size());
    appendByteArray(cluster, data);

    if (lastClusterAddress != -2)
        nativeFs->seek(lastClusterAddress);
    else
        nativeFs->seek(nativeFs->size());

    nativeFs->write(cluster);
}

qint64 KffFileClass::scanForClearCluster()
{
    qint64 clearClusterAddress = -1;
    if (nativeFs->size() == 0)
        clearClusterAddress = 0;
    else
    {
        qint64 flagPoint;
        for (int i = 0; (flagPoint = (contentLenght * i)) < nativeFs->size(); i++)
        {
            nativeFs->seek(flagPoint);
            qint16 flag = nativeFs->read<qint16>(2);// file->read(2).toShort();
            if (flag == -1)
            {
                clearClusterAddress = flagPoint;
                break;
            }
        }
        if (clearClusterAddress == -1)
            clearClusterAddress = -2;
    }
    return clearClusterAddress;
    // if == -2 - do not have clear clusters
}

QByteArray* KffFileClass::readClusters(const qint64 &pos, const qint64 &lenght, ReadedClusters &localReadedClusters, qint16 frontOffset)
{
    localReadedClusters = ReadedClusters();
    qint64 currentCluster = pos;
    QByteArray singleCluster;
    clusters = new QByteArray();
    qint64 i;
    for (i = 0; ((i * contentLenght) < lenght) || (currentCluster != -1); i++)
    {
        nativeFs->seek(currentCluster);
        singleCluster = nativeFs->read<QByteArray>(1024);
        localReadedClusters.contentLenght.append(singleCluster.mid(0, NumberTypesSize::Int16).toShort());
        localReadedClusters.addreses.append(currentCluster);
        currentCluster = singleCluster.mid(NumberTypesSize::Int16, NumberTypesSize::Int64).toLong();
        clusters->append(singleCluster.mid(NumberTypesSize::Int16 + NumberTypesSize::Int64 + frontOffset, localReadedClusters.contentLenght.last()));
        frontOffset = 0;
    }
    if (pos != -1)
    {
        qint32 shard = lenght - (i * contentLenght);
        if (shard > 0)
        {
            nativeFs->seek(currentCluster);
            singleCluster = nativeFs->read<QByteArray>(1024);
            localReadedClusters.contentLenght.append(singleCluster.mid(0, NumberTypesSize::Int16).toShort());
            localReadedClusters.addreses.append(currentCluster);
            clusters->append(singleCluster.mid(NumberTypesSize::Int16 + NumberTypesSize::Int64 + frontOffset, shard));
        }
    }
    return clusters;
}

template<typename T>
T KffFileClass::readHeaderParam(quint64 &offset, const QByteArray *rawHeader, int paramLenght)
{
    if (paramLenght == 0)
        paramLenght = sizeof(T);
    QByteArray param = rawHeader->mid(offset, paramLenght);
    offset += paramLenght;
    return KTools::Converter::byteArrayToT<T>(param);
}

template<typename T>
T KffFileClass::readRawData(const qint64 &pos, const qint64 &lenght, NativeFs &scope)
{
    return KTools::Converter::byteArrayToT<T>(scope.read<T>(pos, lenght));
}

void KffFileClass::deleteData(ReadedClusters &localReadedClusters)
{
    qint16 nullLen = -1;
    QByteArray tmp;
    for (quint64 i = 0; i < localReadedClusters.addreses.size(); i++)
    {
        nativeFs->seek(localReadedClusters.addreses[i]);
        nativeFs->write<qint16>(nullLen);
    }
}

template<typename T>
void KffFileClass::appendByteArray(QByteArray &arr, const T &addData)
{
    QDataStream ds(arr);
    ds << addData;
}

template qint32 KffFileClass::readHeaderParam<qint32>(quint64&, const QByteArray*, int);
template QString KffFileClass::readHeaderParam<QString>(quint64&, const QByteArray*, int);
template quint32 KffFileClass::readHeaderParam<quint32>(quint64&, const QByteArray*, int);
template quint64 KffFileClass::readHeaderParam<quint64>(quint64&, const QByteArray*, int);
template qint64 KffFileClass::readHeaderParam<qint64>(quint64&, const QByteArray*, int);

template void KffFileClass::appendByteArray<QString>(QByteArray&, const QString&);
template void KffFileClass::appendByteArray<quint32>(QByteArray&, const quint32&);
template void KffFileClass::appendByteArray<qint32>(QByteArray&, const qint32&);
template void KffFileClass::appendByteArray<quint64>(QByteArray&, const quint64&);
template void KffFileClass::appendByteArray<qint64>(QByteArray&, const qint64&);
template void KffFileClass::appendByteArray<QByteArray>(QByteArray&, const QByteArray&);
