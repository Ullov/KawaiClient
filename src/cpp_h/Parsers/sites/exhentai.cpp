#include "exhentai.h"

#include "../../KTools/curl.h"
#include "../../KTools/converter.h"
#include "../../KTools/file.h"
#include "../../KTools/HtmlAstMaker/object.h"
#include "../../KTools/exforstring.h"
#include <QJsonArray>

Parsers::Sites::ExHentai::ExHentai()
{
    chunk = {
        "Host: exhentai.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3"
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://exhentai.org/g/1583231/db7901c0b7/",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: ipb_member_id=3603032; ipb_pass_hash=01a83d86714fa441982e362b9e480ca4; igneous=8eb0a9955; sk=rtzh0ml57ih3uhe9232dfnkwuyw3",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };
    this->cc->setHeader(chunk);
    setParserType(KTools::Enums::Parsers::ExHentai);
    cc->setOptions();
}

void Parsers::Sites::ExHentai::slotDownload()
{
    currUrl = "https://exhentai.org/g/" + galleryCode + "/?hc=10#comments"; // 1583231/db7901c0b7
    //currUrl = "https://exhentai.org/g/1583231/db7901c0b7/";
    galleryUrl = "https://exhentai.org/g/" + galleryCode + '/';
    QString data = cc->request(currUrl);
    KTools::HtmlAst::Object *htmlAst = new KTools::HtmlAst::Object();
    htmlAst->makeAst(data);
    QJsonObject info = getGalleryInfo(*htmlAst);
    currUrl = info["name"].toArray().at(0).toString();
    KTools::Converter::toNtfsCompatibleString(currUrl);
    rootPath = basePath + "/" + currUrl;
    writeInfoLog("Downloading started. Info extracted.");
    QJsonArray comments = getComments(*htmlAst);
    writeInfoLog("Comments extracted.");
    QJsonArray pagesLinks = getLinksToPages(*htmlAst);
    writeInfoLog("Page links extracted.");
    QJsonObject allInfo;
    allInfo["info"] = info;
    allInfo["comments"] = comments;
    allInfo["pagesLinks"] = pagesLinks;
    writeJsonDataInFile(allInfo, rootPath, "info.txt");
    KTools::File::writeFile(KTools::Converter::convert<QJsonObject, QString>(allInfo).toUtf8(), rootPath, "info.json");
    writeInfoLog("All info data writed.");

    delete htmlAst;
    for (int i = 0; i < pagesLinks.size(); i++)
    {
        htmlAst = new KTools::HtmlAst::Object();
        currUrl = pagesLinks[i].toObject().value("linkToPage").toString();
        htmlAst->makeAst(cc->request(currUrl));
        if (htmlAst->rootTag->find(1).find(1).find(6).isExist(1))
            currUrl = htmlAst->rootTag->find(1).find(1).find(6).find(1).getAttributeValue("href");
        else
            currUrl = htmlAst->rootTag->find(1).find(1).find(2).find(0).find(0).getAttributeValue("src");
        KTools::Converter::convertHtmlEntities(currUrl);
        downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "/pages/", QString::number(i));
        writeInfoLog("Page #" + QString::number(i) + " downloaded.");
        delete htmlAst;
        delay(1);
    }

    writeInfoLog("Gallery downloaded.");
    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::ExHentai::Download), QJsonObject());
}

void Parsers::Sites::ExHentai::slotGetFrontPage()
{
    /*if (numberNeddedPage >= 0)
        currUrl = "https://exhentai.org/?page=" + QString::number(numberNeddedPage) +"&inline_set=dm_e"; // URL for front page with extended view mode
    else
        currUrl = "https://exhentai.org/?page=0&inline_set=dm_e";
    HtmlObject *htmlAst = new HtmlObject();
    htmlAst->makeAst(cc->performing(currUrl.toUtf8()));

    QJsonArray galleriesInfoArr;
    HtmlTag &hTag = htmlAst->rootTag->find(1).find(2).find(1).find(3); // <table class="itg glte">
    for (int i = 0; i < hTag.getChildTags().size(); i++)
    {
        QJsonArray tmpArr;
        QJsonObject tmpObj;
        HtmlTag &tmpHTag = hTag.find(i);
        tmpObj["linkToGallery"] = tmpHTag.find(0).find(0).find(0).getAttributeValue("href"); // <a href="https://exhentai.org/g/1591450/b1b1afffa3/">
        tmpHTag = tmpHTag.find(1).find(0).find(0); // <div class="gl3e">
        tmpObj["type"] = tmpHTag.find(0).getInnerContent();
        tmpObj["postedOn"] = tmpHTag.find(1).getInnerContent();
        tmpObj["uploader"] = tmpHTag.find(3).find(0).getInnerContent();
        tmpObj["pagesNumber"] = tmpHTag.find(4).getInnerContent();
        tmpHTag = hTag.find(i).find(1).find(0).find(1).find(0); // <div class="gl4e glname"
        tmpObj["title"] = tmpHTag.find(0).getInnerContent();
        tmpHTag = tmpHTag.find(1).find(0);
        tmpObj["sectionedInfo"] = getSectionedInfo(tmpHTag);
        galleriesInfoArr.append(tmpObj);
    }*/
    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::ExHentai::FrontPage), QJsonObject());
}

QJsonObject Parsers::Sites::ExHentai::getGalleryInfo(KTools::HtmlAst::Object &htmlAst)
{
    QJsonObject info;
    QJsonObject tmpObj;
    QJsonArray tmp;
    KTools::HtmlAst::Tag &hTag = htmlAst.rootTag->find(1).find(3).find(1);
    for (int i = 0; i < hTag.getChildTagCounter(); i++)
        tmp.append(hTag.find(i).getInnerContent());
    info["name"] = tmp;
    hTag = htmlAst.rootTag->find(1).find(3).find(3).find(0); // id="gd3"
    info["type"] = hTag.find(0).find(0).getInnerContent();
    info["uploader"] = hTag.find(1).find(0).getInnerContent();
    hTag = hTag.find(2).find(0);
    for (int i = 0; i < hTag.getChildTags().size(); i++)
    {
        QString key = hTag.find(i).find(0).getInnerContent().toLower();
        key.chop(1);
        info[key] = hTag.find(i).find(1).getInnerContent();
    }
    hTag = htmlAst.rootTag->find(1).find(3).find(3).find(0).find(3); // id="gdr"
    info["peopleRatedCounter"] = hTag.find(0).find(0).find(2).find(0).getInnerContent(); // id="rating_count"
    info["averageRating"] = KTools::ExForString::getDoubleNumberFromString(hTag.find(0).find(1).find(0).getInnerContent())[0]; // id="rating_label"
    hTag = htmlAst.rootTag->find(1).find(3).find(3).find(1).find(0).find(0); // <div id="taglist"><table>
    info["sectionedInfo"] = getSectionedInfo(hTag);
    return info;
}

QJsonArray Parsers::Sites::ExHentai::getComments(KTools::HtmlAst::Object &htmlAst)
{
    QString commentId;
    QJsonObject tmpObj;
    QJsonArray comments;
    KTools::HtmlAst::Tag &hTag = htmlAst.rootTag->find(1).find(10); // <div id="cdiv" class="gm">
    for (int i = 0; i < hTag.getChildTags().size() - 3; i++)
    {
        KTools::HtmlAst::Tag &tmpTag = hTag.find(i);
        if (tmpTag.getName() != "a")
        {
            tmpObj = QJsonObject();
            tmpObj["commentId"] = commentId;
            tmpObj["date"] = tmpTag.find(0).find(0).getInnerContent().mid(0, 34);  // <div class="c3">
            tmpObj["userName"] = tmpTag.find(0).find(0).find(0).getInnerContent(); // &nbsp; <a href=
            if (tmpTag.find(0).find(2).isExist(0))
                tmpObj["score"] = tmpTag.find(0).find(2).find(0).getInnerContent();    // <div class="c5 nosel" onmouseover=
            tmpObj["text"] = tmpTag.find(1).getInnerContent();
            comments.append(tmpObj);
        }
        else
            commentId = tmpTag.getAttributeValue("name");
    }
    return comments;
}

QJsonArray Parsers::Sites::ExHentai::getLinksToPages(KTools::HtmlAst::Object &firstPageAst)
{
    QJsonArray linksToPages;
    KTools::HtmlAst::Tag &hTag = firstPageAst.rootTag->find(1).find(5).find(1).find(0);
    //QVector<HtmlTag*> &tmpTagsVector = hTag.getChildTags();
    int pagesNumber = hTag.find(hTag.getChildTags().size() - 2).find(0).getInnerContent().toInt();
    hTag = firstPageAst.rootTag->find(1).find(7);
    getPageLinksFromDiv(hTag, linksToPages);

    if (pagesNumber > 1)
    {
        for (int i = 1; i < pagesNumber; i++)
        {
            KTools::HtmlAst::Object *tmpHObject = new KTools::HtmlAst::Object();
            QString url;
            if (galleryUrl[galleryUrl.size() - 1] == "/")
                url = galleryUrl + "?p=" + QString::number(i);
            else
                url = galleryUrl + "/?p=" + QString::number(i);
            tmpHObject->makeAst(cc->performing(url.toUtf8()));
            getPageLinksFromDiv(tmpHObject->rootTag->find(1).find(7), linksToPages);
            delete tmpHObject;
        }
    }
    return linksToPages;
}

void Parsers::Sites::ExHentai::getPageLinksFromDiv(KTools::HtmlAst::Tag &hTag, QJsonArray &linksToPages)
{
    QJsonObject tmpObj;
    for (int i = 0; i < hTag.getChildTags().size() - 1; i++)
    {
        tmpObj = QJsonObject();
        KTools::HtmlAst::Tag &tmpTag = hTag.find(i).find(0);
        tmpObj["linkToPage"] = tmpTag.getAttributeValue("href");
        tmpObj["title"] = tmpTag.find(0).getAttributeValue("title");
        tmpObj["miniImageSrc"] = tmpTag.find(0).getAttributeValue("src");
        linksToPages.append(tmpObj);
    }
}

QJsonObject Parsers::Sites::ExHentai::getSectionedInfo(KTools::HtmlAst::Tag &hTag)
{
    if (!hTag.isExist(0))
        return QJsonObject();

    QJsonObject sectionedInfoObj;
    for (int i = 0; i < hTag.getChildTags().size(); i++)
    {
        QJsonArray tmp;
        QString key = hTag.find(i).find(0).getInnerContent();
        key.chop(1);
        KTools::HtmlAst::Tag &tmpHTag = hTag.find(i).find(1);
        for (int j = 0; j < tmpHTag.getChildTags().size(); j++)
        {
            tmp.append(tmpHTag.find(j).find(0).getInnerContent());
        }
        sectionedInfoObj[key] = tmp;
    }
    return sectionedInfoObj;
}
