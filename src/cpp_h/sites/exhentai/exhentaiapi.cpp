#include "exhentaiapi.h"

ExhentaiApi::ExhentaiApi()
{
    chunk = {
        "Host: exhentai.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://exhentai.org/",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: ipb_member_id=3603032; ipb_pass_hash=01a83d86714fa441982e362b9e480ca4; igneous=8eb0a9955; sk=rtzh0ml57ih3uhe9232dfnkwuyw3; s=440e72582",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    setParserType(KEnums::Parsers::ExHentai);
}

void ExhentaiApi::download()
{
    std::vector<std::string> imageChunk = {
        "Host: exhentai.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: ipb_member_id=3603032; ipb_pass_hash=01a83d86714fa441982e362b9e480ca4; igneous=8eb0a9955; sk=rtzh0ml57ih3uhe9232dfnkwuyw3; s=440e72582",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    this->cc->setHeader(chunk);

    QVector<QString> pages;
    int countGalleryPages;
    rootPath = basePath;
    QString url = "https://exhentai.org/g/" + galleryCode + "/?hc=10#comments"; // 1583231/db7901c0b7
    //currUrl = url;
    currUrl = "https://exhentai.org/g/1583231/db7901c0b7/";
    QString data = cc->performing(currUrl.toUtf8());
    HtmlObject *hObj = new HtmlObject();
    hObj->makeAst(data);

    pattern = "<title>(.*) - ExHentai.org<\\/title>";
    StringOperations::executeRegex(data, pattern, regexRersult);
    QString titleName = regexRersult[0];
    KawaiConverter::convertHtmlHexCodes(titleName);
    KawaiConverter::toNtfsCompatibleString(titleName);
    QString type = "ExHentai";
    QString logPath = rootPath + '\\' + titleName;
    writeInfoLog("Gallery with URL " + url + " start downloading.");
    writeInfoLog("Start downloading comments.");

    QVector<QString> pattenrs;
    QVector<QVector<QVector<QString>>> regexResult1;
    pattenrs.append("<div class=\"c1\"><div class=\"c2\"><div class=\"c3\">([^<]+)<a href=\"([^\"]+)\">([^<]+)<\\/a><\\/div><div class=\"c4 nosel\">(?><a name=\"ulcomment\"><\\/a>[^<]+<\\/div>|\\[<a(?> ?[\\S]+=\"[^\"]*\" ?)*>[^<]+<\\/a>] &nbsp; \\[<a (?> ?[\\S]+=\"[^\"]*\" ?)*>[^<]+<\\/a>]<\\/div><div (?> ?[\\S]+=\"[^\"]*\" ?)*>[^<]+<span (?> ?[\\S]+=\"[^\"]*\" ?)*>[^<]+<\\/span><\\/div>)?<div class=\"c\">(?><\\/?div>){2}<div class=\"c6\" id=\"[^\"]*\">([^<]*)");
    StringOperations::executeRegex(data, pattenrs, regexResult1);
    QJsonObject comments;
    QJsonArray tmp;
    for (int i = 0; i < regexResult1[0].size(); i++)
    {
        KawaiConverter::convertHtmlHexCodes(regexResult1[0][i][1]);
        KawaiConverter::convertHtmlHexCodes(regexResult1[0][i][4]);
        comments["date"] = regexResult1[0][i][1];
        comments["userLink"] = regexResult1[0][i][2];
        comments["userName"] = regexResult1[0][i][3];
        comments["content"] = regexResult1[0][i][4];
        tmp.push_back(comments);
        comments = QJsonObject();
    }
    comments["data"] = tmp;
    writeJsonDataInFile(comments, rootPath + '\\' + titleName, "comments.txt");

    writeInfoLog("Comments downloaded.");
    writeInfoLog("Gallery name: " + titleName + '.');

    pattern = "https:\\/\\/exhentai\\.org\\/g\\/[0-9]+\\/[0-9a-z]+\\/\\?p=([0-9]+)";
    StringOperations::executeRegex(data, pattern, regexRersult);
    if (!regexRersult.empty())
    {
        countGalleryPages = std::atoi(regexRersult[regexRersult.size() - 2].toUtf8()) + 1;
        writeInfoLog("Here " + QString::number(countGalleryPages) + " gallery pages.");
    }
    else
    {
        countGalleryPages = 1;
        writeInfoLog("Here one gallery page.");
    }


    int g = 0;
    for (int j = 0; j < countGalleryPages; j++)
    {
        if (j != 0)
        {
            currUrl = url + "?p=" + QString::number(j);
            data = cc->performing(currUrl.toUtf8());
        }

        pattern = "https://exhentai.org/s/([0-9a-z]+/[0-9a-z-]+)";
        StringOperations::executeRegex(data, pattern, regexRersult);
        pages = regexRersult;
        writeInfoLog("In this gallery page " + QString::number(pages.size()) + " pages.");

        for (int i = 0; i < pages.size(); i++)
        {
            writeInfoLog("Start downloading page (" + QString::number(i) + '/' + QString::number(pages.size()) + ") from (" + QString::number(j) + '/' + QString::number(countGalleryPages) + ") gallery page.");
            currUrl = "https://exhentai.org/s/" + pages[i];
            data = cc->performing(currUrl.toUtf8());
            pattern = "(https:\\/\\/exhentai\\.org\\/fullimg\\.php\\?gid=[0-9]+&amp;page=[0-9]+&amp;key=[a-z0-9]+)";
            StringOperations::executeRegex(data, pattern, regexRersult);
            if (regexRersult.empty())
            {
                pattern = "(https?:\\/\\/[a-z0-9\\.:]+\\/h\\/[a-zA-Z0-9-\\/=;_]+\\.[a-z]{0,3})";
                StringOperations::executeRegex(data, pattern, regexRersult);
            }
            KawaiConverter::convertHtmlEntities(regexRersult[0]);
            cc->setHeader(imageChunk);
            downloadAndWriteFileWithDefinedExtension(regexRersult[0], rootPath + '\\' + titleName, QString::number(g));
            cc->setHeader(chunk);
            writeInfoLog("Downloaded page (" + QString::number(i) + '/' + QString::number(pages.size()) + ").");
            g++;
            delay(1);
        }
    }

    writeInfoLog("All downloaded.");
    QStringList mode;
    mode.push_back("exhentai");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
// http://109.60.208.52:4458/h/562e3fbf9bc4502223ebb56fd1459232b69a9381-114397-650-909-jpg/keystamp=1563391800-8d2c6b354d;fileindex=71281496;xres=2400/75777774_p16_FF34.jpg
// http://91.122.52.237:15319/h/4975c38ddda3df9b8b36fffd8ae4b1d81d7a00e3-110289-650-909-jpg/keystamp=1563397500-a3f57f8685;fileindex=71281495;xres=2400/75777774_p15_FF34.jpg

// view-source:https://exhentai.org/s/049508088a/1448071-1
// https://exhentai.org/s/43c1a388a3/1448071-16
// view-source:https://exhentai.org/g/1448071/4ed35e639a/
// https://exhentai.org/g/1448071/4ed35e639a/
// view-source:https://exhentai.org/g/1446402/6e95de3c54/
// https://exhentai.org/s/298241baa5/1446402-2
// https://exhentai.org/g/1446402/6e95de3c54/
//

// (http:\/\/[0-9\.:]+\/h\/[a-zA-Z0-9-\/=;_]+.jpg)
// (https?:\/\/[0-9\\.:]+\/h\/[a-zA-Z0-9-\/=;_]+\.[a-z]{0,3})
// (https?:\/\/[a-z0-9\\.:]+\/h\/[a-zA-Z0-9-\/=;_]+\.[a-z]{0,3})

// <div class="c1"><div class="c2"><div class="c3">([^<]+)<a href="([^"]+)">([^<]+)<\/a><\/div><div class="c4 nosel">(?><a name="ulcomment"><\/a>[^<]+<\/div>|\[<a(?> ?[\S]+="[^"]*" ?)*>[^<]+<\/a>] &nbsp; \[<a (?> ?[\S]+="[^"]*" ?)*>[^<]+<\/a>]<\/div><div (?> ?[\S]+="[^"]*" ?)*>[^<]+<span (?> ?[\S]+="[^"]*" ?)*>[^<]+<\/span><\/div>)?<div class="c">(?><\/?div>){2}<div class="c6" id="[^"]*">([^<]*)
}


void ExhentaiApi::viewFrontPage()
{
    this->cc->setHeader(chunk);
    QString data = cc->performing("https://exhentai.org?inline_set=dm_e");
    pattern = "<div style=\"[^\"]+\"><a href=\"([^\"]+)\"><img style=\"[^\"]+\" alt=\"[^\"]+\" title=\"([^\"]+)\" src=\"([^\"]+)\" \\/><\\/a><\\/div>|<div class=\"gtl?\" title=\"([^:]*):([^:\"]+)\">([^<]+)<\\/div>";
    std::vector<std::vector<QString>> result;
    QJsonObject root;
    QJsonArray titles;
    QJsonObject titleItems;
    QJsonObject tags; // because of bug first item is void
    QJsonArray tagTypeItems;
    QString currentTagType = "";
    QString tmpName;
    QString tmpUrl;
    QString tmpCoverUrl;
    QRegularExpression re(pattern);
    QRegularExpressionMatchIterator i = re.globalMatch(data);
    for (int j = 0; i.hasNext(); j++)
    {
        result.resize(result.size() + 1);
        QRegularExpressionMatch match = i.next();
        for (int k = 0; k < 7; k++)
        {
            result[j].push_back(match.captured(k));
        }

        if (match.captured(1) != "")
        {
            if (/*currentTagType == ""*/j < 1)
            {
                tmpName = match.captured(2);
                tmpUrl = match.captured(1);
                tmpCoverUrl = match.captured(3);
            }
            else
            {
                tags[currentTagType] = tagTypeItems;
                titleItems["name"] = tmpName;
                tags.remove("");
                titleItems["tags"] = tags;
                titleItems["url"] = tmpUrl;
                titleItems["coverUrl"] = tmpCoverUrl;
                titles.push_back(titleItems);

                currentTagType = "";
                tags = QJsonObject();
                tagTypeItems = QJsonArray();
                titleItems = QJsonObject();

                tmpName = match.captured(2);
                tmpUrl = match.captured(1);
                tmpCoverUrl = match.captured(3);
            }
        }
        else
        {
            if (currentTagType != match.captured(4))
            {
                tags[currentTagType] = tagTypeItems;
                tagTypeItems = QJsonArray();
                if (match.captured(4) != "")
                {
                    currentTagType = match.captured(4);
                }
                else
                {
                    currentTagType = "misc";
                }
                tagTypeItems.push_back(match.captured(5));
            }
            else
            {
                tagTypeItems.push_back(match.captured(5));
            }
        }
    }
    tags[currentTagType] = tagTypeItems;
    titleItems["name"] = tmpName;
    tags.remove("");
    titleItems["tags"] = tags;
    titleItems["url"] = tmpUrl;
    titleItems["coverUrl"] = tmpCoverUrl;
    titles.push_back(titleItems);
    root["data"] = titles;

    //emit sendViewFrontPage("viewFrontPage", root);
    QStringList mode;
    mode.push_back("exhentai");
    mode.push_back("viewFrontPage");
    emit downloadingFinished(mode, root);
// <div style="[^"]+"><a href="([^"]+)"><img style="[^"]+" alt="[^"]+" title="([^"]+)" src="([^"]+)" \/><\/a><\/div>|<div class="gtl?" title="([^:]+):([^:"]+)">([^<]+)<\/div>
// <div class="gtl?" title="([^:]+):([^:"]+)">([^<]+)<\/div>
}
