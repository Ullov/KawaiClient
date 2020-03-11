#ifndef HTMLASTMAKER_H
#define HTMLASTMAKER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QVectorIterator>
#include "nativefs.h"


class HtmlTag
{
public:
    HtmlTag();
    ~HtmlTag();
    void setSelfclosingness(const bool sc);
    void setName(const QString &newName);
    void addAttribute(const QString &key, const QString &value);
    void setInnerContent(const QString &content);
    void addChildTag(HtmlTag &localTag);
    void setParentTag(HtmlTag &localTag);

    bool isSelfclosing();
    const QString* getName();
    QString getAttributeValue(const QString &key);
    const QMap<QString, QString>* getAttributes();
    const QString* getInnerContent();
    const QVector<HtmlTag*>* getChildTags();
    HtmlTag* getParentTag();

    void clearTags();

    enum class StatusEnum
    {
        TagClosingDetected,
        TagInvalid,
        TagValid,
        NotSetted,
        SelfclosingTag
    };
    StatusEnum status = StatusEnum::NotSetted;

private:
    bool selfclosing = false;
    QString *name;
    QMap<QString, QString> *tags;
    QString *innerContent;
    QVector<HtmlTag*> *childTags;
    HtmlTag *parentTag;
    bool parentTagSetted = false;
};

class HtmlAstMaker
{
public:
    HtmlAstMaker();

    void makeAst(const QString &data);

private:
    HtmlTag *rootTag;

    bool escapedChar = false;
    QString htmlText;
    qint32 tagStartPos;

    HtmlTag* readTag(qint32 &pos, const qint32 &endPos);
    qint32 skipToCharSequence(const QString &data, const QString &sequence, const qint32 startPos);
    bool readTagName(qint32 &pos, HtmlTag &tagClass);
    bool readTagAttributes(qint32 &pos, HtmlTag &tagClass);
    void debugMethod(const qint32 pos, HtmlTag &tagClass, const qint32 stringNumber);
};

#endif // HTMLASTMAKER_H
