#ifndef PARSERS_SITES_YOUTUBE_H
#define PARSERS_SITES_YOUTUBE_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class YouTube : public Parsers::ParserClass
    {
    public:
        YouTube();

        QString videoUrl;

        void download();

    private:
        QJsonObject getParamsToJsonObject(const QString &data);
    };
}

#endif // PARSERS_SITES_YOUTUBE_H
