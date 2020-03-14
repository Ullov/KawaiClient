#include "mangadexapi.h"

MangadexApi::MangadexApi() {
    parserType = KEnums::Parsers::MangaDex;
    basePath = OptionsHandler::parsersWritePathes[parserType];
}


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
    writeInfoLog("Manga with mangaId = " + mangaId + " start downloading.");
    currUrl = "https://mangadex.org/" + object.value("manga").toObject().value("cover_url").toString();
    downloadAndWriteFileWithDefinedExtension(currUrl, rootPath, "cover");
    writeInfoLog("Cover downloaded.");

    QJsonObject chapters = object.value("chapter").toObject();
    QJsonObject chapter;
    QJsonArray pagesArray;
    QStringList chaptersKeys = chapters.keys();
    QString langPrefix;
    QString chapterOrder;
    QString pageDownloadUrl;
    QString chapterTitle;
    QString volume;
    writeInfoLog("Find " + QString::number(chaptersKeys.length()) + " chapters.");
    for (int i = 0; i < chaptersKeys.length(); i++)
    {
        writeInfoLog("Start downloading chapter #" + QString::number(i) + ".");
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
                writeInfoLog("Page #" + QString::number(j) + " in chapter #" + QString::number(i) + " downloaded.");
            }
        }
        else
            writeInfoLog("Chapter #" + QString::number(i) + " with langPrefix = " + langPrefix + " skipped.");
    }

    writeInfoLog("All selected chapters downloaded.");
    QStringList mode;
    mode.push_back("mangadex");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
// https://mangadex.org/api/?id=355650&type=chapter
// https://mangadex.org/api/?id=15242&type=manga
}
