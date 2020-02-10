#ifndef KFFFS_H
#define KFFFS_H

#include "nativefs.h"
#include "kawaiconverter.h"

class KffFs
{
public:
    KffFs();

// enumerations
private:
    enum ClusterFieldsSize
    {// all sizes in bits
        ContentLenght = 2,
        NextCluster = 8,
        Content = 1014,
        SumLenght = 1024
    };

// variables
private:
    NativeFs *nativeFs;
    qint64 position;
    qint64 nextCluster;

// functions
public:
    void open(NativeFs &localNativeFs);
    qint64 pos();
    void seek(const qint64 &pos);
    template<typename T>
    void write(const T &data);
private:
    void searchRequestedPosition(qint64 remainedWalk, const qint64 &startClusterPos);
    qint16 positionInCluster();


};

#endif // KFFFS_H
