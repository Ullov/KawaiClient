#include "kawaifileformat.h"

#define cl 20

KawaiFileFormat::KawaiFileFormat()
{

}

bool KawaiFileFormat::open(const QString &path)
{
    file = new QFile(path);
    if (!file->open(QIODevice::Append | QIODevice::ReadWrite | QIODevice::ExistingOnly))
        return false;

    //if (!seek(0))
    //    return false;

    fStream = new QDataStream(file);
    return true;
}
/*
bool KawaiFileFormat::seek(const qint64 &pos)
{
    return file->seek(pos);
}

qint64 KawaiFileFormat::write(const QByteArray &data)
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
    return pos();
}

qint64 KawaiFileFormat::writeCluster(const QBitArray &data, const qint64 &nextCluster)
{
    qint16 currentClusterContentLenght = data.size();
    qint64 clearCluster = lastClusterAddress = scanForClearCluster();
    
    std::bitset<contentLenght> cluster;
    cluster << currentClusterContentLenght << nextCluster;
    appendBitset(data, cluster, 80);
    
    if (clearCluster != -2)
        seek(clearCluster);
    else
        seek(size());

    return file->write(cluster.to_string().c_str());
}

qint64 KawaiFileFormat::scanForClearCluster()
{
    qint64 clearClusterAddress = -1;
    if (size() == 0)
        clearClusterAddress = 0;
    else
    {
        qint64 flagPoint;
        for (int i = 0; (flagPoint = (contentLenght * i)) < size(); i++)
        {
            seek(flagPoint);
            qint16 flag = file->read(2).toShort();
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

qint64 KawaiFileFormat::size()
{
    return file->size();
}

void KawaiFileFormat::appendBitset(const QBitArray &bitArr, std::bitset<contentLenght> &stdBitset, const int startPos)
{
    for (int i = 0; i < bitArr.size(); i++)
        stdBitset[i + startPos] = bitArr[i];
}
*/
bool KawaiFileFormat::create(const QString &path)
{
    file = new QFile(path);
    if (!file->open(QIODevice::ReadWrite | QIODevice::NewOnly))
        return false;

    makeDir("/");

    return true;
}

void KawaiFileFormat::makeDir(const QString &path)
{
    QStringList dirs = getPathInList(path);
    quint64 filesNumber = 0;
    qint32 type = 0;

    for (int i = 0; i < dirs.size(); i++)
    {
        qint64 nowTime = QDateTime::currentDateTime().toTime_t();
        QByteArray dirData;
        dirData.append(type);
        dirData.append(dirs[i].size());
        dirData.append(dirs[i]);
        dirData.append(nowTime);
        dirData.append(nowTime);
        dirData.append(filesNumber);

        //write(dirData);
    }
}
/*
qint64 KawaiFileFormat::pos()
{
    return file->pos();
}
*/
bool KawaiFileFormat::exist(const QString &path)
{
    if (cd(path, true) != -1)
        return true;
    else
        return false;
}

QStringList KawaiFileFormat::getPathInList(const QString &path)
{
    QStringList dirs;
    //if (path == root)
    //    dirs.append(root);
    //else
    //    dirs = path.split(root);
    return dirs;
}

qint64 KawaiFileFormat::cd(const QString &path, const bool keepCurrentPath)
{
    bool relative;
    qint64 pos = -1;
    if (path[0] == '/')
        relative = false;
    else
        relative = true;

    if (!relative)
        currentDir.clear();

    QStringList dirs = getPathInList(path);
    for (int i = 0; i < dirs.size(); i++)
    {
        if ((pos = readDir(dirs[i])) == -1)
        {
            cd(currentDirPath);
            return -1;
        }
    }
    if (!keepCurrentPath)
        currentDirPath = path;
    return pos;
}

qint64 KawaiFileFormat::readDir(const QString &dirName)
{
    int charsAlreadyRead = 0;
    quint64 pos = 0;
    if (!currentDir.empty())
    {
        for (quint64 i = 0; i < currentDir["filesNumber"].toULong(); i++)
        {
            //seek(currentDirFilesAddresses[i]);
            if (file->read(NumberTypesSize::Int32).toInt() == 0)
            {
                //seek(currentDirFilesAddresses[i] + NumberTypesSize::Int32);
                qint32 dirNameSize = file->read(NumberTypesSize::Int32).toInt();
                //seek(currentDirFilesAddresses[i] + (NumberTypesSize::Int32 * 2));
                QByteArray scannedDirName = file->read(dirNameSize);
                if (dirName == scannedDirName)
                {
                    pos = currentDirFilesAddresses[i];
                    break;
                }
            }
        }
    }
    if (pos == 0 && !currentDir.empty())
        return false;

    QByteArray dir = read(pos);
    currentDir.clear();

    currentDir["type"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int32);
    charsAlreadyRead += NumberTypesSize::Int32;

    currentDir["dirnameLenght"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int32);
    charsAlreadyRead += NumberTypesSize::Int32;

    currentDir["dirname"] = dir.mid(charsAlreadyRead, currentDir["dirnameLenght"].toInt());
    charsAlreadyRead += currentDir["dirnameLenght"].toInt();

    currentDir["pathLenght"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int32);
    charsAlreadyRead += NumberTypesSize::Int32;

    currentDir["path"] = dir.mid(charsAlreadyRead, currentDir["pathLenght"].toInt());
    charsAlreadyRead += currentDir["pathLenght"].toInt();

    currentDir["dateCreated"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int32);
    charsAlreadyRead += NumberTypesSize::Int32;

    currentDir["dateModified"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int32);
    charsAlreadyRead += NumberTypesSize::Int32;

    currentDir["filesNumber"] = dir.mid(charsAlreadyRead, NumberTypesSize::Int64);
    charsAlreadyRead += NumberTypesSize::Int64;

    for (qint64 i = 0; i < currentDir["filesNumber"].toULong(); i++)
    {
        currentDirFilesAddresses.append(dir.mid(charsAlreadyRead, NumberTypesSize::Int64).toLong());
        charsAlreadyRead += NumberTypesSize::Int64;
    }
    return pos;
}

QByteArray KawaiFileFormat::read(const qint64 &firstClusterPos)
{
    //seek(firstClusterPos);
    QByteArray cluster = QByteArray();
    qint64 nextCluster = 0;
    while (nextCluster != -1)
    {
        QByteArray tmp = file->read(1024);
        qint16 localContentLenght = tmp.mid(0, 2).toShort();
        nextCluster = tmp.mid(2, 8).toULong();
        cluster.push_front(tmp.mid(10, localContentLenght));
    }
    return cluster;
}

bool KawaiFileFormat::readFile(const QString &path, const QString &fileName)
{

}

bool KawaiFileFormat::makeFile(const QByteArray &content, const QString &path, const QString &filename)
{
    QStringList dirs = getPathInList(path);
    qint32 type = 1;

    qint64 nowTime = QDateTime::currentDateTime().toTime_t();
    QByteArray fileData;
    fileData.append(type);
    fileData.append(filename.size());
    fileData.append(filename);
    fileData.append(filename.size());
    fileData.append(filename);
    fileData.append(nowTime);
    fileData.append(nowTime);
    fileData.append(content.size());
    fileData.append(content);


    //write(fileData);
}

qint64 KawaiFileFormat::writeFile(const QString &path, const QString &filename, const QByteArray &fileData)
{
    qint64 dirPos = cd(path);
    //seek(dirPos);

}
// all sizes in bits.
// --
// cluster structure:
// Cluster length = 1 Kb = 1024 Byte = 8192 Bit
// [contentLenght]             {16 bit}
// [nextCluster]               {64 bit}
// [content]                   {8112 bit}
// ----
// ----
// dir file structure:
// type                         [int][32] = 0
// dirnameLenght                [int][32]
// dirname                      [string][filenameLenght]
// pathLenght                   [int][32]
// path                         [string][pathLenght]
// dateCreated                  [unixTimestamp(uint)][32]
// dateModified                 [unixTimestamp(uint)][32]
// filesNumber                  [uint][64]
// listFileAddresses {
//     .lenght[filesNumber]
//     item {
//         addressToFile        [int][64]
//     }
// }
// ----
// ----
// file 'type = 0' structure (classic file)
// [type]                       [int][32] = 1
// [filenameLenght]             [int][32]
// [filename]                   [string][filenameLenght]
// [pathLenght]                 [int][32]
// [path]                       [string][pathLenght]
// [dateCreated]                [unixTimestamp(uint)][32]
// [dateModified]               [unixTimestamp(uint)][32]
// [contentLenght]              [int][32]
// [content]                    [string][contentLenght]
