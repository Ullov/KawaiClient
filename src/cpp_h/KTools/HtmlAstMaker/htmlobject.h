#ifndef HTMLOBJECT_H
#define HTMLOBJECT_H

#include <QString>
#include "htmltag.h"

class HtmlObject
{
public:
    HtmlObject();

    bool makeAst(const QString &data);

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

#endif // HTMLOBJECT_H
