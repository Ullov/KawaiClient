#include "kfffs.h"

KffFs::KffFs() {}

bool KffFs::open(NativeFs &localNativeFs)
{
    nativeFs = &localNativeFs;
    nativeFs->seek(0);
    QByteArray signature = nativeFs->read<QByteArray>(3);
    nativeFs->seek(3);
    qint64 size = nativeFs->read<qint64>();
    if (signature != "KFF" && size != nativeFs->size())
        return false;
    else
    {
        nativeFs->seek(3 + 8);
        inodesBlockLenght = nativeFs->read<qint64>();
        allInodesNumber = inodesBlockLenght / InodeFieldsSize::SumSize;
    }
}

qint64 KffFs::pos()
{
    return position;
}

void KffFs::seek(const qint64 &pos)
{
    if (pos < position)
    {
        searchRequestedPosition(pos, 0);
    }
    else
    {
        qint16 posInCluster = positionInCluster();
        qint64 remainedWalk = pos - posInCluster;
        qint64 startClusterPos = position + (ClusterFieldsSize::Content - posInCluster);
        searchRequestedPosition(remainedWalk, startClusterPos);
    }
}

void KffFs::searchRequestedPosition(qint64 remainedWalk, const qint64 &startClusterPos)
{
    nativeFs->seek(startClusterPos);
    while (remainedWalk > 0)
    {
        qint16 contLen = nativeFs->read<qint16>();
        if (contLen != 0)
        {
            if (remainedWalk > contLen)
            {
                remainedWalk -= contLen;
                nativeFs->seek(nativeFs->pos() + ClusterFieldsSize::ContentLenght);
                nextCluster = nativeFs->read<qint64>();
                nativeFs->seek(nextCluster);
            }
            else
            {
                nativeFs->seek(nativeFs->pos() + ClusterFieldsSize::ContentLenght);
                nextCluster = nativeFs->read<qint64>();
                nativeFs->seek(nativeFs->pos() + ClusterFieldsSize::NextCluster + remainedWalk);
                position = nativeFs->pos();
                break;
            }
        }
        else
        {
            nativeFs->seek(nativeFs->pos() + ClusterFieldsSize::ContentLenght);
            qint64 localNextCluster = nativeFs->read<qint64>();
            nativeFs->seek(localNextCluster);
        }
    }
}

qint16 KffFs::positionInCluster()
{
    return position % ClusterFieldsSize::ContentLenght;
}

template<typename T>
void KffFs::write(const T &data)
{
    qint16 posInCluster = positionInCluster();
    //if (posInCluster )
}

bool KffFs::getInode(const qint64 &inodeNumber)
{
    if (inodeNumber > allInodesNumber)
        return false;

    qint64 offsetForInode = inodeOffset + (inodeNumber * InodeFieldsSize::SumSize);
    nativeFs->seek(offsetForInode);
    inode->headerPos = nativeFs->read<qint64>();
    nativeFs->seek(offsetForInode + 8);
    inode->contentPos = nativeFs->read<qint64>();
}
/*
 * all sizes in bits
 * inode structure:
 * headerPos    [64][int]
 * contentPos   [64][int]
 *
 * wholoe inode size: 128 bits
 * reccomend allocate inodes for general use: 2,000,000 = 244.14 MB
 */
