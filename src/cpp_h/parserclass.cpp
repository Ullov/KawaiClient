#include "parserclass.h"

ParserClass::ParserClass()
{
    defExt = new FileIdentifier();
}

ParserClass::~ParserClass() {}

QJsonObject ParserClass::jsonObjectFromString(const QString &content)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    if (!doc.isNull())
    {
        if (doc.isObject())
            obj = doc.object();
        else
            return {}; // document is not an object
    }
    else
        return {}; // invalid JSON
    return obj;
}

bool ParserClass::writeFile(const QByteArray &data, const QString &directory, const QString &fileName)
{
    QDir dir = QDir(directory);
    bool qexi = dir.exists();
    if (!qexi)
        qexi = dir.mkpath("."); // if derictory does not exist make it

    QFile file(dir.path() + '\\' + fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.writeRawData(data, data.length());
    }
    else
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void ParserClass::recExtractJson(const QJsonObject &rootObject, QString offset, QString &data)
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

void ParserClass::writeJsonDataInFile(const QJsonObject &object, const QString &path, const QString &fileName)
{
    QString jData;
    jData = QString();
    recExtractJson(object, "", jData);
    writeFile(jData.toUtf8(), path, fileName);
}

QJsonObject ParserClass::downloadJson(const QString url, CurlClass &pq)
{
    QByteArray result = pq.performing(url.toUtf8());
    QJsonObject object = jsonObjectFromString(result);
    return object;
}

void ParserClass::downloadAndWriteFile(const QString &url, CurlClass &pq, const QString &path, const QString &fileName)
{
    QByteArray result = pq.performing(url.toUtf8());
    writeFile(result, path, fileName);
}

QJsonArray ParserClass::downloadJsonAsArray(const QString &url, CurlClass &pq)
{
    QByteArray result = pq.performing(url.toUtf8());
    QJsonArray arr;
    QJsonDocument doc = QJsonDocument::fromJson(result);
    if (!doc.isNull())
    {
        if (doc.isArray())
            arr = doc.array();
        else
            return {}; // document is not an object
    }
    else
        return {}; // invalid JSON
    return arr;
}

void ParserClass::findMatchChars(const QString &data, const QString &pattern, QVector<QString> &result)
{
    result.clear();
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        result.append(match.captured(1));
    }
}

void ParserClass::delay(const int &seconds)
{
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

void ParserClass::replace(QString &inp, const QVector<QString> &whatReplace, const QVector<QString> &onWhatReplace)
{
    std::string input = inp.toStdString();
    for (int i = 0; i < whatReplace.size(); i++)
    {
        size_t startPos = 0;
        while ((startPos = input.find(whatReplace[i].toStdString(), startPos)) != std::string::npos)
        {
            input.replace(startPos, whatReplace[i].length(), onWhatReplace[i].toStdString());
            startPos += onWhatReplace[i].length();
        }
    }
    inp = QString::fromStdString(input);
}

void ParserClass::replaceHtmlEntities(QString &wrongString)
{
    QVector<QString> htmlEntities;
    htmlEntities.push_back("&amp;");
    htmlEntities.push_back("&quot;");
    htmlEntities.push_back("&apos;");
    htmlEntities.push_back("&it;");
    htmlEntities.push_back("&gt;");
    QVector<QString> rightSumbols;
    rightSumbols.push_back("&");
    rightSumbols.push_back("\"");
    rightSumbols.push_back("'");
    rightSumbols.push_back("<");
    rightSumbols.push_back(">");
    replace(wrongString, htmlEntities, rightSumbols);
}

void ParserClass::downloadAndWriteFileWithDefinedExtension(const QString &url, CurlClass &pq, const QString &path, const QString &fileName)
{
    QByteArray fileString = pq.performing(url.toUtf8());
    QString extension = defineExtension(fileString);
    writeFile(fileString, path, fileName + extension);
}

QString ParserClass::defineExtension(const QByteArray &file)
{
    QStringList tmp = defExt->identifyFileFromString(file);
    return tmp[0];
}

QVector<QJsonObject> ParserClass::extractJsonObjectFromText(const QString &text)
{
    QString pattern;
    QVector<QString> regexResult;
    QVector<QJsonObject> objects;
    pattern = "=*({(\")(.)+})+";
    findMatchChars(text, pattern, regexResult);
    for (int i = 0; i < regexResult.size(); i++)
    {
        QString tmp = regexResult[i];
        QJsonObject obj = jsonObjectFromString(tmp);
        if (!obj.isEmpty())
            objects.push_back(obj);
    }
    return objects;
}

QString ParserClass::intToUtf8(const int &code)
{
    unsigned short tmp = static_cast<unsigned short>(code);
    QString tmp2 = QString::fromUtf16(&tmp);
    tmp2.resize(1);
    return tmp2;
}

void ParserClass::textWithWindows1251ToUtf8(QString &text)
{
    QVector<QString> windows1251;
    for (int i = 0; i < 253; i++) // lenght 252
        windows1251.push_back(intToUtf8(i));
    QVector<QString> utf8; // lenght 254
    for (int i = 1040; i < 1109; i++)
        utf8.push_back(intToUtf8(i));
    replace(text, windows1251, utf8);
}

void ParserClass::deleteNtfsConflictingChars(QString &data)
{
    QVector<QString> wrongChars;
    wrongChars.push_back("\"");
    wrongChars.push_back("|");
    wrongChars.push_back("/");
    wrongChars.push_back(":");
    wrongChars.push_back("*");
    wrongChars.push_back("?");
    wrongChars.push_back(">");
    wrongChars.push_back("<");
    QVector<QString> voids;
    for (int i = 0; i < wrongChars.size(); i++)
        voids.push_back("");
    replace(data, wrongChars, voids);
}
