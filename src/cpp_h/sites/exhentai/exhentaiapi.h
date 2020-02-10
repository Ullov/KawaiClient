#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "cpp_h/parserclass.h"

class ExhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    ExhentaiApi();

    QString galleryCode; // https://exhentai.org/g/[\d]/[\da-z]/

public slots:
    void download();
    void viewFrontPage();

private:
    QVector<QString> regexRersult;
    QString pattern;
};

#endif // EXHENTAIAPI_H
