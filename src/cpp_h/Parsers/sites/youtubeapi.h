#ifndef YOUTUBEAPI_H
#define YOUTUBEAPI_H

#include "../parserclass.h"

class YoutubeApi : public ParserClass
{
public:
    YoutubeApi();

    QString videoUrl;

//public slots:
    void download();

private:
    QJsonObject getParamsToJsonObject(const QString &data);
};

#endif // YOUTUBEAPI_H
