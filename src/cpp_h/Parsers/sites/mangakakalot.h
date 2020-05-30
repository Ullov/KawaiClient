#ifndef PARSERS_SITES_MANGAKAKALOT_H
#define PARSERS_SITES_MANGAKAKALOT_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class MangaKakalot : public ParserClass
    {
    public:
        MangaKakalot();

        QString mangaSystemName;

        void download();
    };
}

#endif // PARSERS_SITES_MANGAKAKALOT_H
