#ifndef KFFSTREAM_H
#define KFFSTREAM_H

#include "../KTools/file.h"
#include "../KTools/log.h"

namespace Kff
{
    class Stream
    {
    public:
        Stream(KTools::File &NfFile, const qint64 dbStart, const qint64 inStart); // dbStart = dataBlockStart; inStart = inodeBlockStart

        qint64 size();
        void seek(const qint64 pos);
        qint64 pos();
        void write(const QByteArray &data);
        bool atEnd();
        QByteArray read(qint64 lenght);

        void addClusterPos(const qint64 pos);

    private:
        bool findClearInode();
        qint64 appendCluster(); // append or finds clear cluster for stream and sets pos to it start
        void writeInInode(qint64 firstClusterPos, qint64 contentLenght);
        void writeInCluster(const QByteArray &content);
        void writeInCluster(const qint64 nextBlockPos, const qint64 localCurrBlockNumber);
        qint64 lastClusterClearSpace();
        qint64 lastClusterUsedSpace();
        void toNextCluster();

        KTools::File *fileInNativeFs;
        qint64 inodeBlockStart;
        qint64 dataBlockStart;
        QVector<qint64> clustersPos;
        qint64 currClusterNumber;
        qint64 posInCurrCluster;
        qint64 inodePos;
        qint64 streamLenght = 0;
        qint64 globalPos;

    public:
        static const qint64 contentLenght;
        static const qint64 clusterLenght;
        static const qint64 eos;
        template <typename T>
        static const T voidPtr();
        static const QByteArray voidCluster(const qint64 previousClusterPos);
    };
}


#endif // KFFSTREAM_H
