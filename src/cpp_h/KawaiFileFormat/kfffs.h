#ifndef KFFFS_H
#define KFFFS_H

#include "../KTools/nativefs.h"
#include "../KTools/kawaiconverter.h"

class KffFs
{
public:
    KffFs();

// functions
    bool open(NativeFs &localNativeFs);
    qint64 pos();
    void seek(const qint64 &pos);
    template<typename T>
    void write(const T &data);
    bool getInode(const qint64 &inodeNumber);

private:
// enumerations
    enum ClusterFieldsSize
    {// all sizes in bits
        ContentLenght = 2,
        NextCluster = 8,
        Content = 1014,
        SumLenght = 1024
    };
    enum InodeFieldsSize : qint16
    {
        HeaderPos = 64,
        ContentPos = 64,
        SumSize = 128
    };

// structures
    struct InodeStruct
    {
       qint64 headerPos;
       qint64 contentPos;
    };
// variables
    NativeFs *nativeFs;
    qint64 position;
    qint64 nextCluster;
    qint64 inodesBlockLenght;
    qint64 allInodesNumber;
    qint64 dataOffset;
    qint8 inodeOffset;
    InodeStruct *inode;
// functions
    void searchRequestedPosition(qint64 remainedWalk, const qint64 &startClusterPos);
    qint16 positionInCluster();

public:
};

#endif // KFFFS_H
