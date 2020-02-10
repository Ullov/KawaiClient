#ifndef KAWAIHTMLPARSER_H
#define KAWAIHTMLPARSER_H

#include <QString>
#include <QRegularExpression>

class KawaiHtmlParser
{
public:
    KawaiHtmlParser();

    void open(const QString &url);

private:
    void findMatchChars(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult);
    QVector<QVector<QString>> extractTags(const QString &data);

    // variables
    QVector<QString> patterns = QVector<QString>();
    QVector<QVector<QVector<QString>>> regexResult = QVector<QVector<QVector<QString>>>();
};

#endif // KAWAIHTMLPARSER_H
