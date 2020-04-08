#ifndef NINEHENTAIAPI_H
#define NINEHENTAIAPI_H

#include "../parserclass.h"

class NinehentaiApi : public ParserClass
{
    Q_OBJECT
public:
    NinehentaiApi();

    QString galleryId;

public slots:
    void download();

private:
    enum class sortType {
        Newest = 0,
        PopularRightnow = 1,
        MostFapped = 2,
        MostViewed = 3,
        ByTitle = 4
    };
};

#endif // NINEHENTAIAPI_H
