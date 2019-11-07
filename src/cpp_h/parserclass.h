#ifndef PARSERCLASS_H
#define PARSERCLASS_H


#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDir>
#include <fstream>
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

class ParserClass : public QObject
{
    Q_OBJECT
public:
    ParserClass();
    ~ParserClass();

    std::string basePath; // path entered by user
    Logging *logger;


protected:
    QJsonObject jsonObjectFromString(QString &content);
    bool writeFile(std::string &data, std::string directory, std::string fileName);
    void recExtractJson(QJsonObject rootObject, std::string offset, std::string &data);
    void writeJsonDataInFile(QJsonObject &object, std::string path, std::string fileName);
    QJsonObject downloadJson(std::string url, CurlClass &pq);
    void downloadAndWriteFile(std::string url, CurlClass &pq, std::string path, std::string fileName);
    void logging(std::string message);
    QJsonArray downloadJsonAsArray(std::string url, CurlClass &pq);
    void eraseForbiddenChars(std::string &line);
    void findMatchChars(std::string &data, std::string &pattern, std::vector<std::string> &result);
    void delay(int seconds);
    void replaceHtmlEntities(std::string &wrongString);
    void replace(std::string &input, std::vector<std::string> whatReplace, std::vector<std::string> onWhatReplace);
    std::string defineExtension(const std::string &file);

    std::string currUrl; // string for current link. added for simplification code
    std::string halfPath; // part file path that permanent
    std::vector<std::string> chunk;
    std::string pattern;

signals:
    void downloadingFinished(QStringList mode, QJsonObject data);
    void logMessage(QString message);
};

#endif // PARSERCLASS_H
