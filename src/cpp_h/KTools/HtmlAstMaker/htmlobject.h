#ifndef HTMLOBJECT_H
#define HTMLOBJECT_H

#include <QString>
#include "htmltag.h"
#include "../../logging.h"

class HtmlObject
{
public:
    HtmlObject();

    bool makeAst(const QString &data);
    HtmlTag *rootTag;

private:

    bool escapedChar = false;
    const QString *htmlText;
    qint32 tagStartPos;

    HtmlTag& readTag(qint32 &pos, const qint32 &endPos);
    bool readTagName(qint32 &pos, HtmlTag &tagClass);
    bool readTagAttributes(qint32 &pos, HtmlTag &tagClass);
    bool setRootTag(HtmlTag &tag);
    qint32 findTagEndingPart(const qint32 &pos, const qint32 &endPos, HtmlTag &tagClass, qint32 differenceEdAndOp = 0);
    //qint32 findTagEndingPartSecondPass(qint32 pos, qint32 endPos, HtmlTag &tagClass, qint32 differenceEdAndOp);
};

#endif // HTMLOBJECT_H
