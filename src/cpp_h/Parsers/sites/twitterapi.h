#ifndef TWITTERAPI_H
#define TWITTERAPI_H

#include "../parserclass.h"

class TwitterApi : public ParserClass
{
public:
    TwitterApi();

    QString userName;

//public slots:
    void download();
};

#endif // TWITTERAPI_H
