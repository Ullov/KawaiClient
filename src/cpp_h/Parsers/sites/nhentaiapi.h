#ifndef PARSERS_SITES_NHENTAI_H
#define PARSERS_SITES_NHENTAI_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class NHentai : public Parsers::ParserClass
    {
    public:
        NHentai();
        ~NHentai();

        QString id;

        void doWork();
    };
}

#endif // PARSERS_SITES_NHENTAI_H
