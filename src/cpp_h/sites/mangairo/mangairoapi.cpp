#include "mangairoapi.h"

MangairoApi::MangairoApi()
{
    setParserType(KEnums::Parsers::MangaIro);
}

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
    QVector<QByteArray> imagesChunk = {
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

    cc->setHeader(chunk);
    currUrl = "https://mangairo.com/series-" + mangaId;
    QString data = cc->performing(currUrl.toUtf8());

    QVector<QVector<QVector<QString>>> regexResult;
    QVector<QString> patterns;
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
        QRegularExpression re(patterns[ii]);
        QRegularExpressionMatchIterator i = re.globalMatch(data);
        for (int jj = 0; i.hasNext(); jj++)
        {
            regexResult[ii].resize(regexResult[ii].size() + 1);
            QRegularExpressionMatch match = i.next();
            for (int j = 0; j < 5; j++)
                regexResult[ii][jj].push_back(match.captured(j));
        }
    }

    QJsonObject mangaInfo;
    QJsonObject tmp;
    QJsonArray tmpArr;
    mangaInfo["mangaName"] = regexResult[0][0][1];
    currUrl = regexResult[0][0][1];
    KawaiConverter::toNtfsCompatibleString(currUrl);
    rootPath = basePath + "\\[" + mangaId + "](" + currUrl + ')';
    QString type = "MangaIro";
    logPath = rootPath;
    writeInfoLog("Start downloading manga with mangaId = " + mangaId + " and name " + regexResult[0][0][1]);
    mangaInfo["summary"] = regexResult[1][0][1];
    if (!regexResult[2].empty())
        mangaInfo["alternativeNames"] = regexResult[2][0][1];
    tmp["Link"] = regexResult[3][0][1];
    tmp["Name"] = regexResult[3][0][2];
    mangaInfo["author"] = tmp;
    tmp = QJsonObject();
    for (int i = 0; i < regexResult[4].size(); i++)
    {
        tmp["link"] = regexResult[4][i][1];
        tmp["name"] = regexResult[4][i][2];
        tmpArr.push_back(tmp);
    }
    tmp = QJsonObject();
    mangaInfo["genre"] = tmpArr;
    mangaInfo["status"] = regexResult[5][0][1];
    mangaInfo["lastUpdateDate"] = regexResult[6][0][1];
    tmpArr = QJsonArray();
    for (int i = 0; i < regexResult[7].size(); i++)
    {
        tmp["link"] = regexResult[7][i][1];
        tmp["volume"] = regexResult[7][i][2];
        tmp["number"] = regexResult[7][i][3];
        tmp["name"] = regexResult[7][i][4];
        tmpArr.push_front(tmp);
    }
    mangaInfo["chapters"] = tmpArr;
    mangaInfo["coverLink"] = regexResult[8][0][1];

    writeJsonDataInFile(mangaInfo, rootPath, "mangaInfo.txt");
    writeInfoLog("Manga metadata parsed and writed");
    cc->setHeader(imagesChunk);
    downloadAndWriteFileWithDefinedExtension(regexResult[8][0][1], rootPath, "cover");
    cc->setHeader(chunk);
    writeInfoLog("Cover downloaded and writed");
    QString pattern = "<img src=\"([^\"]+)\" alt=\"[^\"]+\" title=\"[^\"]+\" class='img_content' \\/>";

    for (int i = 0; i < tmpArr.size(); i++)
    {
        writeInfoLog("Start downloading chapter (" + QString::number(i) + '/' + QString::number(tmpArr.size()) + ')');
        currUrl = tmpArr[i].toObject().value("link").toString();
        data = cc->performing(currUrl.toStdString().c_str());
        QVector<QString> regexResult1;
        StringOperations::executeRegex(data, pattern, regexResult1);

        QString volume;
        QString name;
        if (tmpArr[i].toObject().value("volume").toString() != "")
            volume = '[' + tmpArr[i].toObject().value("volume").toString() + ']';
        if (tmpArr[i].toObject().value("name").toString() != "")
        {
            currUrl = tmpArr[i].toObject().value("name").toString();
            currUrl.remove(0, 2);
            KawaiConverter::toNtfsCompatibleString(currUrl);
            name = '(' + currUrl + ')';
        }
        QString number = '[' + tmpArr[i].toObject().value("number").toString() + ']';
        cc->setHeader(imagesChunk);
        for (int j = 0; j < regexResult1.size(); j++)
        {
            downloadAndWriteFileWithDefinedExtension(regexResult1[j], rootPath + "\\chs\\[" + QString::number(i) + ']' + volume + number  + name, QString::number(j));
            writeInfoLog("Page " + QString::number(j) + " in chapter " + QString::number(i) + " downloaded");
        }
        cc->setHeader(chunk);
        writeInfoLog("Chapter " + QString::number(i) + " downloaded");
    }
    writeInfoLog("Manga downloaded");
    QList<int> mode;
    mode.push_back(static_cast<int>(KEnums::Parsers::MangaIro));
    mode.push_back(static_cast<int>(KEnums::ParserModes::MangaIro::Download));
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
