#ifndef NHENTAIDOTCOMAPI_H
#define NHENTAIDOTCOMAPI_H

#include "../parserclass.h"

class NHentaiDotComApi : public Parsers::ParserClass
{
public:
    NHentaiDotComApi();

    QString slugName;

//public slots:
    void download();
};

#endif // NHENTAIDOTCOMAPI_H
