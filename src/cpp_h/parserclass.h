#ifndef PARSERCLASS_H
#define PARSERCLASS_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <QVariant>
#include <ctime>
#include "curlclass.h"
#include <QObject>
#include <QRegularExpression>
#include <thread>
#include <chrono>
#include <QDataStream>
#include <QJsonValue>
#include <QTextCodec>
#include "logging.h"
#include "fileidentifier.h"

class ParserClass : public QObject
{
    Q_OBJECT
public:
    ParserClass();
    ~ParserClass();

    QString basePath; // path entered by user
    Logging *logger;
    CurlClass *cc = new CurlClass();

protected:
    // JSON
    QJsonObject jsonObjectFromString(const QString &content);
    void recExtractJson(const QJsonObject &rootObject, QString offset, QString &data);
    QJsonObject downloadJson(const QString url);
    QJsonArray downloadJsonAsArray(const QString &url);
    QJsonArray jsonArrayFromString(const QString &content);

    // File IO operations
    bool writeFile(const QByteArray &data, const QString &directory, const QString &fileName);
    void downloadAndWriteFile(const QString &url, const QString &path, const QString &fileName);
    void downloadAndWriteFileWithDefinedExtension(const QString &url, const QString &path, const QString &fileName);

    // String operations
    void findMatchChars(const QString &data, const QString &pattern, QVector<QString> &result);
    void findMatchChars(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult);
    void replace(QString &inp, const QVector<QString> &whatReplace, const QVector<QString> &onWhatReplace);
    void replace(QByteArray &inp, const QVector<QByteArray> &whatReplace, const QVector<QByteArray> &onWhatReplace);
    void replaceHtmlEntities(QString &wrongString);
    void replaceHtmlEntities(QByteArray &wrongString);
    QString intToUtf8(const int &code);
    void deleteNtfsConflictingChars(QString &data);
    void percentEncodingToUtf8(QString &data);
    QString convertNationalEncodingToUtf8(const QByteArray &inputEncoding, const QByteArray &data);
    void replaceHtmlHexCodes(QString &data);

    // Other/Mixed
    void writeJsonDataInFile(const QJsonObject &object, const QString &path, const QString &fileName);
    void delay(const int &seconds);
    QVector<QJsonObject> extractJsonObjectFromText(const QString &text);
    QString defineExtension(const QByteArray &file);
    bool FileExist(const QString &path);
    bool FolderExist(const QString &path);
    void recursiveMakePath(const QString &path);



    // variables
    QString currUrl;
    QString rootPath; // part file path that permanent
    std::vector<std::string> chunk; // header for curl requests
    FileIdentifier *defExt;

signals:
    void downloadingFinished(QStringList mode, QJsonObject data);
    void logMessage(QString message);

protected slots:
    void asyncWriteFile(const QByteArray &data, const QString &directory, const QString &fileName);
};

#endif // PARSERCLASS_H
