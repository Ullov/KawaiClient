#ifndef PARSERS_SITES_MANGAIRO_H
#define PARSERS_SITES_MANGAIRO_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class MangaIro : public Parsers::ParserClass
    {
    public:
        MangaIro();

        QString mangaId;

        void download();
    };
}

#endif // PARSERS_SITES_MANGAIRO_H
