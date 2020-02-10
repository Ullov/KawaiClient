#include "kawaihtmlparser.h"

KawaiHtmlParser::KawaiHtmlParser() {}

void KawaiHtmlParser::open(const QString &data)
{
    //patterns.append("<(?:(?P<tagName>[^ ]+)(?: ?([a-zA-Z-]+)=\"([^\"]+)\" ?)?)>([\\S\\s]*)<\\/(?P=tagName)>");
    //findMatchChars(data, patterns, regexResult);
    //QString nope = regexResult[0][0][4];
    //findMatchChars(nope, patterns, regexResult);
    //nope = "";

    QVector<QVector<QString>> tags = extractTags(data);
    QString nope;
// <(?:(?P<tagName>[^ ]+)(?: ?([a-zA-Z-]+)="([^"]+)" ?)?)>([\S\s]*)<\/(?P=tagName)>
}

void KawaiHtmlParser::findMatchChars(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult)
{
    regexResult.clear();
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

QVector<QVector<QString>> KawaiHtmlParser::extractTags(const QString &data)
{
    QVector<QString> localPatterns;
    QVector<QVector<QString>> result;
    localPatterns.append("<(?:(?P<tagName>[^ ]+)(?: ?([a-zA-Z-]+)=\"([^\"]+)\" ?)?)>([\\S\\s]*)<\\/(?P=tagName)>");
    QVector<QVector<QVector<QString>>> localRegexResult;
    findMatchChars(data, localPatterns, localRegexResult);
    for (int i = 0; i < localRegexResult[0].size(); i++)
    {
        if (localRegexResult[0][i][1] != "")
        {
            result.append(localRegexResult[0][i]);
            result.append(extractTags(localRegexResult[0][i][4]));
        }
    }
    return result;
}
