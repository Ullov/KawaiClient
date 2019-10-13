#ifndef MANGADEXAPI_H
#define MANGADEXAPI_H

#include "cpp_h/parserclass.h"

class MangadexApi : public ParserClass
{
    Q_OBJECT
public:
    MangadexApi();

    std::string mangaId;
    std::string enDownload; // bool
    std::string ruDownload; // bool
    std::string otherDownload; // bool

public slots:
    void download();
};

#endif // MANGADEXAPI_H
