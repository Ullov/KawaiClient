#include "htmlastmaker.h"

HtmlAstMaker::HtmlAstMaker() {}

void HtmlAstMaker::makeAst(const QString &data)
{
    /*htmlText = data;
    rootTag = new HtmlTag();
    for (int i = 0; i < htmlText.size(); i++)
    {
        HtmlTag *newTag = new HtmlTag();
        qint32 newPos = skipToCharSequence(htmlText, "<", i);
        if (newPos > 0)
        {
            if (htmlText[newPos - 1] != "\\" && htmlText.mid(newPos, 4) != "<!--")
            {
                readTag(newPos, *newTag);
            }
        }
    }*/
    htmlText = data;
    //QByteArray tmp = QByteArray(htmlText);
    NativeFs::writeFile(htmlText.toUtf8(), "E:\\Win7アプリ\\downloads", "astTestHtml.txt");
    NativeFs::writeFile("", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt");
    qint32 pos = 0;
    rootTag = readTag(pos, htmlText.size());
}

HtmlTag* HtmlAstMaker::readTag(qint32 &pos, const qint32 &endPos)
{
    HtmlTag *tagClass = new HtmlTag();
    while (pos < endPos)
    {
        //debugMethod(pos, *tagClass, 34);
        if (htmlText[pos] == "<")
        {
            bool tagNameReaded = false;
            bool tagClosed = false;
            pos++; // skip < char
            //NativeFs::writeFile( htmlText.mid(pos, 20).toUtf8() + "\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
            if (htmlText[pos] == "/")
            {
                tagClass->status = HtmlTag::StatusEnum::TagClosingDetected;
                return tagClass;
            }
            while (pos < endPos)
            {
                //debugMethod(pos, *tagClass, 47);
                if (!tagClosed)
                {
                    if (htmlText[pos] == ">")
                    {
                        tagClosed = true; // tag end detected
                        pos++;
                        NativeFs::writeFile("1\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                    }
                    else if (htmlText.mid(pos, pos + 1) == "/>")
                    {
                        tagClosed = true; // tag end detected
                        pos += 2;
                        NativeFs::writeFile("2\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                    }
                    else if (/*htmlText[pos] == " " || */htmlText[pos].isSpace() || htmlText[pos] == "\n" || htmlText[pos] == "\r")
                    {
                        pos++; // skip space char after < char
                        NativeFs::writeFile("3\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                    }
                    else if ((htmlText[pos].isLetter() || htmlText[pos] == "-") && !tagNameReaded)
                    {
                        readTagName(pos, *tagClass);
                        tagNameReaded = true;
                        NativeFs::writeFile("4\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                    }
                    else if ((htmlText[pos].isLetter() || htmlText[pos] == "-") && tagNameReaded)
                    {
                        readTagAttributes(pos, *tagClass);
                        tagClosed = true;
                        //QMap<QString, QString> attr = *tagClass->getAttributes();
                        NativeFs::writeFile("5\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                    }
                }
                else
                {
                    qint32 tmpPos = pos; // this also ABSOLUTE end position
                    while (tmpPos < endPos)
                    {
                        //debugMethod(tmpPos, *tagClass, 75);

                        qint32 nameSize = tagClass->getName()->size();
                        if (htmlText.mid(tmpPos, 3 + nameSize) == "</" + *tagClass->getName() + ">")
                        {
                            qint32 innerContentLen = tmpPos - pos; // and this RELATIVE end position i.e. HtmlTag::innerContent::size
                            tagClass->setInnerContent(htmlText.mid(pos, innerContentLen));
                            NativeFs::writeFile(tagClass->getInnerContent()->toUtf8() + "\n" + htmlText.mid(tmpPos, 3 + nameSize).toUtf8() + " " + QByteArray::number(tmpPos) + "\n\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            tagClass->setSelfclosingness(true);
                            break;
                        }
                        else
                        {
                            tmpPos++;
                        }
                    }
                    if (tagClass->isSelfclosing())
                    {
                        while (pos < tmpPos)
                        {
                            //debugMethod(pos, *tagClass, 91);
                            HtmlTag *newTag = readTag(pos, tmpPos);
                            if (newTag->status == HtmlTag::StatusEnum::TagValid)
                            {
                                tagClass->addChildTag(*newTag);
                                NativeFs::writeFile("Tag valid\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            }
                            else if (newTag->status == HtmlTag::StatusEnum::TagInvalid)
                            {
                                delete newTag;
                                //pos++;
                                NativeFs::writeFile("Tag invalid " + htmlText.mid(pos, 20).toUtf8() + "\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            }
                            else if(newTag->status == HtmlTag::StatusEnum::TagClosingDetected)
                            {
                                pos++;
                                NativeFs::writeFile("Tag closing\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            }
                            else if (newTag->status == HtmlTag::StatusEnum::NotSetted)
                            {
                                NativeFs::writeFile("Tag status not setted\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            }
                            else if (newTag->status == HtmlTag::StatusEnum::SelfclosingTag)
                            {
                                tagClass->addChildTag(*newTag);
                                NativeFs::writeFile("Tag selfclosing\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
                            }
                        }
                        tagClass->status = HtmlTag::StatusEnum::TagValid;
                        return tagClass;
                        //pos++;
                    }
                    else
                    {
                        tagClass->status = HtmlTag::StatusEnum::TagValid;
                        return tagClass;
                    }
                }
            }
        }
        else
        {
            QString invalidChar = htmlText.mid(pos, 10);
            tagClass->status = HtmlTag::StatusEnum::TagInvalid; // error handling
            pos++;
            return tagClass;
        }
    }
    tagClass->status = HtmlTag::StatusEnum::TagValid;
    return tagClass;
}

qint32 HtmlAstMaker::skipToCharSequence(const QString &data, const QString &sequence, const qint32 startPos)
{
    if ((data.size() - startPos) < 0)
        return -1;
    if ((data.size() - startPos) < sequence.size())
        return -1;
    for (int i = startPos + sequence.size(); i < data.size(); i++)
    {
        if (data.mid(i, sequence.size()) == sequence)
            return i;
    }
    return -1;
}

bool HtmlAstMaker::readTagName(qint32 &pos, HtmlTag &tagClass)
{
    QString name = "";
    while (htmlText[pos].isLetter() || htmlText[pos] == "-")
    {
        name += htmlText[pos];
        pos++;
    }
    tagClass.setName(name);
    //pos++;
    return true;
}

bool HtmlAstMaker::readTagAttributes(qint32 &pos, HtmlTag &tagClass)
{
    while (htmlText[pos] != ">" || htmlText.mid(pos, 2) == "/>") // while tag not closed
    {
        QString attributeKey = "";
        QString attributeValue = "";
        while ((htmlText[pos].isLetter() || htmlText[pos] == "-") && htmlText[pos] != "=")
        {
            attributeKey += htmlText[pos];
            pos++;
        }
        //pos++; // skip " char
        QChar quiote = htmlText[pos + 1];
        if (htmlText[pos] == "=" && (quiote == "\"" || quiote == "'"))
        {
            pos += 2;
            while (htmlText[pos] != quiote)
            {
                attributeValue += htmlText[pos];
                pos++;
            }
        }
        else
        {
            return false; // here should be error handling
        }
        tagClass.addAttribute(attributeKey, attributeValue);
        pos++; // skip " char
        while (htmlText[pos] == " ") // skip spaces between attributes
            pos++;
    }
    pos++;
    return true;
}

void HtmlAstMaker::debugMethod(const qint32 pos, HtmlTag &tagClass, const qint32 stringNumber)
{
    qint32 prePosChars = 10;
    qint32 afterPosChars = 20;
    QByteArray prePos = htmlText.mid(pos - prePosChars, prePosChars).toUtf8().replace("\r\n", "NL").replace("\n", "").replace("\r", "");
    QByteArray afterPos = htmlText.mid(pos, afterPosChars).toUtf8().replace("\r\n", "NL").replace("\n", "").replace("\r", "");
    NativeFs::writeFile(QByteArray::number(pos) + " " + prePos + " " + afterPos + " " + tagClass.getName()->toUtf8() + " " + QByteArray::number(stringNumber) + "\n", "E:\\Win7アプリ\\downloads", "astMakerDebugData.txt", QIODevice::Append);
}


HtmlTag::HtmlTag()
{
    name = new QString();
    tags = new QMap<QString, QString>();
    innerContent = new QString();
    childTags = new QVector<HtmlTag*>();
    //parentTag = new HtmlTag();
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
