#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "cpp_h/parserclass.h"

class ExhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    ExhentaiApi();

    QString url;

public slots:
    void download();
    void viewFrontPage();

private:
    QVector<QString> regexRersult;
    QString pattern;
};

#endif // EXHENTAIAPI_H
