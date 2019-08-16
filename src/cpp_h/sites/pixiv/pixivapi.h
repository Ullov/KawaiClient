#ifndef PIXIVAPI_H
#define PIXIVAPI_H

#include "cpp_h/parserclass.h"
#include "cpp_h/logging.h"

class PixivApi : public ParserClass
{
    Q_OBJECT
public:
    PixivApi();
    ~PixivApi();

    std::string userId; // artist's id entered by user
    Logging *logging;
    QStringList imagesFromApi;
    QJsonObject userData;
    QJsonObject userAllData;

public slots:
    void downloadUser();
    void viewUser();

private:
    QJsonObject object;
    QJsonArray arrJ; // json array for art links' list
    std::string userName; // pixiv artist's user name. Now don't need
    std::string novelContent;
    std::vector<std::string> novelCoverChunk;

signals:
    void viewDataDownloaded(QJsonObject userData, QJsonObject userAllData, QStringList imagesFromApi);
};

#endif // PIXIVAPI_H
