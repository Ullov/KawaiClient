#include "htmltag.h"

HtmlTag::HtmlTag()
{
    name = new QString();
    tags = new QMap<QString, QString>();
    innerContent = new QString();
    childTags = new QVector<HtmlTag*>();
}

HtmlTag::~HtmlTag()
{
    delete name;
    delete tags;
    delete innerContent;
    if (parentTagSetted)
        delete parentTag;
    for (qint32 i = 0; i < childTags->size(); i++)
        delete childTags->at(i);
    delete childTags;
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
    delete name;
    name = new QString(newName);
}

const QString* HtmlTag::getName()
{
    return name;
}

void HtmlTag::addAttribute(const QString &key, const QString &value)
{
    tags->insert(key, value);
}

QString HtmlTag::getAttributeValue(const QString &key)
{
    return tags->value(key);
}

const QMap<QString, QString>* HtmlTag::getAttributes()
{
    return tags;
}

void HtmlTag::clearTags()
{
    tags->clear();
}

void HtmlTag::setInnerContent(const QString &content)
{
    delete innerContent;
    innerContent = new QString(content);
}

const QString* HtmlTag::getInnerContent()
{
    return innerContent;
}

void HtmlTag::addChildTag(HtmlTag &localTag)
{
    childTags->append(&localTag);
    localTag.setParentTag(*this);
}

const QVector<HtmlTag*>* HtmlTag::getChildTags()
{
    return childTags;
}

void HtmlTag::setParentTag(HtmlTag &localTag)
{
    parentTag = &localTag;
    parentTagSetted = true;
}

HtmlTag* HtmlTag::getParentTag()
{
    return parentTag;
}
