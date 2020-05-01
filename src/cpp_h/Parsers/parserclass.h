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
//#include "../KTools/kenums.h"
//#include "../KTools/logging.h"
//#include "../KTools/kawaiconverter.h"
//#include "../KTools/nativefs.h"
//#include "../KTools/HtmlAstMaker/htmlobject.h"
#include "../KTools/kenums.h"
#include "../KTools/fileidentifier.h"
#include "../KTools/curlclass.h"
#include "parsersqmlinterface.h"
#include "../KTools/optionshandler.h"

namespace Parsers
{
    class ParserClass
    {
    public:
        ParserClass();
        ~ParserClass();

        KTools::Curl *cc;
        KTools::Enums::Parsers parserType;

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
        void setParserType(const KTools::Enums::Parsers type);
        void endDownloadingFunction(const int parserMode, const QJsonObject &data = QJsonObject(), const QVector<QByteArray> &binaryContent = QVector<QByteArray>());

        // variables
        QString currUrl;
        QString rootPath; // in this paths writes log file
        QVector<QByteArray> chunk; // header for curl requests
        KTools::FileIdentifier *defExt;
        QString logPath;
        const QString logFile = "log.txt";
        QString basePath;
        QString parserName;
    };
}

#endif // PARSERCLASS_H
