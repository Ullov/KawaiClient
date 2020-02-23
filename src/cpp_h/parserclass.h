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
#include "KTools/kawaiconverter.h"
#include "KTools/nativefs.h"

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
    void recExtractJson(const QJsonObject &rootObject, QString offset, QString &data);
    QJsonObject downloadJson(const QString url);
    QJsonArray downloadJsonAsArray(const QString &url);

    // File IO operations
    void downloadAndWriteFile(const QString &url, const QString &path, const QString &fileName);
    void downloadAndWriteFileWithDefinedExtension(const QString &url, const QString &path, const QString &fileName);

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
