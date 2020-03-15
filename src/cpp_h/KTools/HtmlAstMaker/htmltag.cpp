#include "htmltag.h"

HtmlTag::HtmlTag()
{
    name = new QString();
    attributes = new QMap<QString, QString>();
    innerContent = new QString();
    childTags = new QVector<HtmlTag*>();
}

HtmlTag::~HtmlTag()
{
    delete name;
    delete attributes;
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

const QString& HtmlTag::getName()
{
    return *name;
}

void HtmlTag::addAttribute(const QString &key, const QString &value)
{
    attributes->insert(key, value);
}

QString HtmlTag::getAttributeValue(const QString &key)
{
    return attributes->value(key);
}

const QMap<QString, QString>& HtmlTag::getAttributes()
{
    return *attributes;
}

void HtmlTag::clearAttributes()
{
    attributes->clear();
}

void HtmlTag::setInnerContent(const QString &content)
{
    delete innerContent;
    innerContent = new QString(content);
}

const QString& HtmlTag::getInnerContent()
{
    return *innerContent;
}

void HtmlTag::addChildTag(HtmlTag &localTag)
{
    childTags->append(&localTag);
    localTag.setParentTag(*this);
}

const QVector<HtmlTag*>& HtmlTag::getChildTags()
{
    return *childTags;
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

HtmlTag& HtmlTag::operator[](const qint32 numb)
{
    return *childTags->at(numb);
}

QPair<QString, QString> HtmlTag::operator[](const QString &localAttributeName)
{
    return QPair<QString, QString>(localAttributeName,  attributes->find(localAttributeName).value());
}
