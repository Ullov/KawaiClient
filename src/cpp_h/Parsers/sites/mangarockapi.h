#ifndef MANGAROCKAPI_H
#define MANGAROCKAPI_H

#include "../parserclass.h"

class MangarockApi : public ParserClass
{
    Q_OBJECT
public:
    MangarockApi();
    ~MangarockApi();

    std::string oid;

private:
    std::string titleName;
    std::string chapterOid;
    std::string chapterName;
    int order;
    QJsonArray arrJ;
    QJsonObject object;
    QJsonArray pageLinks;

    void downloadAndWriteMri(std::string url, CurlClass &cc, std::string directory, std::string fileName);

public slots:
    void downloadUser();
};

#endif // MANGAROCKAPI_H
