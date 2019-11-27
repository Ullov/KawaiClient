#include "mangairoapi.h"

MangairoApi::MangairoApi() {}

void MangairoApi::download()
{
    chunk = {
        "Host: mangairo.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://mangairo.com/manga-list/type-topview/ctg-42/state-completed/page-1",
        "Connection: keep-alive",
        "Cookie: __cfduid=dcb87e04a5715d9554c64bbc9c069e2ed1574690286; ci_session=rnlzhBOAPl%2Fhczm%2BJSLRMy3RwiGtVblKS7xd8T6i2L8C4qd1dV75BAKFHHSJWUsSrwXfO6U8RSEkh1Sd%2FvV4eZE4uLxjsKC%2FGeC2YnZDcxqMjEYgOrSMrEZd3iQM5lDJ1tYR5r7vC9v%2B4s8LJgH0qwtN%2B4o3zPR%2Bwe2uzplqP2pUnpf5LqbsUFIuZI6%2Bcf8BhxBNcbx0aMkF3Lep0KNSW4TPalGGVEc6ozyPHVODRRCK%2FsQuLsXXaksYFMt3ug7OaPsstmoKeMVJ2zVwGF2cPfjMsvWfSqyrQwotOYJT5xU7HwVmPHFreI%2B6w1PMa9xG0yl4x3GaNQAWE9QuVbMgamAs1fph0gMfzskUls3jE6nsKGgGuHXxqW7ldgAC4YWr8dADbaTBGB5ZS%2FgBAUtM7xPaAnppVzVAi6RzGmP%2BXG4%3D58b457066887b3c9c88763f962d41c11b8f3b3cd; _ga=GA1.2.883811971.1574690291; _gid=GA1.2.259710887.1574690291",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };
    std::vector<std::string> imagesChunk = {
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: image/webp,*/*",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive",
        "Referer: https://mangairo.com/series-1288893755/chapter-37",
        "Cookie: __cfduid=d6a3bebaba21b0c4c4145763a2e9200191574690288",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers",
    };

    CurlClass *cc = new CurlClass(chunk);
    currUrl = "https://mangairo.com/series-" + mangaId;
    std::string data = cc->performing(currUrl.c_str());

    std::vector<std::vector<std::vector<std::string>>> regexResult;
    std::vector<std::string> patterns;
    patterns.push_back("<title>([^<>]+) Manga \\| Mangairo\\.com<\\/title>");
    patterns.push_back("<meta name=\"description\" content=\"([^<>]+)\" \\/>([^<>]+)");
    patterns.push_back("<span>Alternative: <\\/span> <h2>([^<>]+)<\\/h2>");
    patterns.push_back("<a href='(https:\\/\\/mangairo\\.com\\/author\\/[0-9A-Za-z]+)'>([^<>]+)<\\/a>");
    patterns.push_back("<a href='(https:\\/\\/mangairo\\.com\\/manga-list\\/type-latest\\/ctg-[\\d]+\\/state-all\\/page-[\\d]+)'>([^<>]+)<\\/a>");
    patterns.push_back("<a href=\"https:\\/\\/mangairo\\.com\\/manga-list\\/type-topview\\/ctg-all\\/state-[a-z]+\\/page-[\\d]\" title=\"[^\"]+\">([a-zA-Z]+)<\\/a>");
    patterns.push_back("<span>Last updated : <\\/span>\n([a-zA-Z]+-[\\d]{1,2}-[\\d]{4} [\\d]{2}:[\\d]{2}) <\\/li>");
    patterns.push_back("<a href=\"(https:\\/\\/mangairo\\.com\\/series-[\\d]+\\/chapter-[\\d\\.]+)\" title=\"[^\"]+\">[Vol\\.]{0,4}([\\d]{0,4}) ?Chapter ?([\\d]+\\.?[\\d]*):? ?([^<>]*)<\\/a>\n<p>[a-zA-Z]+-[\\d]{1,2}-[\\d]{1,2}<\\/p>");
    patterns.push_back("<img class=\"avatar\" src=\"([^\"]+)\"");
    regexResult.resize(9);
    for (int ii = 0; ii < 9; ii++)
    {
        QRegularExpression re(patterns[ii].c_str());
        QRegularExpressionMatchIterator i = re.globalMatch(data.c_str());
        for (int jj = 0; i.hasNext(); jj++)
        {
            regexResult[ii].resize(regexResult[ii].size() + 1);
            QRegularExpressionMatch match = i.next();
            for (int j = 0; j < 5; j++)
                regexResult[ii][jj].push_back(match.captured(j).toStdString());
        }
    }

    QJsonObject mangaInfo;
    QJsonObject tmp;
    QJsonArray tmpArr;
    mangaInfo["mangaName"] = regexResult[0][0][1].c_str();
    currUrl = regexResult[0][0][1];
    deleteNtfsConflictingChars(currUrl);
    halfPath = basePath + "\\[" + mangaId + "](" + currUrl + ')';
    std::string type = "MangaIro";
    std::string logPath = halfPath;
    logger->cppPerformLogging("Start downloading manga with mangaId = " + mangaId + " and name " + regexResult[0][0][1], type, logPath);
    mangaInfo["summary"] = regexResult[1][0][1].c_str();
    if (!regexResult[2].empty())
        mangaInfo["alternativeNames"] = regexResult[2][0][1].c_str();
    tmp["Link"] = regexResult[3][0][1].c_str();
    tmp["Name"] = regexResult[3][0][2].c_str();
    mangaInfo["author"] = tmp;
    tmp = QJsonObject();
    for (int i = 0; i < regexResult[4].size(); i++)
    {
        tmp["link"] = regexResult[4][i][1].c_str();
        tmp["name"] = regexResult[4][i][2].c_str();
        tmpArr.push_back(tmp);
    }
    tmp = QJsonObject();
    mangaInfo["genre"] = tmpArr;
    mangaInfo["status"] = regexResult[5][0][1].c_str();
    mangaInfo["lastUpdateDate"] = regexResult[6][0][1].c_str();
    tmpArr = QJsonArray();
    for (int i = 0; i < regexResult[7].size(); i++)
    {
        tmp["link"] = regexResult[7][i][1].c_str();
        tmp["volume"] = regexResult[7][i][2].c_str();
        tmp["number"] = regexResult[7][i][3].c_str();
        tmp["name"] = regexResult[7][i][4].c_str();
        tmpArr.push_front(tmp);
    }
    mangaInfo["chapters"] = tmpArr;
    mangaInfo["coverLink"] = regexResult[8][0][1].c_str();

    writeJsonDataInFile(mangaInfo, halfPath, "mangaInfo.txt");
    logger->cppPerformLogging("Manga metadata parsed and writed", type, logPath);
    cc->setHeader(imagesChunk);
    downloadAndWriteFileWithDefinedExtension(regexResult[8][0][1], *cc, halfPath, "cover");
    cc->setHeader(chunk);
    logger->cppPerformLogging("Cover downloaded and writed", type, logPath);
    pattern = "<img src=\"([^\"]+)\" alt=\"[^\"]+\" title=\"[^\"]+\" class='img_content' \\/>";

    for (int i = 0; i < tmpArr.size(); i++)
    {
        logger->cppPerformLogging("Start downloading chapter (" + std::to_string(i) + '/' + std::to_string(tmpArr.size()) + ')', type, logPath);
        currUrl = tmpArr[i].toObject().value("link").toString().toStdString();
        data = cc->performing(currUrl.c_str());
        std::vector<std::string> regexResult1;
        findMatchChars(data, pattern, regexResult1);

        std::string volume;
        std::string name;
        if (tmpArr[i].toObject().value("volume").toString().toStdString() != "")
            volume = '[' + tmpArr[i].toObject().value("volume").toString().toStdString() + ']';
        if (tmpArr[i].toObject().value("name").toString().toStdString() != "")
        {
            currUrl = tmpArr[i].toObject().value("name").toString().toStdString();
            currUrl.erase(0, 2);
            deleteNtfsConflictingChars(currUrl);
            name = '(' + currUrl + ')';
        }
        std::string number = '[' + tmpArr[i].toObject().value("number").toString().toStdString() + ']';
        cc->setHeader(imagesChunk);
        for (int j = 0; j < regexResult1.size(); j++)
        {
            downloadAndWriteFileWithDefinedExtension(regexResult1[j], *cc, halfPath + "\\chs\\[" + std::to_string(i) + ']' + volume + number  + name, std::to_string(j));
            logger->cppPerformLogging("Page " + std::to_string(j) + " in chapter " + std::to_string(i) + " downloaded", type, logPath);
        }
        cc->setHeader(chunk);
        logger->cppPerformLogging("Chapter " + std::to_string(i) + " downloaded", type, logPath);
    }
    logger->cppPerformLogging("Manga downloaded", type, logPath);
    QStringList mode;
    mode.push_back("mangairo");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());

    // <title>([^<>]+) Manga \| Mangairo\.com<\/title>                          - Title name
    // <meta name="description" content="([^<>]+)" \/>([^<>]+)                  - Title summary
    // <span>Alternative: <\/span> <h2>([^<>]+)<\/h2>                           - Alternative title name(s)
    // <a href='(https:\/\/mangairo\.com\/author\/[0-9A-Za-z]+)'>([^<>]+)<\/a>  - Author name and author link
    // <a href='(https:\/\/mangairo\.com\/manga-list\/type-latest\/ctg-[\d]+\/state-all\/page-[\d]+)'>([^<>]+)<\/a> - Genres names and links
    // <a href="https:\/\/mangairo\.com\/manga-list\/type-topview\/ctg-all\/state-[a-z]+\/page-[\d]" title="[^"]+">([a-zA-Z]+)<\/a> - Title status
    // <span>Last updated : <\/span>\n([a-zA-Z]+-[\d]{1,2}-[\d]{4} [\d]{2}:[\d]{2}) <\/li> - Last upadate date
    // <a href="(https:\/\/mangairo\.com\/series-[\d]+\/chapter-[\d\.]+)" title="[^"]+">[Vol\.]{0,4}([\d]{0,4}) ?Chapter ?([\d]+\.?[\d]*):? ?([^<>]*)<\/a>\n<p>[a-zA-Z]+-[\d]{1,2}-[\d]{1,2}<\/p> - Chapter link, volume number, chapter number, chapter name and chapter upload date
    // <img src="([^"]+)" alt="[^"]+" title="[^"]+" class='img_content' \/> - Chapter pages links
    // <img class="avatar" src="([^"]+)"    - Title cover;
}
