#ifndef MANGAKAKALOTAPI_H
#define MANGAKAKALOTAPI_H

#include "../parserclass.h"
#include "../../KTools/HtmlAstMaker/htmlobject.h"

class MangakakalotApi : public ParserClass
{
public:
    MangakakalotApi();

    QString mangaSystemName;

//public slots:
    void download();
};

#endif // MANGAKAKALOTAPI_H
