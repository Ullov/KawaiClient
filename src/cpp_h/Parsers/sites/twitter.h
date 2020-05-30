#ifndef PARSERS_SITES_TWITTER_H
#define PARSERS_SITES_TWITTER_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class Twitter : public ParserClass
    {
    public:
        Twitter();

        QString userName;

        void download();
    };
}

#endif // PARSERS_SITES_TWITTER_H
