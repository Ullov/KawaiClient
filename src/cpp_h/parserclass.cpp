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
    recursiveMakePath(directory);
    QFile file(directory + '\\' + fileName);
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

QJsonObject ParserClass::downloadJson(const QString url)
{
    QByteArray result = cc->performing(url.toUtf8());
    QJsonObject object = jsonObjectFromString(result);
    return object;
}

void ParserClass::downloadAndWriteFile(const QString &url, const QString &path, const QString &fileName)
{
    QByteArray result = cc->performing(url.toUtf8());
    writeFile(result, path, fileName);
}

QJsonArray ParserClass::downloadJsonAsArray(const QString &url)
{
    QByteArray result = cc->performing(url.toUtf8());
    QJsonArray arr = jsonArrayFromString(result);
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

void ParserClass::findMatchChars(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult)
{
    regexResult.resize(pattens.size());
    for (int i = 0; i < pattens.size(); i++)
    {
        QRegularExpression re(pattens[i]);
        QRegularExpressionMatchIterator reI = re.globalMatch(data);
        for (int j = 0; reI.hasNext(); j++)
        {
            regexResult[i].resize(regexResult[i].size() + 1);
            QRegularExpressionMatch match = reI.next();
            for (int jj = 0; jj <= match.lastCapturedIndex(); jj++)
                regexResult[i][j].push_back(match.captured(jj));
        }
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

void ParserClass::replace(QByteArray &inp, const QVector<QByteArray> &whatReplace, const QVector<QByteArray> &onWhatReplace)
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
    inp = QByteArray::fromStdString(input);
}

void ParserClass::replaceHtmlEntities(QString &wrongString)
{
    QVector<QString> htmlEntities;
    htmlEntities.push_back("&amp;");
    htmlEntities.push_back("&quot;");
    htmlEntities.push_back("&apos;");
    htmlEntities.push_back("&it;");
    htmlEntities.push_back("&gt;");
    htmlEntities.push_back("&nbsp;");
    QVector<QString> rightSumbols;
    rightSumbols.push_back("&");
    rightSumbols.push_back("\"");
    rightSumbols.push_back("'");
    rightSumbols.push_back("<");
    rightSumbols.push_back(">");
    rightSumbols.push_back(" ");
    replace(wrongString, htmlEntities, rightSumbols);
}

void ParserClass::replaceHtmlEntities(QByteArray &wrongString)
{
    QVector<QByteArray> htmlEntities;
    htmlEntities.push_back("&amp;");
    htmlEntities.push_back("&quot;");
    htmlEntities.push_back("&apos;");
    htmlEntities.push_back("&it;");
    htmlEntities.push_back("&gt;");
    htmlEntities.push_back("&nbsp;");
    QVector<QByteArray> rightSumbols;
    rightSumbols.push_back("&");
    rightSumbols.push_back("\"");
    rightSumbols.push_back("'");
    rightSumbols.push_back("<");
    rightSumbols.push_back(">");
    rightSumbols.push_back(" ");
    for (int i = 0; i < rightSumbols.size(); i++)
        wrongString = wrongString.replace(htmlEntities[i], rightSumbols[i]);
    //replace(wrongString, htmlEntities, rightSumbols);
}

void ParserClass::downloadAndWriteFileWithDefinedExtension(const QString &url, const QString &path, const QString &fileName)
{
    QByteArray fileString = cc->performing(url.toUtf8());
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
    pattern = "({\".+})+"; // =*({(\")(.)+})+
    
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

void ParserClass::percentEncodingToUtf8(QString &data)
{
    QVector<QString> entityes;
    QVector<QString> codes;
    QRegularExpression re("(%([A-F0-9]{2}))");
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    for (int j = 0;i.hasNext(); j++)
    {
        QRegularExpressionMatch match = i.next();
        entityes.push_back(match.captured(1));
        codes.push_back(QByteArray::fromHex(match.captured(2).toUtf8()));
    }
    for (int i = 0; i < codes.size(); i++)
        data.replace(entityes[i], codes[i]);
}

QString ParserClass::convertNationalEncodingToUtf8(const QByteArray &inputEncoding, const QByteArray &data)
{
    QTextCodec *codec = QTextCodec::codecForName(inputEncoding);
    return codec->toUnicode(data);
}

bool ParserClass::FileExist(const QString &path)
{
    QFileInfo checkFile(path);
    if (checkFile.exists() && checkFile.isFile())
        return true;
    else
        return false;
}

bool ParserClass::FolderExist(const QString &path)
{
    QFileInfo checkFile(path);
    if (checkFile.exists() && checkFile.isDir())
        return true;
    else
        return false;
}

QJsonArray ParserClass::jsonArrayFromString(const QString &content)
{
    QJsonArray arr;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
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

void ParserClass::asyncWriteFile(const QByteArray &data, const QString &directory, const QString &fileName)
{
    recursiveMakePath(directory);
    QFile file(directory + '\\' + fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream stream(&file);
        stream.writeRawData(data, data.length());
    }
    file.close();
}

void ParserClass::recursiveMakePath(const QString &path)
{
    QDir dir = QDir(path);
    bool qexi = dir.exists();
    if (!qexi)
        qexi = dir.mkpath("."); // if derictory does not exist make it
}

void ParserClass::replaceHtmlHexCodes(QString &data)
{
    QVector<QVector<QVector<QString>>> regexResult;
    QVector<QString> patterns;
    patterns.push_back("&#(\\d+);");
    findMatchChars(data, patterns, regexResult);
    for (int i = 0; i < regexResult[0].size(); i++)
    {
        regexResult[0][i][1] = intToUtf8(regexResult[0][i][1].toInt());
        data.replace(regexResult[0][i][0], regexResult[0][i][1]);
    }
    replaceHtmlEntities(data);
}
