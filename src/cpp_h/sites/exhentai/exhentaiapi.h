#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "cpp_h/parserclass.h"

class ExhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    ExhentaiApi();

    std::string url;

public slots:
    void download();
    void viewFrontPage();

private:
    std::vector<std::string> regexRersult;
    std::string pattern;

signals:
    //void sendViewFrontPage(QString mode, QJsonObject data);
};

#endif // EXHENTAIAPI_H
