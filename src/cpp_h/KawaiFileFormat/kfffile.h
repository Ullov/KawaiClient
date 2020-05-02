#ifndef KFFFILE_H
#define KFFFILE_H

#include "kawaifileformat.h"
#include "../KTools/converter.h"
#include "../KTools/file.h"


class KffFile
{
public:
    KffFile(KawaiFileFormat *file, const QString path);
    ~KffFile();
// enums
    enum FileTypes : qint32
    {
        Folder = 0,
        File = 1
    };

// structures
    struct FileHeader
    {
        quint64 headerLenght;
        qint32 type; // always 1 if not this is not file
        qint32 filenameLenght;
        QString filename;
        qint32 pathLenght;
        QString path;
        quint32 dateCreated;
        quint32 dateModified;
        qint32 contentLenght; // in bytes
    };
    struct FolderHeader
    {
        quint64 headerLenght;
        qint32 type;
        qint32 dirnameLenght;
        QString dirname;
        qint32 pathLenght;
        QString path;
        quint32 dateCreated;
        quint32 dateModified;
        quint64 filesNumber;
        QVector<qint64> addresToFile;
    };
    struct FileStructure
    {
        FileHeader header;
        QByteArray data;
    };
    struct FolderStructure
    {
        QByteArray header;
        QVector<qint64> fiilesStartPos;
    };

private:
// constants
    static constexpr int contentLenght = 8112;
    static constexpr QChar dirSeparator = '/';

// variables
    KawaiFileFormat *kff;
    qint64 lastClusterAddress;
    QByteArray *clusters;
    FileStructure fileStruct;
    FolderStructure folderStruct;
    FileHeader fileHeaderStruct;
    FolderHeader folderHeaderStruct;
    KTools::File *nativeFs;

// functions
    void appendBitset(const QBitArray &bitArr, std::bitset<contentLenght> &stdBitset, const int startPos);
    qint64 write(const QByteArray &data);
    qint64 writeCluster(const QBitArray &data, const qint64 &nextCluster);
    qint64 scanForClearCluster();
    QByteArray* concatenateClusters(const qint64 &pos, const qint64 &lenght, const qint16 frontOffset = 0);
    void readHeader(const qint64 &pos, const FileTypes ft);
    template<typename T>
    T readHeaderParam(quint64 &offset, const QByteArray *rawHeader, int paramLenght = 0);
    void readAllHeaderParams(const qint64 &pos, const FileTypes &ft);
    template<typename T>
    T* getFileStructure(const qint64 &pos);
    template<typename T>
    T read(const qint64 &pos, const qint64 &lenght);

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
};

#endif // KFFFILE_H
