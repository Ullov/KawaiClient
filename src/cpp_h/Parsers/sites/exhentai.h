#ifndef PARSERS_SITES_EXHENTAI_H
#define PARSERS_SITES_EXHENTAI_H

#include "../parserclass.h"

namespace Parsers::Sites
{
    class ExHentai : public Parsers::ParserClass
    {
    public:
        ExHentai();

        QString galleryCode;
        int numberNeddedPage;

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
}

#endif // PARSERS_SITES_EXHENTAI_H
