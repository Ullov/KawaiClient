#ifndef EXHENTAIAPI_H
#define EXHENTAIAPI_H

#include "../parserclass.h"

class ExhentaiApi : public Parsers::ParserClass
{
public:
    ExhentaiApi();

    QString galleryCode;
    int numberNeddedPage;

//public slots:
    void slotDownload();
    void slotGetFrontPage();


private:
    // variables
    QString galleryUrl;

    // functions
    QJsonObject getGalleryInfo(KTools::HtmlAst::Object &htmlAst);
    QJsonArray getComments(KTools::HtmlAst::Object &htmlAst);
    QJsonArray getLinksToPages(KTools::HtmlAst::Object &firstPageAst);
    void getPageLinksFromDiv(KTools::HtmlAst::Tag &hTag, QJsonArray &linksToPages);
    QJsonObject getSectionedInfo(KTools::HtmlAst::Tag &hTag);
};

#endif // EXHENTAIAPI_H
