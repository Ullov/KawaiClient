#ifndef PARSERS_SITES_MANGAIRO_H
#define PARSERS_SITES_MANGAIRO_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class MangaIro : public ParserClass
    {
    public:
        MangaIro();

        QString mangaId;

        void download();
    };
}

#endif // PARSERS_SITES_MANGAIRO_H
