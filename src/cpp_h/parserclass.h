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


protected:
    // JSON
    QJsonObject jsonObjectFromString(const QString &content);
    void recExtractJson(const QJsonObject &rootObject, QString offset, QString &data);
    QJsonObject downloadJson(const QString url, CurlClass &pq);
    QJsonArray downloadJsonAsArray(const QString &url, CurlClass &pq);

    // File IO operations
    bool writeFile(const QByteArray &data, const QString &directory, const QString &fileName);
    void downloadAndWriteFile(const QString &url, CurlClass &pq, const QString &path, const QString &fileName);
    void downloadAndWriteFileWithDefinedExtension(const QString &url, CurlClass &pq, const QString &path, const QString &fileName);

    // String operations
    void findMatchChars(const QString &data, const QString &pattern, QVector<QString> &result);
    void replace(QString &inp, const QVector<QString> &whatReplace, const QVector<QString> &onWhatReplace);
    void replaceHtmlEntities(QString &wrongString);
    QString intToUtf8(const int &code);
    void textWithWindows1251ToUtf8(QString &text);
    void deleteNtfsConflictingChars(QString &data);

    // Other/Mixed
    void writeJsonDataInFile(const QJsonObject &object, const QString &path, const QString &fileName);
    void delay(const int &seconds);
    QVector<QJsonObject> extractJsonObjectFromText(const QString &text);
    QString defineExtension(const QByteArray &file);


    // variables
    QString currUrl;
    QString rootPath; // part file path that permanent
    std::vector<std::string> chunk; // header for curl requests
    FileIdentifier *defExt;

signals:
    void downloadingFinished(QStringList mode, QJsonObject data);
    void logMessage(QString message);
};

#endif // PARSERCLASS_H
