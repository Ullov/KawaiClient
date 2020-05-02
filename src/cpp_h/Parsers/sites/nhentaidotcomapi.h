#ifndef PARSERS_SITES_NHENTAIDOTCOM_H
#define PARSERS_SITES_NHENTAIDOTCOM_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class NHentaiDotCom : public Parsers::ParserClass
    {
    public:
        NHentaiDotCom();

        QString slugName;

        void download();
    };
}

#endif // PARSERS_SITES_NHENTAIDOTCOM_H
