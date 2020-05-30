#ifndef PARSERS_SITES_MANGADEX_H
#define PARSERS_SITES_MANGADEX_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class MangaDex : public ParserClass
    {
    public:
        MangaDex();

        QString mangaId;
        QString enDownload; // bool
        QString ruDownload; // bool
        QString otherDownload; // bool

        void download();
    };
}

#endif // PARSERS_SITES_MANGADEX_H
