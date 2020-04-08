#ifndef HTMLASTMAKER_H
#define HTMLASTMAKER_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QTime>
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
        TagValid
    };
    StatusEnum status;

private:
    bool selfclosing = false;
    QString *name;
    QMap<QString, QString> *tags;
    QString *innerContent;
    QVector<HtmlTag*> *childTags;
    HtmlTag *parentTag;
    bool parentTagSetted = false;
};

class HtmlObject
{
public:
    HtmlObject();

    void makeAst(const QString &data);

private:
    HtmlTag *rootTag;

    bool escapedChar = false;
    const QString *htmlText;
    qint32 tagStartPos;

    HtmlTag* readTag(qint32 &pos, const qint32 &endPos);
    bool readTagName(qint32 &pos, HtmlTag &tagClass);
    bool readTagAttributes(qint32 &pos, HtmlTag &tagClass);
    bool setRootTag(HtmlTag &tag);

};

#endif // HTMLASTMAKER_H
