#ifndef KFFFILECLASS_H
#define KFFFILECLASS_H

#include "../../KTools/kawaiconverter.h"
#include "../../KTools/nativefs.h"
#include <QChar>

class KffFileClass
{
public:
    KffFileClass();

// constants
    static constexpr int contentLenght = 8112;
    static constexpr QChar dirSeparator = '/';

// variables
    qint64 lastClusterAddress;
    QByteArray *clusters;
    KTools::File *nativeFs;

// enums
    enum NumberTypesSize : int
    {
        Int64 = 8,
        Int32 = 4,
        Int16 = 2,
        Int8 = 1,
        Long = 8,
        Int = 4,
        Short = 2,
        Char = 1,
        Float = 4,
        Double = 8
    };

// functions
    bool openFromNativeFs(const QString &path);
    qint64 write(const QByteArray &data);

protected:
// enums
    enum FileTypeCodes : qint32
    {
        KffDir = 0
    };

// structures
    struct ReadedClusters
    {
        QVector<qint64> addreses;
        QVector<qint16> contentLenght;
    };
    struct Header
    {
        quint64 headerLenght;
        qint32 type;
        qint32 nameLenght;
        QString name;
        qint32 pathLenght;
        QString path;
        quint32 dateCreated;
        quint32 dateModified;
        qint64 contentAddres;
        ReadedClusters clusters;
    };
    struct Content
    {
        QByteArray content;
        ReadedClusters clusters;
    };

// variables
    ReadedClusters *readedClusters;

// functions
    void writeCluster(const QByteArray &data, const qint64 &nextCluster);
    qint64 scanForClearCluster();
    QByteArray* readClusters(const qint64 &pos, const qint64 &lenght, ReadedClusters &localReadedClusters, qint16 frontOffset = 0);
    template<typename T>
    T readHeaderParam(quint64 &offset, const QByteArray *rawHeader, int paramLenght = 0);
    template<typename T>
    T readRawData(const qint64 &pos, const qint64 &lenght, KTools::File &scope);
    void deleteData(ReadedClusters &localReadedClusters);
    template<typename T>
    void appendByteArray(QByteArray &arr, const T &addData);
};

#endif // KFFFILECLASS_H
