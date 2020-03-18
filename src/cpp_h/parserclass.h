#ifndef PARSERCLASS_H
#define PARSERCLASS_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QVariant>
#include <ctime>
#include <thread>
#include <chrono>
#include "curlclass.h"
#include "logging.h"
#include "fileidentifier.h"
#include "KTools/kawaiconverter.h"
#include "KTools/nativefs.h"
#include "KTools/HtmlAstMaker/htmlobject.h"
#include "optionshandler.h"
#include "KTools/kenums.h"

class ParserClass : public QObject
{
    Q_OBJECT
public:
    ParserClass();
    ~ParserClass();

    CurlClass *cc;
    KEnums::Parsers parserType;

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
    void writeInfoLog(const QString &message);
    void setParserType(const KEnums::Parsers type);

    // variables
    QString currUrl;
    QString rootPath; // in this paths writes log file
    std::vector<std::string> chunk; // header for curl requests
    FileIdentifier *defExt;
    QString logPath;
    const QString logFile = "log.txt";
    QString basePath;
    QString parserName;

signals:
    void downloadingFinished(const QStringList mode, const QJsonObject data);
    void logMessage(const QString message);
};

#endif // PARSERCLASS_H
