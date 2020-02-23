#include "stringoperations.h"

StringOperations::StringOperations() {}

void StringOperations::replace(QString &inp, const QVector<QString> &whatReplace, const QVector<QString> &onWhatReplace)
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

void StringOperations::replace(QByteArray &inp, const QVector<QByteArray> &whatReplace, const QVector<QByteArray> &onWhatReplace)
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

void StringOperations::deleteChars(QString &inp, const QVector<QString> &whatDelete)
{
    QVector<QString> voids;
    for (int i = 0; i < whatDelete.size(); i++)
        voids.push_back("");
    replace(inp, whatDelete, voids);
}

void StringOperations::executeRegex(const QString &data, const QVector<QString> &pattens, QVector<QVector<QVector<QString>>> &regexResult)
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

void StringOperations::executeRegex(const QString &data, const QString &pattern, QVector<QString> &result)
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
