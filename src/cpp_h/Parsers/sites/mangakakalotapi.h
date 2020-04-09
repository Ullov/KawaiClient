#ifndef MANGAKAKALOTAPI_H
#define MANGAKAKALOTAPI_H

#include "../parserclass.h"

class MangakakalotApi : public ParserClass
{
    Q_OBJECT
public:
    MangakakalotApi();

    QString mangaSystemName;

public slots:
    void download();
};

#endif // MANGAKAKALOTAPI_H
