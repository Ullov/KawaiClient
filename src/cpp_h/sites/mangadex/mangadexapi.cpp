#include "mangadexapi.h"

MangadexApi::MangadexApi() {}


void MangadexApi::download()
{
    chunk = {
        "Host: mangadex.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:69.0) Gecko/20100101 Firefox/69.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers",
    };

    std::vector<std::string> wrongChars;
    wrongChars.push_back("\"");
    wrongChars.push_back("|");
    wrongChars.push_back("/");
    wrongChars.push_back(":");
    wrongChars.push_back("*");
    wrongChars.push_back("?");
    wrongChars.push_back(">");
    wrongChars.push_back("<");
    std::vector<std::string> voids;
    for (int i = 0; i < wrongChars.size(); i++)
    {
        voids.push_back("");
    }


    CurlClass *cc = new CurlClass(chunk);
    QJsonObject object = downloadJson("https://mangadex.org/api/manga/" + mangaId, *cc); // mangaId == 24220
    std::string title = object.value("manga").toObject().value("title").toString().toStdString();
    std::string rootPath = basePath + "\\[" + mangaId + "](" + title + ')';
    writeJsonDataInFile(object, rootPath + "\\txt", "chapterData.txt");
    std::string type = "MangaDex";
    std::string logPath = rootPath;
    logger->cppPerformLogging("Manga with mangaId = " + mangaId + " start downloading.", type, logPath);
    currUrl = "https://mangadex.org/" + object.value("manga").toObject().value("cover_url").toString().toStdString();
    downloadAndWriteFileWithDefinedExtension(currUrl, *cc, rootPath, "cover");
    logger->cppPerformLogging("Cover downloaded.", type, logPath);

    QJsonObject chapters = object.value("chapter").toObject();
    QJsonObject chapter;
    QJsonArray pagesArray;
    QStringList chaptersKeys = chapters.keys();
    std::string langPrefix;
    std::string chapterOrder;
    std::string pageDownloadUrl;
    std::string chapterTitle;
    std::string volume;
    logger->cppPerformLogging("Find " + std::to_string(chaptersKeys.length()) + " chapters.", type, logPath);
    for (int i = 0; i < chaptersKeys.length(); i++)
    {
        logger->cppPerformLogging("Start downloading chapter #" + std::to_string(i) + ".", type, logPath);
        langPrefix = chapters[chaptersKeys[i]].toObject().value("lang_code").toString().toStdString();
        chapterOrder = chapters[chaptersKeys[i]].toObject().value("chapter").toString().toStdString();
        chapterTitle = chapters[chaptersKeys[i]].toObject().value("title").toString().toStdString();
        replace(chapterTitle, wrongChars, voids);
        volume = chapters[chaptersKeys[i]].toObject().value("volume").toString().toStdString();
        currUrl = "https://mangadex.org/api/chapter/" + chaptersKeys[i].toStdString();
        chapter = downloadJson(currUrl, *cc);
        pageDownloadUrl = chapter.value("server").toString().toStdString() + chapter.value("hash").toString().toStdString();
        pagesArray = chapter.value("page_array").toArray();
        if ((langPrefix == "gb" && enDownload == "true") || (langPrefix == "ru" && ruDownload == "true") || (langPrefix != "en" && langPrefix != "ru" && otherDownload == "true"))
        {
            writeJsonDataInFile(chapter, rootPath + "\\txt\\chs\\" + langPrefix,"[(" + volume + ')' + chapterOrder + "](" + chapterTitle + ").txt");
            for (int j = 0; j < pagesArray.size(); j++)
            {
                downloadAndWriteFileWithDefinedExtension(pageDownloadUrl + '/' + pagesArray[j].toString().toStdString(), *cc, rootPath + "\\chs\\" + langPrefix + "\\[(" + volume + ')' + chapterOrder + "](" + chapterTitle + ')', std::to_string(j));
                logger->cppPerformLogging("Page #" + std::to_string(j) + " in chapter #" + std::to_string(i) + " downloaded.", type, logPath);
            }
        }
        else
            logger->cppPerformLogging("Chapter #" + std::to_string(i) + " with langPrefix = " + langPrefix + " skipped.", type, logPath);
    }

    logger->cppPerformLogging("All selected chapters downloaded.", type, logPath);
    QStringList mode;
    mode.push_back("mangadex");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
// https://mangadex.org/api/?id=355650&type=chapter
// https://mangadex.org/api/?id=15242&type=manga
}
