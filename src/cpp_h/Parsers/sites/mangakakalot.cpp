#include "mangakakalot.h"

#include "../../KTools/curl.h"
#include "../../KTools/converter.h"
#include "../../KTools/HtmlAstMaker/object.h"
#include "../../KTools/file.h"
#include <QJsonArray>

Parsers::Sites::MangaKakalot::MangaKakalot()
{
    setParserType(KTools::Enums::Parsers::MangaKakalot);
}

void Parsers::Sites::MangaKakalot::download()
{
    cc->currHeaderMode = KTools::Enums::Curl::HeaderMode::None;
    cc->setOptions();
    QByteArray data = cc->request("https://mangakakalots.com/manga/" + mangaSystemName);
    KTools::HtmlAst::Object htmlAst = KTools::HtmlAst::Object();
    htmlAst.makeAst(data);
    KTools::HtmlAst::Tag &astTag = htmlAst.rootTag->find(1).find(1).find(1).find(0); // <div class="leftCol">
    QByteArray cover = cc->request(astTag.find(2).find(0).find(0).getAttributeValue("src"));
    QJsonObject info;
    info["title"] = astTag.find(2).find(1).find(0).find(0).getInnerContent();

    currUrl = info["title"].toString();
    KTools::Converter::convertHtmlEntities(currUrl);
    KTools::Converter::toNtfsCompatibleString(currUrl);
    rootPath = basePath + "/" + currUrl.trimmed();
    for (int i = 0; KTools::File::dirExist(rootPath); i++)
        rootPath = basePath + "/" + currUrl.trimmed() + "[" + QString::number(i) + ']';

    info["altTitles"] = astTag.find(2).find(1).find(0).find(1).getInnerContent();
    info["author"] = astTag.find(2).find(1).find(1).find(0).getInnerContent();
    info["status"] = astTag.find(2).find(1).find(2).getInnerContent().replace("Status : ", "");
    info["lastUpdate"] = astTag.find(2).find(1).find(3).getInnerContent().replace("Last updated : ", "");
    info["viewCounter"] = astTag.find(2).find(1).find(5).getInnerContent().replace("View : ", "");
    KTools::HtmlAst::Tag &genresRoot = astTag.find(2).find(1).find(6);
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
    KTools::File::writeFile(KTools::Converter::convert<QJsonObject, QByteArray>(info), rootPath, "info.json");
    writeInfoLog("All info downloaded and writed.");
    KTools::File::writeFile(cover, rootPath, "cover" + defineExtension(cover));
    writeInfoLog("Cover writed");

    for (int i = 0; i < allChaptersData.size(); i++)
    {
        QString chapterFolder = allChaptersData[i].toObject().value("name").toString();
        KTools::Converter::convertHtmlEntities(chapterFolder);
        KTools::Converter::toNtfsCompatibleString(chapterFolder);
        chapterFolder = "[" + QString::number(i) + "]" + chapterFolder;
        writeInfoLog("Start download chapter with name " + chapterFolder);
        data = cc->request(allChaptersData[i].toObject().value("url").toString());
        KTools::HtmlAst::Object chapterAst = KTools::HtmlAst::Object();
        chapterAst.makeAst(data);
        KTools::HtmlAst::Tag &pagesList = chapterAst.rootTag->find(1).find(6);

        for (int j = 0; j < pagesList.getChildTags().size(); j++)
        {
            currUrl = pagesList.find(j).getAttributeValue("data-src");
            data = cc->request(currUrl);
            QString extension = defineExtension(data);
            KTools::File::writeFile(data, rootPath + "/chs/" + chapterFolder, QString::number(j) + extension);
            writeInfoLog("Page #" + QString::number(j) + " downloaded");
        }
    }
    writeInfoLog("Manga downloaded");
    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::MangaKakalot::Download));
}
