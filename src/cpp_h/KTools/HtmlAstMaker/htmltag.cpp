#include "htmltag.h"

HtmlTag::HtmlTag()
{
    childTags = QVector<HtmlTag*>();
}

HtmlTag::~HtmlTag()
{
    if (parentTagSetted)
        delete parentTag;
    for (qint32 i = 0; i < childTags.size(); i++)
        delete childTags.at(i);
}

bool HtmlTag::isSelfclosing()
{
    return selfclosing;
}

void HtmlTag::setSelfclosingness(bool sc)
{
    selfclosing = sc;
}

void HtmlTag::setName(const QString &newName)
{
    name = newName;
}

QString& HtmlTag::getName()
{
    return name;
}

void HtmlTag::addAttribute(const QString &key, const QString &value)
{
    attributes.insert(key, value);
}

QString HtmlTag::getAttributeValue(const QString &key)
{
    return attributes.value(key);
}

QMap<QString, QString>& HtmlTag::getAttributes()
{
    return attributes;
}

void HtmlTag::clearAttributes()
{
    attributes.clear();
}

void HtmlTag::setInnerContent(const QString &content)
{
    innerContent = content;
}

QString& HtmlTag::getInnerContent()
{
    return innerContent;
}

void HtmlTag::addChildTag(HtmlTag &localTag)
{
    childTags.append(&localTag);
    localTag.setParentTag(*this);
    ++childTagCounter;
}

QVector<HtmlTag*>& HtmlTag::getChildTags()
{
    return childTags;
}

void HtmlTag::setParentTag(HtmlTag &localTag)
{
    parentTag = &localTag;
    parentTagSetted = true;
}

HtmlTag& HtmlTag::getParentTag()
{
    return *parentTag;
}

HtmlTag& HtmlTag::find(const qint32 numb)
{
    return *childTags[numb];
}

qint32 HtmlTag::getChildTagCounter()
{
    return childTagCounter;
}

bool HtmlTag::isExist(qint32 childTagIndex)
{
    if (childTagIndex < childTags.size())
        return true;
    else
        return false;
}
