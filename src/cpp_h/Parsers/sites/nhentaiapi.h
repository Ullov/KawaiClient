#ifndef NHENTAIAPI_H
#define NHENTAIAPI_H

#include "../parserclass.h"

class NhentaiApi : public Parsers::ParserClass
{
public:
    NhentaiApi();
    ~NhentaiApi();

    QString id;

//public slots:
    void doWork();
};

#endif // NHENTAIAPI_H
