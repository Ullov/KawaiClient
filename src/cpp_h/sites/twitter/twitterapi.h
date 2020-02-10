#ifndef TWITTERAPI_H
#define TWITTERAPI_H

#include "cpp_h/parserclass.h"

class TwitterApi : public ParserClass
{
    Q_OBJECT
public:
    TwitterApi();

    QString userName;

public slots:
    void download();
};

#endif // TWITTERAPI_H
