#ifndef KAWAIFILEFORMAT_H
#define KAWAIFILEFORMAT_H

#include <QString>
#include <QFileInfo>
#include <bitset>
#include <QBitArray>
#include <QDateTime>
#include <QMap>
#include <QDataStream>

class KawaiFileFormat
{
public:
    KawaiFileFormat();

    bool open(const QString &path);
    bool create(const QString &path);
    //qint64 write(const QByteArray &data);
    qint64 size();
    void makeDir(const QString &path);
    bool exist(const QString &path);
    qint64 cd(const QString &path, const bool keepCurrentPath = false);
    qint64 readDir(const QString &dirName);
    QByteArray readDir(const qint64 &pos);
    bool readFile(const QString &path, const QString &fileName);
    bool makeFile(const QByteArray &content, const QString &path, const QString &filename);
    //void makeFile();

private:
    //static constexpr QChar root = '/';


// variables
    QFile *file;
    //qint64 lastClusterAddress;
    QMap<QString, QByteArray> currentDir;
    QVector<qint64> currentDirFilesAddresses;
    QString currentDirPath;
    qint64 currentDirPos;
    qint64 lastFilePos;
    QDataStream *fStream;


// functions
    //bool seek(const qint64 &pos);
    //qint64 writeCluster(const QBitArray &data, const qint64 &nextCluster);
    //qint64 scanForClearCluster();
    //void appendBitset(const QBitArray &bitArr, std::bitset<contentLenght> &stdBitset, const int startPos);
    //qint64 pos();
    QStringList getPathInList(const QString &path);
    QByteArray read(const qint64 &firstClusterPos);
    qint64 writeFile(const QString &path, const QString &filename, const QByteArray &fileData);

    enum NumberTypesSize
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

#endif // KAWAIFILEFORMAT_H
