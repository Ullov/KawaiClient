#ifndef KAWAICONVERTER_H
#define KAWAICONVERTER_H

#include "stringoperations.h"
#include "logging.h"
#include <QByteArray>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QVector>
#include <QRegularExpression>
#include <QTextCodec>
#include <QDataStream>

class KawaiConverter
{
public:
    KawaiConverter();

    template<typename T, typename E>
    static E convert(const T &data);

    template<typename T>
    static T byteArrayToT(const QByteArray &bArr);
    template<typename T>
    static QByteArray toByteArray(const T &data);

    static QString numberToUtf8(const quint16 &code);
    static void percentEncodingToString(QString &encodedString);
    static void percentEncodingToString(QByteArray &encodedString);
    static void toNtfsCompatibleString(QString &data);
    static void convertHtmlEntities(QString &inp);
    static void convertHtmlEntities(QByteArray &inp);
    static void convertHtmlHexCodes(QString &data);
    static QString nationalEncodingToUtf8(const QByteArray &inputEncoding, const QByteArray &data);
};

#endif // KAWAICONVERTER_H
