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
    QString& getName();
    QString getAttributeValue(const QString &key);
    QMap<QString, QString>& getAttributes();
    QString& getInnerContent();
    QVector<HtmlTag*>& getChildTags();
    HtmlTag& getParentTag();
    qint32 getChildTagCounter();

    void clearAttributes();
    HtmlTag& find(const qint32 numb); // returns child tag ny number

    enum class StatusEnum
    {
        TagClosingDetected,
        TagInvalid,
        TagValid
    };
    StatusEnum status;

private:
    bool selfclosing = false;
    QString name;
    QMap<QString, QString> attributes;
    QString innerContent;
    QVector<HtmlTag*> childTags;
    HtmlTag *parentTag;
    bool parentTagSetted = false;
    qint32 childTagCounter = 0;
};

#endif // HTMLTAG_H
