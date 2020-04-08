#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "cpp_h/parserclass.h"

class ExhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    ExhentaiApi();

    QString galleryCode;
    int numberNeddedPage;

public slots:
    void slotDownload();
    void slotGetFrontPage();


private:
    // variables
    QString galleryUrl;

    // functions
    QJsonObject getGalleryInfo(HtmlObject &htmlAst);
    QJsonArray getComments(HtmlObject &htmlAst);
    QJsonArray getLinksToPages(HtmlObject &firstPageAst);
    void getPageLinksFromDiv(HtmlTag &hTag, QJsonArray &linksToPages);
    QJsonObject getSectionedInfo(HtmlTag &hTag);
};

#endif // EXHENTAIAPI_H
