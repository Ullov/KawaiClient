#include "mangakakalotapi.h"

MangakakalotApi::MangakakalotApi()
{
    setParserType(KEnums::Parsers::MangaKakalot);
}

void MangakakalotApi::download()
{
    cc->currHeaderMode = KEnums::CurlSettings::HeaderMode::None;
    cc->setOptions();
    QByteArray data = cc->request("https://mangakakalots.com/manga/" + mangaSystemName);
    HtmlObject htmlAst = HtmlObject();
    htmlAst.makeAst(data);
    HtmlTag &astTag = htmlAst.rootTag->find(1).find(1).find(1).find(0); // <div class="leftCol">
    QByteArray cover = cc->request(astTag.find(2).find(0).find(0).getAttributeValue("src"));
    QJsonObject info;
    info["title"] = astTag.find(2).find(1).find(0).find(0).getInnerContent();

    currUrl = info["title"].toString();
    KawaiConverter::convertHtmlEntities(currUrl);
    KawaiConverter::toNtfsCompatibleString(currUrl);
    rootPath = basePath + "/" + currUrl.trimmed();
    for (int i = 0; NativeFs::dirExist(rootPath); i++)
        rootPath = basePath + "/" + currUrl.trimmed() + "[" + QString::number(i) + ']';

    info["altTitles"] = astTag.find(2).find(1).find(0).find(1).getInnerContent();
    info["author"] = astTag.find(2).find(1).find(1).find(0).getInnerContent();
    info["status"] = astTag.find(2).find(1).find(2).getInnerContent().replace("Status : ", "");
    info["lastUpdate"] = astTag.find(2).find(1).find(3).getInnerContent().replace("Last updated : ", "");
    info["viewCounter"] = astTag.find(2).find(1).find(5).getInnerContent().replace("View : ", "");
    HtmlTag &genresRoot = astTag.find(2).find(1).find(6);
    QJsonArray genres;
    for (int i = 0; i < genresRoot.getChildTags().size(); i++)
    {
        genres.append(genresRoot.find(i).getInnerContent());
    }
    info["genres"] = genres;
    info["summary"] = astTag.find(3).getInnerContent();
    astTag = astTag.find(8).find(0).find(1); // <div class="chapter-list">
    QJsonArray allChaptersData;
    for (int i = 0; i < astTag.getChildTags().size(); i++)
    {
        QJsonObject chapterData;
        chapterData["url"] = astTag.find(i).find(0).find(0).getAttributeValue("href");
        chapterData["name"] = astTag.find(i).find(0).find(0).getInnerContent().trimmed();
        chapterData["viewCounter"] = astTag.find(i).find(1).getInnerContent().trimmed();
        chapterData["uploadDate"] = astTag.find(i).find(2).getInnerContent().trimmed();
        allChaptersData.append(chapterData);
    }
    info["chaptersData"] = allChaptersData;
    NativeFs::writeFile(KawaiConverter::convert<QJsonObject, QByteArray>(info), rootPath, "info.json");
    writeInfoLog("All info downloaded and writed.");
    NativeFs::writeFile(cover, rootPath, "cover" + defineExtension(cover));
    writeInfoLog("Cover writed");

    for (int i = 0; i < allChaptersData.size(); i++)
    {
        QString chapterFolder = allChaptersData[i].toObject().value("name").toString();
        KawaiConverter::convertHtmlEntities(chapterFolder);
        KawaiConverter::toNtfsCompatibleString(chapterFolder);
        writeInfoLog("Start download chapter with name " + chapterFolder);
        data = cc->request(allChaptersData[i].toObject().value("url").toString());
        HtmlObject chapterAst = HtmlObject();
        chapterAst.makeAst(data);
        HtmlTag &pagesList = chapterAst.rootTag->find(1).find(6);

        for (int j = 0; j < pagesList.getChildTags().size(); j++)
        {
            currUrl = pagesList.find(j).getAttributeValue("data-src");
            data = cc->request(currUrl);
            QString extension = defineExtension(data);
            NativeFs::writeFile(data, rootPath + "/chs/" + chapterFolder, QString::number(j) + extension);
            writeInfoLog("Page #" + QString::number(j) + " downloaded");
        }
    }

    endDownloadingFunction(static_cast<int>(KEnums::ParserModes::MangaKakalot::Download));
}
