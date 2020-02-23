#include "mangadexapi.h"

MangadexApi::MangadexApi() {}


void MangadexApi::download()
{
    chunk = {
        "Host: mangadex.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:71.0) Gecko/20100101 Firefox/71.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers",
    };

    this->cc->setHeader(chunk);
    QJsonObject object = downloadJson("https://mangadex.org/api/manga/" + mangaId); // mangaId == 24220
    QString title = object.value("manga").toObject().value("title").toString();
    KawaiConverter::toNtfsCompatibleString(title);
    rootPath = basePath + "\\[" + mangaId + "](" + title + ')';
    writeJsonDataInFile(object, rootPath + "\\txt", "chapterData.txt");
    QString type = "MangaDex";
    QString logPath = rootPath;
    logger->cppPerformLogging("Manga with mangaId = " + mangaId + " start downloading.", type, logPath);
    currUrl = "https://mangadex.org/" + object.value("manga").toObject().value("cover_url").toString();
    downloadAndWriteFileWithDefinedExtension(currUrl, rootPath, "cover");
    logger->cppPerformLogging("Cover downloaded.", type, logPath);

    QJsonObject chapters = object.value("chapter").toObject();
    QJsonObject chapter;
    QJsonArray pagesArray;
    QStringList chaptersKeys = chapters.keys();
    QString langPrefix;
    QString chapterOrder;
    QString pageDownloadUrl;
    QString chapterTitle;
    QString volume;
    logger->cppPerformLogging("Find " + QString::number(chaptersKeys.length()) + " chapters.", type, logPath);
    for (int i = 0; i < chaptersKeys.length(); i++)
    {
        logger->cppPerformLogging("Start downloading chapter #" + QString::number(i) + ".", type, logPath);
        langPrefix = chapters[chaptersKeys[i]].toObject().value("lang_code").toString();
        chapterOrder = chapters[chaptersKeys[i]].toObject().value("chapter").toString();
        chapterTitle = chapters[chaptersKeys[i]].toObject().value("title").toString();
        KawaiConverter::toNtfsCompatibleString(chapterTitle);
        volume = chapters[chaptersKeys[i]].toObject().value("volume").toString();
        currUrl = "https://mangadex.org/api/chapter/" + chaptersKeys[i];
        chapter = downloadJson(currUrl);
        pageDownloadUrl = chapter.value("server").toString() + chapter.value("hash").toString();
        pagesArray = chapter.value("page_array").toArray();
        if ((langPrefix == "gb" && enDownload == "true") || (langPrefix == "ru" && ruDownload == "true") || (langPrefix != "en" && langPrefix != "ru" && otherDownload == "true"))
        {
            writeJsonDataInFile(chapter, rootPath + "\\txt\\chs\\" + langPrefix,"[(" + volume + ')' + chapterOrder + "](" + chapterTitle + ").txt");
            for (int j = 0; j < pagesArray.size(); j++)
            {
                downloadAndWriteFileWithDefinedExtension(pageDownloadUrl + '/' + pagesArray[j].toString(), rootPath + "\\chs\\" + langPrefix + "\\[(" + volume + ')' + chapterOrder + "](" + chapterTitle + ')', QString::number(j));
                logger->cppPerformLogging("Page #" + QString::number(j) + " in chapter #" + QString::number(i) + " downloaded.", type, logPath);
            }
        }
        else
            logger->cppPerformLogging("Chapter #" + QString::number(i) + " with langPrefix = " + langPrefix + " skipped.", type, logPath);
    }

    logger->cppPerformLogging("All selected chapters downloaded.", type, logPath);
    QStringList mode;
    mode.push_back("mangadex");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
// https://mangadex.org/api/?id=355650&type=chapter
// https://mangadex.org/api/?id=15242&type=manga
}
