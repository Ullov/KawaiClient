#ifndef HTMLTAG_H
#define HTMLTAG_H

#include <QString>
#include <QMap>

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

#endif // HTMLTAG_H
