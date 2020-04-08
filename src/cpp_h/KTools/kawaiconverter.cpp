#include "kawaiconverter.h"

KawaiConverter::KawaiConverter() {}

template<typename T>
T KawaiConverter::byteArrayToT(const QByteArray &bArr)
{
    if (typeid(T) == typeid(qint32))        // int[32]
        return bArr.toInt();
    else if (typeid(T) == typeid(quint32))  // uint[32]
        return bArr.toUInt();

    else if (typeid(T) == typeid(qint64))   // int[64]
        return bArr.toLong();
    else if (typeid(T) == typeid(quint64))  // uint[64]
        return bArr.toULong();

    else if (typeid(T) == typeid(qint16))   // int[16]
        return bArr.toShort();
    else if (typeid(T) == typeid(quint16))  // uint[16]
        return bArr.toUShort();

    return T();
}
template<>
const char* KawaiConverter::byteArrayToT<const char*>(const QByteArray &bArr)
{
    return bArr.data();
}
template<>
QString KawaiConverter::byteArrayToT<QString>(const QByteArray &bArr)
{
    return bArr;
}
template<>
QByteArray KawaiConverter::byteArrayToT<QByteArray>(const QByteArray &bArr)
{
    return bArr;
}



template<typename QByteArray, typename E>
E KawaiConverter::convert(const QByteArray &data)
{
    return byteArrayToT<E>(data);
}
template<>
QJsonObject KawaiConverter::convert<QString, QJsonObject>(const QString &data)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
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
template<>
QJsonArray KawaiConverter::convert<QString, QJsonArray>(const QString &data)
{
    QJsonArray arr;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());
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
template<>
QByteArray KawaiConverter::convert<qint8, QByteArray>(const qint8 &data)
{
    return toByteArray<qint8>(data);
}
template<>
QByteArray KawaiConverter::convert<quint8, QByteArray>(const quint8 &data)
{
    return toByteArray<quint8>(data);
}
template<>
QByteArray KawaiConverter::convert<qint16, QByteArray>(const qint16 &data)
{
    return toByteArray<qint16>(data);
}
template<>
QByteArray KawaiConverter::convert<quint16, QByteArray>(const quint16 &data)
{
    return toByteArray<quint16>(data);
}
template<>
QByteArray KawaiConverter::convert<qint32, QByteArray>(const qint32 &data)
{
    return toByteArray<qint32>(data);
}
template<>
QByteArray KawaiConverter::convert<quint32, QByteArray>(const quint32 &data)
{
    return toByteArray<quint32>(data);
}
template<>
QByteArray KawaiConverter::convert<qint64, QByteArray>(const qint64 &data)
{
    return toByteArray<qint64>(data);
}
template<>
QByteArray KawaiConverter::convert<quint64, QByteArray>(const quint64 &data)
{
    return toByteArray<quint64>(data);
}
template<>
QByteArray KawaiConverter::convert<float, QByteArray>(const float &data)
{
    return toByteArray<float>(data);
}
template<>
QByteArray KawaiConverter::convert<double, QByteArray>(const double &data)
{
    return toByteArray<double>(data);
}
template<>
unsigned char KawaiConverter::convert<char, unsigned char>(const char &data)
{
    return static_cast<unsigned char>(data);
}
template<>
QByteArray KawaiConverter::convert<QString, QByteArray>(const QString &data)
{
    return data.toUtf8();
}
template<>
unsigned char KawaiConverter::convert<QString, unsigned char>(const QString &data)
{
    const char *tmp = convert<QString, QByteArray>(data).constData();
    return convert<char, unsigned char>(*tmp);
}
template<>
QString KawaiConverter::convert<QJsonObject, QString>(const QJsonObject &data)
{
    QJsonDocument jDoc(data);
    return jDoc.toJson();
}
template<>
QByteArray KawaiConverter::convert<QJsonObject, QByteArray>(const QJsonObject &data)
{
    return convert<QJsonObject, QString>(data).toUtf8();
}



template<typename T>
QByteArray KawaiConverter::toByteArray(const T &data)
{
    QByteArray byteArr;
    QDataStream byteStream(byteArr);
    byteStream << data;
    return byteArr;
}

QString KawaiConverter::numberToUtf8(const quint16 &code)
{
    QString resultChar = QString::fromUtf16(&code);
    resultChar.resize(1);
    return resultChar;
}

void KawaiConverter::percentEncodingToString(QString &encodedString)
{
    QVector<QString> entityes;
    QVector<QString> codes;
    QRegularExpression re("(%([A-F0-9]{2}))");
    QRegularExpressionMatchIterator i = re.globalMatch(encodedString);
    for (int j = 0;i.hasNext(); j++)
    {
        QRegularExpressionMatch match = i.next();
        entityes.push_back(match.captured(1));
        codes.push_back(QByteArray::fromHex(match.captured(2).toUtf8()));
    }
    for (int i = 0; i < codes.size(); i++)
        encodedString.replace(entityes[i], codes[i]);
}

void KawaiConverter::toNtfsCompatibleString(QString &data)
{
    QVector<QString> wrongChars = {"\"", "|", "/", ":", "*", "?", ">", "<"};
    QVector<QString> voids;
    for (int i = 0; i < wrongChars.size(); i++)
        voids.push_back("");
    StringOperations::deleteChars(data, wrongChars);
}

void KawaiConverter::convertHtmlEntities(QString &inp)
{
    QVector<QString> htmlEntities = {"&amp;", "&quot;", "&apos;", "&it;", "&gt;", "&nbsp;"};
    QVector<QString> rightSumbols = {"&", "\"", "'", "<", ">", " "};
    StringOperations::replace(inp, htmlEntities, rightSumbols);
}

void KawaiConverter::convertHtmlEntities(QByteArray &inp)
{
    QVector<QByteArray> htmlEntities = {"&amp;", "&quot;", "&apos;", "&it;", "&gt;", "&nbsp;"};
    QVector<QByteArray> rightSumbols = {"&", "\"", "'", "<", ">", " "};
    StringOperations::replace(inp, htmlEntities, rightSumbols);
}

void KawaiConverter::convertHtmlHexCodes(QString &data)
{
    QVector<QVector<QVector<QString>>> regexResult;
    QVector<QString> patterns;
    patterns.push_back("&#(\\d+);");
    StringOperations::executeRegex(data, patterns, regexResult);
    for (int i = 0; i < regexResult[0].size(); i++)
    {
        regexResult[0][i][1] = numberToUtf8(regexResult[0][i][1].toUShort());
        data.replace(regexResult[0][i][0], regexResult[0][i][1]);
    }
    convertHtmlEntities(data);
}

QString KawaiConverter::nationalEncodingToUtf8(const QByteArray &inputEncoding, const QByteArray &data)
{
    QTextCodec *codec = QTextCodec::codecForName(inputEncoding);
    return codec->toUnicode(data);
}

template qint8 KawaiConverter::byteArrayToT<qint8>(const QByteArray&);
template quint8 KawaiConverter::byteArrayToT<quint8>(const QByteArray&);
template qint16 KawaiConverter::byteArrayToT<qint16>(const QByteArray&);
template quint16 KawaiConverter::byteArrayToT<quint16>(const QByteArray&);
template qint32 KawaiConverter::byteArrayToT<qint32>(const QByteArray&);
template quint32 KawaiConverter::byteArrayToT<quint32>(const QByteArray&);
template qint64 KawaiConverter::byteArrayToT<qint64>(const QByteArray&);
template quint64 KawaiConverter::byteArrayToT<quint64>(const QByteArray&);
