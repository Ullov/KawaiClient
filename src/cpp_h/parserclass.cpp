#include "parserclass.h"

ParserClass::ParserClass() {
    defExt = new FileIdentifier();
}

ParserClass::~ParserClass() {}

QJsonObject ParserClass::jsonObjectFromString(QString &content)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());

    if (!doc.isNull())
    {
        if (doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            return {}; // document is not an object
        }
    }
    else
    {
        return {}; // invalid JSON
    }

    return obj;
}

bool ParserClass::writeFile(std::string &data, std::string directory, std::string fileName)
{
    QDir dir = QDir(directory.c_str());
    bool qexi = dir.exists();
    if (!qexi)
    {
        qexi = dir.mkpath(".");
    }

    QFile file(dir.path() + '\\' + fileName.c_str());
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.writeRawData(data.c_str(), data.length());
    }
    else
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void ParserClass::recExtractJson(QJsonObject rootObject, std::string offset, std::string &data)
{
    std::string tmp;
    QStringList keysChain = rootObject.keys(); // Number; Null; Array; String; Object(aka array); Bool;
    for (int i = 0; i < keysChain.length(); i++)
    {
        if (rootObject.value(keysChain[i]).isString()) // is string
        {
            tmp = offset + keysChain[i].toStdString() + ": " + rootObject.value(keysChain[i]).toString().toStdString() + '\n';
            data += tmp;
        }
        else if (rootObject.value(keysChain[i]).isObject()) // is object
        {
            data += offset + "\\+" + keysChain[i].toStdString() + '\n';
            recExtractJson(rootObject.value(keysChain[i]).toObject(), offset + '\t', data);
        }
        else if (rootObject.value(keysChain[i]).isNull()) // is null
        {
            data += offset + keysChain[i].toStdString() + ": Is Null\n";
        }
        else if (rootObject.value(keysChain[i]).isBool()) // is bool
        {
            if (rootObject.value(keysChain[i]).toBool())
            {
                tmp = offset + keysChain[i].toStdString() + ": True\n";
            }
            else
            {
                tmp = offset + keysChain[i].toStdString() + ": False\n";
            }
            data += tmp;
        }
        else if (rootObject.value(keysChain[i]).isArray()) // is array
        {
            data += offset + "\\+" + keysChain[i].toStdString() + '\n';
            QJsonValue val = rootObject.value(keysChain[i]);
            QJsonArray arr = val.toArray();
            int c = 0;
            offset += '\t';
            foreach (const QJsonValue &v, arr)
            {
                if (v.isBool())
                {
                    if (v.toBool())
                    {
                        tmp = offset + std::to_string(c) + ": True\n";
                    }
                    else
                    {
                        tmp = offset + std::to_string(c) + ": False\n";
                    }
                    data += tmp;
                }
                else if (v.isDouble())
                {
                    tmp = offset + std::to_string(c) + ": " + v.toString().toStdString() + '\n';
                    data += tmp;
                }
                else if (v.isNull())
                {
                    data += offset + std::to_string(c) + ": Is Null\n";
                }
                else if (v.isObject())
                {
                    data += offset + "\\+" + std::to_string(c) + '\n';
                    recExtractJson(v.toObject(), offset + '\t', data);
                }
                else if (v.isString())
                {
                    tmp = offset + std::to_string(c) + ": " + v.toString().toStdString() + '\n';
                    data += tmp;
                }
                c++;
            }
            offset.pop_back();
        }
        else if (rootObject.value(keysChain[i]).isDouble()) // is double (aka number)
        {
            tmp = offset + keysChain[i].toStdString() + ": " + rootObject.value(keysChain[i]).toVariant().toString().toStdString() + '\n';
            data += tmp;
        }
    }
    offset.pop_back();
}

void ParserClass::writeJsonDataInFile(QJsonObject &object, std::string path, std::string fileName)
{
    std::string jData;
    jData.erase();
    recExtractJson(object, "", jData);
    writeFile(jData, path, fileName);
}

QJsonObject ParserClass::downloadJson(std::string url, CurlClass &pq)
{
    std::string result = pq.performing(url.c_str());
    QString tmpString = QString::fromStdString(result);
    QJsonObject object = jsonObjectFromString(tmpString);
    return object;
}

void ParserClass::downloadAndWriteFile(const std::string &url, CurlClass &pq, const std::string &path, const std::string &fileName)
{
    std::string result = pq.performing(url.c_str());
    writeFile(result, path, fileName);
}

void ParserClass::logging(std::string message)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    dt = dt + ' ' + message + '\n';

    QString forSlot = dt.c_str();
    emit logMessage(forSlot);

    QDir dir = QDir(halfPath.c_str());
    bool qexi = dir.exists();
    if (!qexi)
    {
        qexi = dir.mkpath(".");
    }

    QFile file(dir.path() + "\\log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.writeRawData(dt.c_str(), dt.length());
    }
    else
    {
        file.close();
    }
    file.close();
}

QJsonArray ParserClass::downloadJsonAsArray(std::string url, CurlClass &pq)
{
    std::string result = pq.performing(url.c_str());
    QString tmpString = QString::fromStdString(result);
    QJsonArray arr;
    QJsonDocument doc = QJsonDocument::fromJson(tmpString.toUtf8());

    if (!doc.isNull())
    {
        if (doc.isArray())
        {
            arr = doc.array();
        }
        else
        {
            return {}; // document is not an object
        }
    }
    else
    {
        return {}; // invalid JSON
    }

    return arr;
}

void ParserClass::eraseForbiddenChars(std::string &directory)
{
    char chars[] = "\\:*?<>\"|";
    for (int i = 0; i < 5; i++)
    {
        directory.erase(std::remove(directory.begin(), directory.end(), chars[i]), directory.end());
    }
}

void ParserClass::findMatchChars(std::string &data, std::string &pattern, std::vector<std::string> &result)
{
    result.clear();
    QRegularExpression re(pattern.c_str());
    QRegularExpressionMatchIterator i = re.globalMatch(data.c_str());
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        result.push_back(word.toStdString());
    }
}

void ParserClass::delay(int seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void ParserClass::replaceHtmlEntities(std::string &wrongString)
{
    std::vector<std::string> htmlEntities;
    htmlEntities.push_back("&amp;");
    std::vector<std::string> rightSumbols;
    rightSumbols.push_back("&");

    /*for (int i = 0; i < htmlEntities.size(); i++)
    {
        size_t startPos = 0;
        while ((startPos = wrongString.find(htmlEntities[i], startPos)) != std::string::npos)
        {
            wrongString.replace(startPos, htmlEntities[i].length(), rightSumbols[i]);
            startPos += rightSumbols[i].length();
        }
    }*/
    replace(wrongString, htmlEntities, rightSumbols);
}

void ParserClass::replace(std::string &input, std::vector<std::string> whatReplace, std::vector<std::string> onWhatReplace)
{
    for (int i = 0; i < whatReplace.size(); i++)
    {
        size_t startPos = 0;
        while ((startPos = input.find(whatReplace[i], startPos)) != std::string::npos)
        {
            input.replace(startPos, whatReplace[i].length(), onWhatReplace[i]);
            startPos += onWhatReplace[i].length();
        }
    }
}

std::string ParserClass::defineExtension(const std::string &file)
{
    QStringList tmp = defExt->identifyFileFromString(QString::fromStdString(file));
    return tmp[0].toStdString();
}

void ParserClass::downloadAndWriteFileWithDefinedExtension(const std::string &url, CurlClass &pq, const std::string &path, const std::string &fileName)
{
    std::string fileString = pq.performing(url.c_str());
    std::string extension = defineExtension(fileString);
    writeFile(fileString, path, fileName + extension);
}
