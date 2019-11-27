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

    std::string basePath; // path entered by user
    Logging *logger;


protected:
    // JSON
    QJsonObject jsonObjectFromString(QString &content);
    void recExtractJson(QJsonObject rootObject, std::string offset, std::string &data);
    QJsonObject downloadJson(std::string url, CurlClass &pq);
    QJsonArray downloadJsonAsArray(std::string url, CurlClass &pq);

    // File IO operations
    bool writeFile(std::string &data, std::string directory, std::string fileName);
    void downloadAndWriteFile(const std::string &url, CurlClass &pq, const std::string &path, const std::string &fileName);
    void downloadAndWriteFileWithDefinedExtension(const std::string &url, CurlClass &pq, const std::string &path, const std::string &fileName);

    // String operations
    void eraseForbiddenChars(std::string &line);
    void findMatchChars(std::string &data, std::string &pattern, std::vector<std::string> &result);
    void replace(std::string &input, std::vector<std::string> whatReplace, std::vector<std::string> onWhatReplace);
    void replaceHtmlEntities(std::string &wrongString);
    std::string intToUtf8(const int &code);
    void textWithWindows1251ToUtf8(std::string &text);
    void deleteNtfsConflictingChars(std::string &data);

    // Other/Mixed
    void writeJsonDataInFile(QJsonObject &object, std::string path, std::string fileName);
    void logging(std::string message);
    void delay(int seconds);
    std::vector<QJsonObject> extractJsonObjectFromText(std::string text);
    std::string defineExtension(const std::string &file);


    // variables
    std::string currUrl;
    std::string halfPath; // part file path that permanent
    std::vector<std::string> chunk; // header for curl requests
    std::string pattern; // pattern for regex
    FileIdentifier *defExt;

signals:
    void downloadingFinished(QStringList mode, QJsonObject data);
    void logMessage(QString message);
};

#endif // PARSERCLASS_H
