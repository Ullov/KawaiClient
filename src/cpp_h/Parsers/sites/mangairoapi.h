#ifndef MANGAIROAPI_H
#define MANGAIROAPI_H

#include "../parserclass.h"

class MangairoApi : public ParserClass
{
    Q_OBJECT
public:
    MangairoApi();

    QString mangaId;

public slots:
    void download();
};

#endif // MANGAIROAPI_H
