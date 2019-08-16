#ifndef INSTAGRAMAPI_H
#define INSTAGRAMAPI_H

#include "cpp_h/parserclass.h"

class InstagramApi : public ParserClass
{
    Q_OBJECT
public:
    InstagramApi();
    ~InstagramApi();

    std::string userName;
    std::vector<std::string> postChunk;
    std::vector<std::string> regexResult;
    std::vector<std::string> shortcode;
    std::vector<QJsonObject> objects;
    std::string after;
    bool hasNextPage;
    std::string userId;
    std::string quryHash;
    std::string postId;
    QJsonArray postImages;
    std::string queryHash;

public slots:
    void doWork();
};

#endif // INSTAGRAMAPI_H
