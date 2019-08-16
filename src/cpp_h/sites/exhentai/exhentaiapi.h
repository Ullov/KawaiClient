#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "cpp_h/parserclass.h"

class ExhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    ExhentaiApi();

    std::string galleryUrl;

public slots:
    void doWork();

private:
    std::vector<std::string> regexRersult;
    std::string pattern;
};

#endif // EXHENTAIAPI_H
