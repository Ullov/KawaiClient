#include "kfffile.h"

KffFile::KffFile(KawaiFileFormat *formatClass, const QString path)
{
    kff = formatClass;
    nativeFs = new NativeFs();
    nativeFs->open(path, QIODevice::Append | QIODevice::ReadWrite | QIODevice::ExistingOnly);
    nativeFs->seek(0);
}

KffFile::~KffFile() {}

qint64 KffFile::write(const QByteArray &data)
{
    lastClusterAddress = -1;
    QBitArray bits(data.count());

    for (qint64 pos = data.size(); pos > 0; pos -= contentLenght)
    {
        QByteArray dataBlock;
        qint64 actualPos;
        if ((actualPos = pos - contentLenght) > 0)
            dataBlock = data.mid(actualPos, contentLenght);
        else
            dataBlock = data.mid(0, pos);
        QBitArray bitArr = QBitArray::fromBits(static_cast<const char*>(dataBlock.data()), dataBlock.size() * 8);
        writeCluster(bitArr, lastClusterAddress);
    }
    return nativeFs->pos();
}

qint64 KffFile::writeCluster(const QBitArray &data, const qint64 &nextCluster)
{
    qint16 currentClusterContentLenght = data.size();
    qint64 clearCluster = lastClusterAddress = scanForClearCluster();

    std::bitset<contentLenght> cluster;
    cluster << currentClusterContentLenght << nextCluster;
    appendBitset(data, cluster, 80);

    if (clearCluster != -2)
        nativeFs->seek(clearCluster);
    else
        nativeFs->seek(nativeFs->size());

    //return nativeFs->write(cluster.to_string().c_str());
}

qint64 KffFile::scanForClearCluster()
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

void KffFile::appendBitset(const QBitArray &bitArr, std::bitset<contentLenght> &stdBitset, const int startPos)
{
    for (int i = 0; i < bitArr.size(); i++)
        stdBitset[i + startPos] = bitArr[i];
}

QByteArray* KffFile::concatenateClusters(const qint64 &pos, const qint64 &lenght, const qint16 frontOffset)
{
    qint64 nextluster = pos + frontOffset;
    QByteArray singleCluster;
    clusters = new QByteArray();
    int i;
    for (i = 0; ((i * contentLenght) < lenght) || (pos == -1); i++)
    {
        singleCluster = nativeFs->read<QByteArray>(1024); //file->read(1024);
        qint16 contLenght = singleCluster.mid(0, NumberTypesSize::Int16).toShort();
        nextluster = singleCluster.mid(NumberTypesSize::Int16, NumberTypesSize::Int64).toLong();
        clusters->append(singleCluster.mid(NumberTypesSize::Int16 + NumberTypesSize::Int64, contLenght));
    }
    if (pos != -1)
    {
        int shard = (i * contentLenght) - lenght;
        if (shard > 0)
        {
            clusters->append(singleCluster.mid(NumberTypesSize::Int16 + NumberTypesSize::Int64, shard));
        }
    }
    return clusters;
}

void KffFile::readHeader(const qint64 &pos, const FileTypes ft)
{
    readAllHeaderParams(pos, ft);
}

template<typename T>
T KffFile::readHeaderParam(quint64 &offset, const QByteArray *rawHeader, int paramLenght)
{
    if (paramLenght == 0)
        paramLenght = sizeof(T);
    QByteArray param = rawHeader->mid(offset, paramLenght);
    offset += paramLenght;
    return KTools::Converter::byteArrayToT<T>(param);
}

void KffFile::readAllHeaderParams(const qint64 &pos, const FileTypes &ft)
{
    quint64 offset = 0;
    nativeFs->seek(pos);
    quint64 len = nativeFs->read<quint64>(); //file->read(NumberTypesSize::Int64).toULong();
    QByteArray *rawHeader = concatenateClusters(pos + NumberTypesSize::Int64, fileHeaderStruct.headerLenght);
    if (ft == FileTypes::File)
    {
        fileHeaderStruct.headerLenght = len;
        fileHeaderStruct.type = readHeaderParam<qint32>(offset, rawHeader);
        fileHeaderStruct.filenameLenght = readHeaderParam<qint32>(offset, rawHeader);
        fileHeaderStruct.filename = readHeaderParam<QString>(offset, rawHeader, fileHeaderStruct.filenameLenght);
        fileHeaderStruct.pathLenght = readHeaderParam<qint32>(offset, rawHeader);
        fileHeaderStruct.dateCreated = readHeaderParam<quint32>(offset, rawHeader);
        fileHeaderStruct.dateModified = readHeaderParam<quint32>(offset, rawHeader);
        fileHeaderStruct.contentLenght = readHeaderParam<qint32>(offset, rawHeader);
    }
    else if (ft == FileTypes::Folder)
    {
        folderHeaderStruct.headerLenght = len;
        folderHeaderStruct.type = readHeaderParam<qint32>(offset, rawHeader);
        folderHeaderStruct.dirnameLenght = readHeaderParam<qint32>(offset, rawHeader);
        folderHeaderStruct.dirname = readHeaderParam<QString>(offset, rawHeader, folderHeaderStruct.dirnameLenght);
        folderHeaderStruct.pathLenght = readHeaderParam<qint32>(offset, rawHeader);
        folderHeaderStruct.path = readHeaderParam<QString>(offset, rawHeader, folderHeaderStruct.pathLenght);
        folderHeaderStruct.dateCreated = readHeaderParam<quint32>(offset, rawHeader);
        folderHeaderStruct.dateModified = readHeaderParam<quint32>(offset, rawHeader);
        folderHeaderStruct.filesNumber = readHeaderParam<quint64>(offset, rawHeader);
        folderHeaderStruct.addresToFile.clear();
        for (quint64 i = 0; i < folderHeaderStruct.filesNumber; i++)
            folderHeaderStruct.addresToFile.append(readHeaderParam<qint64>(offset, rawHeader));
    }
}

template <typename T>
T* KffFile::getFileStructure(const qint64 &pos)
{
    if (typeid(T) == typeid(FileStructure))
    {
        readAllHeaderParams(pos, FileTypes::File);
        return fileStruct;
    }
    else if (typeid(T) == typeid(FolderStructure))
    {
        readAllHeaderParams(pos, FileTypes::Folder);
        return folderStruct;
    }
}

template<typename T>
T read(const qint64 &pos, const qint64 &lenght, NativeFs &scope)
{
    return KTools::Converter::byteArrayToT<T>(scope.read<T>(pos, lenght));
}
