#include "exhentaiapi.h"

ExhentaiApi::ExhentaiApi()
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
    setParserType(KEnums::Parsers::ExHentai);
}

void ExhentaiApi::download()
{
    currUrl = "https://exhentai.org/g/" + galleryCode + "/?hc=10#comments"; // 1583231/db7901c0b7
    //currUrl = "https://exhentai.org/g/1583231/db7901c0b7/";
    galleryUrl = "https://exhentai.org/g/" + galleryCode + '/';
    QString data = cc->performing(currUrl.toUtf8());
    HtmlObject *htmlAst = new HtmlObject();
    htmlAst->makeAst(data);
    QJsonObject info = getGalleryInfo(*htmlAst);
    currUrl = info["name"].toArray().at(0).toString();
    KawaiConverter::toNtfsCompatibleString(currUrl);
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
    NativeFs::writeFile(KawaiConverter::convert<QJsonObject, QString>(allInfo).toUtf8(), rootPath, "info.json");
    writeInfoLog("All info data writed.");

    delete htmlAst;
    for (int i = 0; i < pagesLinks.size(); i++)
    {
        htmlAst = new HtmlObject();
        currUrl = pagesLinks[i].toObject().value("linkToPage").toString();
        htmlAst->makeAst(cc->performing(currUrl.toStdString().c_str()));
        if (htmlAst->rootTag->find(1).find(1).find(6).isExist(1))
            currUrl = htmlAst->rootTag->find(1).find(1).find(6).find(1).getAttributeValue("href");
        else
            currUrl = htmlAst->rootTag->find(1).find(1).find(2).find(0).find(0).getAttributeValue("src");
        KawaiConverter::convertHtmlEntities(currUrl);
        downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "/pages/", QString::number(i));
        writeInfoLog("Page #" + QString::number(i) + " downloaded.");
    }

    writeInfoLog("Gallery downloaded.");
    QStringList mode;
    mode.push_back("exhentai");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
}

QJsonObject ExhentaiApi::getGalleryInfo(HtmlObject &htmlAst)
{
    QJsonObject info;
    QJsonObject tmpObj;
    QJsonArray tmp;
    HtmlTag &hTag = htmlAst.rootTag->find(1).find(3).find(1);
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
    info["averageRating"] = StringOperations::getDoubleNumberFromString(hTag.find(0).find(1).find(0).getInnerContent())[0]; // id="rating_label"
    hTag = htmlAst.rootTag->find(1).find(3).find(3).find(1).find(0).find(0); // <div id="taglist"><table>
    for (int i = 0; i < hTag.getChildTags().size(); i++)
    {
        tmp = QJsonArray();
        QString key = hTag.find(i).find(0).getInnerContent();
        key.chop(1);
        HtmlTag &tmpHTag = hTag.find(i).find(1);
        for (int j = 0; j < tmpHTag.getChildTags().size(); j++)
        {
            tmp.append(tmpHTag.find(j).find(0).getInnerContent());
        }
        tmpObj[key] = tmp;
    }
    info["sectionedInfo"] = tmpObj;
    return info;
}

QJsonArray ExhentaiApi::getComments(HtmlObject &htmlAst)
{
    QString commentId;
    QJsonObject tmpObj;
    QJsonArray comments;
    HtmlTag &hTag = htmlAst.rootTag->find(1).find(10); // <div id="cdiv" class="gm">
    for (int i = 0; i < hTag.getChildTags().size() - 3; i++)
    {
        HtmlTag &tmpTag = hTag.find(i);
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

QJsonArray ExhentaiApi::getLinksToPages(HtmlObject &firstPageAst)
{
    QJsonArray linksToPages;
    HtmlTag &hTag = firstPageAst.rootTag->find(1).find(5).find(1).find(0);
    //QVector<HtmlTag*> &tmpTagsVector = hTag.getChildTags();
    int pagesNumber = hTag.find(hTag.getChildTags().size() - 2).find(0).getInnerContent().toInt();
    hTag = firstPageAst.rootTag->find(1).find(7);
    getPageLinksFromDiv(hTag, linksToPages);

    if (pagesNumber > 1)
    {
        for (int i = 1; i < pagesNumber; i++)
        {
            HtmlObject *tmpHObject = new HtmlObject();
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

void ExhentaiApi::getPageLinksFromDiv(HtmlTag &hTag, QJsonArray &linksToPages)
{
    QJsonObject tmpObj;
    for (int i = 0; i < hTag.getChildTags().size() - 1; i++)
    {
        tmpObj = QJsonObject();
        HtmlTag &tmpTag = hTag.find(i).find(0);
        tmpObj["linkToPage"] = tmpTag.getAttributeValue("href");
        tmpObj["title"] = tmpTag.find(0).getAttributeValue("title");
        tmpObj["miniImageSrc"] = tmpTag.find(0).getAttributeValue("src");
        linksToPages.append(tmpObj);
    }
}
