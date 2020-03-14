#include "htmlobject.h"

HtmlObject::HtmlObject()
{

}

bool HtmlObject::makeAst(const QString &data)
{
    htmlText = &data;
    qint32 pos = 0;
    return setRootTag(*readTag(pos, htmlText->size()));
}

HtmlTag* HtmlObject::readTag(qint32 &pos, const qint32 &endPos)
{
    HtmlTag *tagClass = new HtmlTag();
    while (pos < endPos)
    {
        if (htmlText->mid(pos, 2) == "<!")
        {
            ++pos;
            while (htmlText->at(pos) != "<")
                ++pos;
            //tagClass->status = HtmlTag::StatusEnum::TagInvalid;
            //return tagClass;
        }
        else if (htmlText->at(pos) == "<")
        {
            bool tagNameReaded = false;
            bool tagClosed = false;
            ++pos; // skip < char
            if (htmlText->at(pos) == "/")
            {
                tagClass->status = HtmlTag::StatusEnum::TagClosingDetected;
                return tagClass;
            }
            while (pos < endPos)
            {
                if (!tagClosed)
                {
                    if (htmlText->at(pos) == ">")
                    {
                        tagClosed = true; // tag end detected
                        ++pos;
                    }
                    else if (htmlText->mid(pos, 2) == "/>")
                    {
                        tagClosed = true; // tag end detected
                        pos += 2;
                    }
                    else if (htmlText->at(pos).isSpace() || htmlText->at(pos) == "\n" || htmlText->at(pos) == "\r")
                    {
                        ++pos; // skip space char after < char
                    }
                    else if ((htmlText->at(pos).isLetter() || htmlText->at(pos) == "-") && !tagNameReaded)
                    {
                        readTagName(pos, *tagClass);
                        tagNameReaded = true;
                    }
                    else if ((htmlText->at(pos).isLetter() || htmlText->at(pos) == "-") && tagNameReaded)
                    {
                        readTagAttributes(pos, *tagClass);
                        tagClosed = true;
                    }
                }
                else
                {
                    qint32 tmpPos = pos; // this also ABSOLUTE end position
                    qint32 nameSize = tagClass->getName()->size();
                    QString tmpTagName = "</" + *tagClass->getName() + ">"; // thank to this variable ast maker now works in 6 times faster
                    while (tmpPos < endPos + 1)
                    {
                        if (htmlText->mid(tmpPos, 3 + nameSize) == tmpTagName)
                        {
                            tagClass->setInnerContent(htmlText->mid(pos, tmpPos - pos));
                            tagClass->setSelfclosingness(true);
                            break;
                        }
                        else
                        {
                            ++tmpPos;
                        }
                    }
                    if (tagClass->isSelfclosing())
                    {
                        while (pos < tmpPos)
                        {
                            HtmlTag *newTag = readTag(pos, tmpPos);
                            if (newTag->status == HtmlTag::StatusEnum::TagValid)
                            {
                                tagClass->addChildTag(*newTag);
                            }
                            else if (newTag->status == HtmlTag::StatusEnum::TagInvalid)
                            {
                                delete newTag;
                            }
                            else if(newTag->status == HtmlTag::StatusEnum::TagClosingDetected)
                            {
                                ++pos;
                            }
                        }
                        tagClass->status = HtmlTag::StatusEnum::TagValid;
                        return tagClass;
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
            tagClass->status = HtmlTag::StatusEnum::TagInvalid; // error handling
            pos++;
            return tagClass;
        }
    }
    tagClass->status = HtmlTag::StatusEnum::TagValid;
    return tagClass;
}

bool HtmlObject::readTagName(qint32 &pos, HtmlTag &tagClass)
{
    qint32 start = pos;
    while (htmlText->at(pos).isLetter() || htmlText->at(pos) == "-" || htmlText->at(pos).isDigit())
    {
        ++pos;
    }
    tagClass.setName(htmlText->mid(start, pos - start));
    return true;
}

bool HtmlObject::readTagAttributes(qint32 &pos, HtmlTag &tagClass)
{
    while (htmlText->at(pos) != ">" || htmlText->mid(pos, 2) == "/>") // while tag not closed
    {
        qint32 startKey = pos;
        while ((htmlText->at(pos).isLetter() || htmlText->at(pos) == "-" || htmlText->at(pos) == ":") && htmlText->at(pos) != "=")
        {
            ++pos;
        }
        qint32 lenKey = pos - startKey; // key lenght
        QChar quiote = htmlText->at(pos + 1);
        if (htmlText->at(pos) == "=" && (quiote == "\"" || quiote == "'"))
        {
            pos += 2;
            qint32 startValue = pos;
            while (htmlText->at(pos) != quiote)
            {
                ++pos;
            }
            tagClass.addAttribute(htmlText->mid(startKey, lenKey), htmlText->mid(startValue, pos - startValue));
        }
        else
        {
            return false; // here should be error handling
        }
        ++pos; // skip " char
        while (htmlText->at(pos) == " ") // skip spaces between attributes
            ++pos;
    }
    ++pos;
    return true;
}

bool HtmlObject::setRootTag(HtmlTag &tag)
{
    if (tag.status == HtmlTag::StatusEnum::TagValid)
    {
        rootTag = &tag;
        return true;
    }
    else
        return false;
}
