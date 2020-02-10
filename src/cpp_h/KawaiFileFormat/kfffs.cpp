#include "kfffs.h"

KffFs::KffFs() {}

void KffFs::open(NativeFs &localNativeFs)
{
    nativeFs = &localNativeFs;
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
    if (posInCluster )
}
