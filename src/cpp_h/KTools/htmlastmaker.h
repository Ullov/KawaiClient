#ifndef HTMLASTMAKER_H
#define HTMLASTMAKER_H

#include <QString>
#include <QVector>

class HtmlAstMaker
{
public:
    HtmlAstMaker();

    void makeAst(const QString &data);

private:
    struct TagAttribute {
        QString name;
        QString value;
    };
    struct Tag {
        QString name;
        QVector<TagAttribute> attributes;
        bool selfclosing;
        QString innerText;
        QString openingPart;
        QString closingPart;
    };

    bool escapedChar = false;
    QString htmlText;

    void readTag(const qint64 startPos, Tag &tagStructure);
};

#endif // HTMLASTMAKER_H
