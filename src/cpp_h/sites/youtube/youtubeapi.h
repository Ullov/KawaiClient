#ifndef YOUTUBEAPI_H
#define YOUTUBEAPI_H

#include "cpp_h/parserclass.h"

class YoutubeApi : public ParserClass
{
    Q_OBJECT
public:
    YoutubeApi();

    QString videoUrl;

public slots:
    void download();

private:
    QJsonObject getParamsToJsonObject(const QString &data);
};

#endif // YOUTUBEAPI_H
