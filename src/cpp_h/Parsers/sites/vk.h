#ifndef PARSERS_SITES_VK_H
#define PARSERS_SITES_VK_H

#include "../parserclass.h"
#include <locale>
#include <codecvt>

namespace Parsers::Sites
{
    class Vk : public ParserClass
    {
    public:
        Vk();

        QString postUrl;

        void downloadPost();
    };
}

#endif // PARSERS_SITES_VK_H
