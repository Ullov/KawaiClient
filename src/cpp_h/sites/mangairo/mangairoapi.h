#ifndef MANGAIROAPI_H
#define MANGAIROAPI_H

#include "cpp_h/parserclass.h"

class MangairoApi : public ParserClass
{
    Q_OBJECT
public:
    MangairoApi();

    std::string mangaId;

public slots:
    void download();
};

#endif // MANGAIROAPI_H
