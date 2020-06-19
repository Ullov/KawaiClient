#include "kffstream.h"

#include <cmath>
#include "../KTools/converter.h"

const qint64 Kff::Stream::eos = 0;
const qint64 Kff::Stream::contentLenght = 4096;
const qint64 Kff::Stream::clusterLenght = contentLenght + 8 + 8;

Kff::Stream::Stream(KTools::File &NfFile, const qint64 dbStart, const qint64 inStart)
{
    dataBlockStart = dbStart;
    fileInNativeFs = &NfFile;
    inodeBlockStart = inStart;
    findClearInode();
}

bool Kff::Stream::findClearInode()
{
    fileInNativeFs->seek(inodeBlockStart);
    while (fileInNativeFs->pos() < dataBlockStart)
    {
        qint64 currPos = fileInNativeFs->pos();
        bool tmp = fileInNativeFs->read<qint64>() == voidPtr<qint64>();
        if (tmp)
        {
            inodePos = currPos;
            appendCluster();
            return true;
        }
        else
        {
            fileInNativeFs->seek(currPos + 8 + 8);
        }
    }
    return false;
}

qint64 Kff::Stream::appendCluster()
{
    fileInNativeFs->seek(dataBlockStart);
    qint64 clearClusterPos = voidPtr<qint64>();
    while (!fileInNativeFs->atEnd())
    {
        qint64 currPos = fileInNativeFs->pos();
        if (fileInNativeFs->read<qint64>() == voidPtr<qint64>())
        {
            clearClusterPos = currPos;
            break;
        }
        else
        {
            fileInNativeFs->seek(currPos + 8 + contentLenght); // 8 = next cluster pos [qint64]; 256 = content [QByteArray]
        }
    }

    if (clearClusterPos == voidPtr<qint64>())
    {
        // if all clusters full append new cluster
        fileInNativeFs->toEnd();
        clearClusterPos = fileInNativeFs->pos();
        fileInNativeFs->write<qint64>(eos);
        fileInNativeFs->resize(fileInNativeFs->size() + contentLenght);
        fileInNativeFs->write<QByteArray>(QByteArray().append(contentLenght, 0));
    }

    clustersPos.append(clearClusterPos);
    currClusterNumber = clustersPos.size() - 1;

    if (clustersPos.size() > 1)
    {
        writeInCluster(clustersPos.last(), clustersPos.size() - 2);
    }

    if (clustersPos.size() == 1)
    {
        writeInInode(clearClusterPos, 0);
    }

    fileInNativeFs->seek(clustersPos.last() + 8);
    posInCurrCluster = 0;
    return clearClusterPos;
}

void Kff::Stream::writeInInode(qint64 firstClusterPos, qint64 contentLenght)
{
    qint64 currStreamPos = fileInNativeFs->pos();
    fileInNativeFs->seek(inodePos);
    fileInNativeFs->write(firstClusterPos);
    fileInNativeFs->write(contentLenght);
    fileInNativeFs->seek(currStreamPos);
}

void Kff::Stream::writeInCluster(const QByteArray &content)
{
    qint64 offset = globalPos % contentLenght;
    if (content.size() > (contentLenght - offset))
    {
        KTools::Log::writeError("Attempt write more content than may fit in cluster. offset: " + QString::number(offset) + "; content.size(): " + QString::number(content.size()) + "; content: " + content, "Kff::Stream::writeInCluster()");
        return;
    }
    qint64 whereWrite = clustersPos[std::floor(globalPos / contentLenght)] + 8 + offset;
    fileInNativeFs->seek(whereWrite);
    fileInNativeFs->write(content);
    globalPos += content.size();
}

void Kff::Stream::writeInCluster(const qint64 nextBlockPos, const qint64 localCurrBlockNumber)
{
    if (nextBlockPos <= 0)
    {
        KTools::Log::writeError("Attempt write incorrect next block pos. nextBlockPos: " + QString::number(nextBlockPos) + "; localCurrBlockNumber: " + QString::number(localCurrBlockNumber), "Kff::Stream::writeInCluster()");
        return;
    }
    if (localCurrBlockNumber < 0 || localCurrBlockNumber > clustersPos.size() - 1)
    {
        KTools::Log::writeError("Incorrect localCurrBlockNumber. nextBlockPos: " + QString::number(nextBlockPos) + "; localCurrBlockNumber: " + QString::number(localCurrBlockNumber), "Kff::Stream::writeInCluster()");
        return;
    }
    fileInNativeFs->seek(clustersPos[localCurrBlockNumber]);
    fileInNativeFs->write(nextBlockPos);
}

qint64 Kff::Stream::size()
{
    return streamLenght;
}

qint64 Kff::Stream::lastClusterClearSpace()
{
    return (contentLenght * clustersPos.size()) - streamLenght;
}

qint64 Kff::Stream::lastClusterUsedSpace()
{
    return contentLenght - lastClusterClearSpace();
}

void Kff::Stream::seek(const qint64 pos)
{
    if (pos > size()) // if pos more than stream size sets pos to last byte
    {
        fileInNativeFs->seek(clustersPos.last() + lastClusterUsedSpace());
        return;
    }

    qint64 posInCluster = pos % contentLenght;
    qint64 clusterNumber = std::floor(pos / contentLenght);

    fileInNativeFs->seek(clustersPos[clusterNumber] + 8 + posInCluster);
    currClusterNumber = clusterNumber;
    posInCurrCluster = posInCluster;
}

qint64 Kff::Stream::pos()
{
    return currClusterNumber * contentLenght + posInCurrCluster;
}

bool Kff::Stream::atEnd()
{
    return ((currClusterNumber * contentLenght) + posInCurrCluster) == size();
}

void Kff::Stream::toNextCluster()
{
    if (currClusterNumber < clustersPos.size() - 1)
    {
        ++currClusterNumber;
        seek(clustersPos[currClusterNumber] + 8);
        posInCurrCluster = 0;
    }
    else
    {
        appendCluster();
    }
}

void Kff::Stream::write(const QByteArray &data)
{
    if (data.size() <= (contentLenght - posInCurrCluster)) // if data size smaller or equal to number butes in cluster after pos writes all in current cluster, if not in multiple clusters
    {
        fileInNativeFs->write(data);
    }
    else
    {
        QByteArray firstWriteBlock = data.mid(0, contentLenght - posInCurrCluster);
        fileInNativeFs->write(firstWriteBlock);
        toNextCluster();

        qint64 writedSize = 0;
        qint64 firstBlockSize = firstWriteBlock.size();
        for (qint64 i = 0; (writedSize = i * contentLenght) < data.size(); i++)
        {
            QByteArray writeBlock = data.mid(writedSize + firstBlockSize, contentLenght);
            qint64 blockLenght = writeBlock.size();
            fileInNativeFs->write(writeBlock);
            if (blockLenght == contentLenght)
                toNextCluster();
            else
                posInCurrCluster += blockLenght;
        }
    }
}

QByteArray Kff::Stream::read(qint64 lenght)
{
    if (lenght > size() - pos())
    {
        lenght = size() - pos();
    }
    QByteArray result;

    if (lenght <= (contentLenght - posInCurrCluster))
    {
        result.append(fileInNativeFs->read<QByteArray>(lenght));
        posInCurrCluster += result.size();
    }
    else
    {
        result.append(fileInNativeFs->read<QByteArray>(contentLenght - posInCurrCluster));
        qint64 firstBlockSize = result.size();
        toNextCluster();

        for (qint64 i = 0; ((i * contentLenght) + firstBlockSize) < lenght; i++)
        {
            qint64 remained = (lenght - ((i * contentLenght) + firstBlockSize));
            if (remained < contentLenght)
            {
                result.append(fileInNativeFs->read<QByteArray>((lenght - ((i * contentLenght) + firstBlockSize))));
            }
            else
            {
                result.append(fileInNativeFs->read<QByteArray>(contentLenght));
                toNextCluster();
            }
        }
    }
    return result;
}

template <typename T> const
T Kff::Stream::voidPtr()
{
    T tmp = -1;
    return tmp;
}

void Kff::Stream::addClusterPos(const qint64 pos)
{
    qint64 lastCluster = clustersPos.last();
    clustersPos.append(pos);
    fileInNativeFs->seek(pos);
    fileInNativeFs->write(voidCluster(lastCluster));

    fileInNativeFs->seek(lastCluster + 8);
    fileInNativeFs->write(pos);
}

const QByteArray Kff::Stream::voidCluster(const qint64 previousClusterPos)
{
    QByteArray result;
    result.append(KTools::Converter::toByteArray(previousClusterPos)); // pos of a previous cluster [qint64]
    result.append(KTools::Converter::toByteArray(voidPtr<qint64>())); // pos of a next cluster [qint64]
    result.append(contentLenght, 0); // cluster's content. Raw bytes, 4096 bytes lenght
    return result;
}
