#ifndef PARSERS_SITES_NINEHENTAI_H
#define PARSERS_SITES_NINEHENTAI_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class NineHentai : public Parsers::ParserClass
    {
    public:
        NineHentai();

        QString galleryId;

        void download();

    private:
        enum class sortType {
            Newest = 0,
            PopularRightnow = 1,
            MostFapped = 2,
            MostViewed = 3,
            ByTitle = 4
        };
    };
}

#endif // PARSERS_SITES_NINEHENTAI_H
