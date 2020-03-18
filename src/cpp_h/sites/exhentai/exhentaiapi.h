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

private:
    // variables
    QString galleryUrl;

    // functions
    QJsonObject getGalleryInfo(HtmlObject &htmlAst);
    QJsonArray getComments(HtmlObject &htmlAst);
    QJsonArray getLinksToPages(HtmlObject &firstPageAst);
    void getPageLinksFromDiv(HtmlTag &hTag, QJsonArray &linksToPages);
};

#endif // EXHENTAIAPI_H
