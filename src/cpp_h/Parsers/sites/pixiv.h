#ifndef PARSERS_SITES_PIXIV_H
#define PARSERS_SITES_PIXIV_H

#include "../parserclass.h"
#include <QJsonArray>

namespace Parsers::Sites
{
    class Pixiv : public ParserClass
    {
    public:
        Pixiv();
        ~Pixiv();

        QString userId; // artist's id entered by user
        QStringList *imagesFromApi;
        QJsonObject userData;
        QJsonObject userAllData;

        void download();
        void viewUser();
        void getRecomendedUsers();

    private:
        QJsonObject object;
        QJsonArray arrJ; // json array for art links' list
        QString userName; // pixiv artist's user name. Now don't need
        QByteArray novelContent;
        QVector<QByteArray> novelCoverChunk;
    };
}

#endif // PARSERS_SITES_PIXIV_H
