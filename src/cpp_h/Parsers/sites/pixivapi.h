#ifndef PIXIVAPI_H
#define PIXIVAPI_H

#include "../parserclass.h"

class PixivApi : public Parsers::ParserClass
{
public:
    PixivApi();
    ~PixivApi();

    QString userId; // artist's id entered by user
    QStringList imagesFromApi;
    QJsonObject userData;
    QJsonObject userAllData;

//public slots:
    void download();
    void viewUser();
    void getRecomendedUsers();

private:
    QJsonObject object;
    QJsonArray arrJ; // json array for art links' list
    QString userName; // pixiv artist's user name. Now don't need
    QByteArray novelContent;
    QVector<QByteArray> novelCoverChunk;

//signals:
//    void viewDataDownloaded(QJsonObject userData, QJsonObject userAllData, QStringList imagesFromApi);
};

#endif // PIXIVAPI_H
