#ifndef MANGADEXAPI_H
#define MANGADEXAPI_H

#include "cpp_h/parserclass.h"

class MangadexApi : public ParserClass
{
    Q_OBJECT
public:
    MangadexApi();

    QString mangaId;
    QString enDownload; // bool
    QString ruDownload; // bool
    QString otherDownload; // bool

public slots:
    void download();
};

#endif // MANGADEXAPI_H
