#include "htmlastmaker.h"

HtmlAstMaker::HtmlAstMaker() {}

void HtmlAstMaker::makeAst(const QString &data)
{
    htmlText = data;
    QVector<Tag> tags;
    for (int i = 0; i < htmlText.size(); i++)
    {
        if (htmlText[i] == "<")
        {
            if (!escapedChar)
            {
                Tag currentTag;
                readTag(i, currentTag);
            }
        }
    }
}

void HtmlAstMaker::readTag(const qint64 startPos, Tag &tagStructure)
{
    bool tagOpened = false;
    bool comment = false;
    for (int i = startPos; i < htmlText.size();)
    {
        if (htmlText[i] == "<" && !comment)
        {
            tagStructure.openingPart.append(htmlText[i]);
            tagOpened = true;
            i++;
        }
        else if (htmlText[i] == "!" && htmlText[i + 1] == "-" && htmlText[i + 2] == "-" && tagOpened)
        {
            comment = true;

        }
    }
}
