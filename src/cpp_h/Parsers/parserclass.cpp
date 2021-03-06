#include "parserclass.h"

#include "../KTools/fileidentifier.h"
#include "../KTools/curl.h"
#include "../KTools/converter.h"
#include "../KTools/options.h"
#include "../KTools/log.h"
#include "../KTools/exforstring.h"
#include <thread>
#include "parsersqmlinterface.h"
#include <QJsonArray>

Parsers::ParserClass::ParserClass()
{
    defExt = new KTools::FileIdentifier();
    cc = new KTools::Curl();
}

Parsers::ParserClass::~ParserClass()
{
    delete defExt;
    delete cc;
}

void Parsers::ParserClass::recExtractJson(const QJsonObject &rootObject, QString offset, QString &data)
{
    QString tmp;
    QStringList keysChain = rootObject.keys(); // Number; Null; Array; String; Object(aka array); Bool;
    for (int i = 0; i < keysChain.length(); i++)
    {
        if (rootObject.value(keysChain[i]).isString()) // is string
            data += offset + keysChain[i] + ": " + rootObject.value(keysChain[i]).toString() + '\n';
        else if (rootObject.value(keysChain[i]).isObject()) // is object
        {
            data += offset + "\\+" + keysChain[i] + '\n';
            recExtractJson(rootObject.value(keysChain[i]).toObject(), offset + '\t', data);
        }
        else if (rootObject.value(keysChain[i]).isNull()) // is null
            data += offset + keysChain[i] + ": Is Null\n";
        else if (rootObject.value(keysChain[i]).isBool()) // is bool
        {
            if (rootObject.value(keysChain[i]).toBool())
                tmp = offset + keysChain[i] + ": True\n";
            else
                tmp = offset + keysChain[i] + ": False\n";
            data += tmp;
        }
        else if (rootObject.value(keysChain[i]).isArray()) // is array
        {
            data += offset + "\\+" + keysChain[i] + '\n';
            QJsonValue val = rootObject.value(keysChain[i]);
            QJsonArray arr = val.toArray();
            int c = 0;
            offset += '\t';
            foreach (const QJsonValue &v, arr)
            {
                if (v.isBool())
                {
                    if (v.toBool())
                        tmp = offset + QString::number(c) + ": True\n";
                    else
                        tmp = offset + QString::number(c) + ": False\n";
                    data += tmp;
                }
                else if (v.isDouble())
                    data += offset + QString::number(c) + ": " + v.toString() + '\n';
                else if (v.isNull())
                    data += offset + QString::number(c) + ": Is Null\n";
                else if (v.isObject())
                {
                    data += offset + "\\+" + QString::number(c) + '\n';
                    recExtractJson(v.toObject(), offset + '\t', data);
                }
                else if (v.isString())
                    data += offset + QString::number(c) + ": " + v.toString() + '\n';
                c++;
            }
            offset.chop(1);
        }
        else if (rootObject.value(keysChain[i]).isDouble()) // is double (aka number)
            data += offset + keysChain[i] + ": " + rootObject.value(keysChain[i]).toVariant().toString() + '\n';
    }
    offset.chop(1);
}

void Parsers::ParserClass::writeJsonDataInFile(const QJsonObject &object, const QString &path, const QString &fileName)
{
    QString jData;
    jData = QString();
    recExtractJson(object, "", jData);
    KTools::File::writeFile(jData.toUtf8(), path, fileName);
}

QJsonObject Parsers::ParserClass::downloadJson(const QString url)
{
    QByteArray result = cc->performing(url.toUtf8());
    QJsonObject object = KTools::Converter::convert<QString, QJsonObject>(result);
    return object;
}

void Parsers::ParserClass::downloadAndWriteFile(const QString &url, const QString &path, const QString &fileName)
{
    QByteArray result = cc->performing(url.toUtf8());
    KTools::File::writeFile(result, path, fileName);
}

QJsonArray Parsers::ParserClass::downloadJsonAsArray(const QString &url)
{
    QByteArray result = cc->performing(url.toUtf8());
    QJsonArray arr = KTools::Converter::convert<QString, QJsonArray>(result);
    return arr;
}

void Parsers::ParserClass::delay(const int &seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void Parsers::ParserClass::downloadAndWriteFileWithDefinedExtension(const QString &url, const QString &path, const QString &fileName)
{
    QByteArray fileString = cc->performing(url.toUtf8());
    QString extension = defineExtension(fileString);
    KTools::File::writeFile(fileString, path, fileName + extension);
}

QString Parsers::ParserClass::defineExtension(const QByteArray &file)
{
    QStringList tmp = KTools::FileIdentifier::identifyFileFromString(file);
    return tmp[0];
}

QVector<QJsonObject> Parsers::ParserClass::extractJsonObjectFromText(const QString &text)
{
    QString pattern;
    QVector<QString> regexResult;
    QVector<QJsonObject> objects;
    pattern = "({\".+})+"; // =*({(\")(.)+})+

    KTools::ExForString::executeRegex(text, pattern, regexResult);
    for (int i = 0; i < regexResult.size(); i++)
    {
        QString tmp = regexResult[i];
        QJsonObject obj = KTools::Converter::convert<QString, QJsonObject>(tmp);
        if (!obj.isEmpty())
            objects.push_back(obj);
    }
    return objects;
}

void Parsers::ParserClass::writeInfoLog(const QString &message)
{
    KTools::Log::writeCustomLog(message, parsersNames[parserType], KTools::Enums::LogType::Info, rootPath, logFile);
}

void Parsers::ParserClass::setParserType(const Parsers type)
{
    parserType = type;
    basePath = KTools::Options::rootProgramPath + '/' + parsersWritePathes[type];
    parserName = parsersNames[type];
    //cc->downloaderType = type;
}

void Parsers::ParserClass::endDownloadingFunction(const int parserMode, const QJsonObject &data, const QVector<QByteArray> &binaryContent)
{
    QList<int> mode;
    mode.push_back(static_cast<int>(parserType));
    mode.push_back(parserMode);
    ParsersQmlInterface::obj.emitParserClassDownloadingFinished(mode, data, binaryContent);
}

void Parsers::ParserClass::setRootPath(const QString &name)
{
    QString tmp = name;
    KTools::Converter::toNtfsCompatibleString(tmp);
    rootPath = basePath + '/' + tmp;
    for (int i = 0; KTools::File::dirExist(rootPath); i++)
        rootPath = basePath + '/' + tmp + '[' + QString::number(i) + ']';
}

void Parsers::registerQmlTypes()
{
    qmlRegisterUncreatableMetaObject(staticMetaObject, "PEnums", 1, 0, "Parsers", "Is enum");
    qRegisterMetaType<Parsers>("ParsersParsers");
}

