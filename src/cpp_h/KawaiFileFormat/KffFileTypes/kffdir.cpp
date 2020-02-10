#include "kffdir.h"

KffDir::KffDir() {}

bool KffDir::open(const qint64 &pos)
{
    startPos = pos;
    return readHeader(pos);
}

bool KffDir::readHeader(const qint64 &pos)
{
    quint64 offset = 0;
    nativeFs->seek(pos);
    quint64 len = readClusters(pos, NumberTypesSize::Int64, folderHeaderStruct->clusters)->toULong();
    QByteArray *rawHeader = readClusters(pos, folderHeaderStruct->headerLenght, folderHeaderStruct->clusters);

    folderHeaderStruct->headerLenght = len;
    folderHeaderStruct->type = readHeaderParam<qint32>(offset, rawHeader);
    if (folderHeaderStruct->type != FileTypeCodes::KffDir)
        return false;
    folderHeaderStruct->nameLenght = readHeaderParam<qint32>(offset, rawHeader);
    folderHeaderStruct->name = readHeaderParam<QString>(offset, rawHeader, folderHeaderStruct->nameLenght);
    folderHeaderStruct->pathLenght = readHeaderParam<qint32>(offset, rawHeader);
    folderHeaderStruct->path = readHeaderParam<QString>(offset, rawHeader, folderHeaderStruct->pathLenght);
    folderHeaderStruct->dateCreated = readHeaderParam<quint32>(offset, rawHeader);
    folderHeaderStruct->dateModified = readHeaderParam<quint32>(offset, rawHeader);
    folderHeaderStruct->filesNumber = readHeaderParam<quint64>(offset, rawHeader);
    folderHeaderStruct->addresToFile.clear();
    for (quint64 i = 0; i < folderHeaderStruct->filesNumber; i++)
        folderHeaderStruct->addresToFile.append(readHeaderParam<qint64>(offset, rawHeader));
    return true;
}

void KffDir::save()
{
    deleteData(folderHeaderStruct->clusters);
    QByteArray headerData;
    quint64 len = 0;
    appendByteArray(headerData, folderHeaderStruct->type);
    len += sizeof(folderHeaderStruct->type);
    appendByteArray(headerData, folderHeaderStruct->nameLenght);
    len += sizeof(folderHeaderStruct->nameLenght);
    appendByteArray(headerData, folderHeaderStruct->name);
    len += sizeof(folderHeaderStruct->name);
    appendByteArray(headerData, folderHeaderStruct->dateCreated);
    len += sizeof(folderHeaderStruct->dateCreated);
    appendByteArray(headerData, folderHeaderStruct->dateModified);
    len += sizeof(folderHeaderStruct->dateModified);
    appendByteArray(headerData, folderHeaderStruct->filesNumber);
    len += sizeof(folderHeaderStruct->filesNumber);
    for (quint64 i = 0; i < folderHeaderStruct->filesNumber; i++)
    {
        appendByteArray(headerData, folderHeaderStruct->addresToFile[i]);
        len += NumberTypesSize::Int64;
    }
    QByteArray lenByteArr;
    appendByteArray(lenByteArr, len);
    appendByteArray(lenByteArr, headerData);
    write(lenByteArr);
}
