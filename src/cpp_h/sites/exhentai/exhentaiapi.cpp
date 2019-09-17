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
}

void ExhentaiApi::download()
{
    std::vector<std::string> imageChunk = {
        "Host: exhentai.org",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        //"Referer: https://exhentai.org/g/1446402/6e95de3c54/?p=93",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: ipb_member_id=3603032; ipb_pass_hash=01a83d86714fa441982e362b9e480ca4; igneous=8eb0a9955; sk=rtzh0ml57ih3uhe9232dfnkwuyw3",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
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

    std::vector<std::string> pages;
    int countGalleryPages;
    halfPath = basePath;
    currUrl = url;
    std::string data = cc->performing(currUrl.c_str());

    pattern = "<title>(.*) - ExHentai.org<\/title>";
    findMatchChars(data, pattern, regexRersult);
    std::string titleName = regexRersult[0];
    replace(titleName, wrongChars, voids);
    std::string type = "ExHentai";
    std::string logPath = halfPath + '\\' + titleName;
    logger->cppPerformLogging("Gallery with URL " + url + " start downloading.", type, logPath);
    logger->cppPerformLogging("Gallery name: " + titleName + '.', type, logPath);

    pattern = "https:\\/\\/exhentai\\.org\\/g\\/[0-9]+\\/[0-9a-z]+\\/\\?p=([0-9]+)";
    findMatchChars(data, pattern, regexRersult);
    if (!regexRersult.empty())
    {
        countGalleryPages = std::atoi(regexRersult[regexRersult.size() - 2].c_str()) + 1;
        logger->cppPerformLogging("Here " + std::to_string(countGalleryPages) + " gallery pages.", type, logPath);
    }
    else
    {
        countGalleryPages = 1;
        logger->cppPerformLogging("Here one gallery page.", type, logPath);
    }


    int g = 0;
    for (int j = 0; j < countGalleryPages; j++)
    {
        if (j != 0)
        {
            currUrl = url + "?p=" + std::to_string(j);
            data = cc->performing(currUrl.c_str());
        }

        pattern = "https://exhentai.org/s/([0-9a-z]+/[0-9a-z-]+)";
        findMatchChars(data, pattern, regexRersult);
        pages = regexRersult;
        logger->cppPerformLogging("In this gallery page " + std::to_string(pages.size()) + " pages.", type, logPath);

        for (int i = 0; i < pages.size(); i++)
        {
            logger->cppPerformLogging("Start downloading page (" + std::to_string(i) + '/' + std::to_string(pages.size()) + ") from (" + std::to_string(j) + '/' + std::to_string(countGalleryPages) + ") gallery page.", type, logPath);
            currUrl = "https://exhentai.org/s/" + pages[i];
            data = cc->performing(currUrl.c_str());
            pattern = "(https:\\/\\/exhentai\\.org\\/fullimg\\.php\\?gid=[0-9]+&amp;page=[0-9]+&amp;key=[a-z0-9]+)";
            findMatchChars(data, pattern, regexRersult);
            if (regexRersult.empty())
            {
                pattern = "(http:\\/\\/[0-9\\.:]+\\/h\\/[a-zA-Z0-9-\\/=;_]+.jpg)";
                findMatchChars(data, pattern, regexRersult);
            }
            replaceHtmlEntities(regexRersult[0]);
            cc->setHeader(imageChunk);
            downloadAndWriteFile(regexRersult[0], *cc, halfPath + '\\' + titleName, std::to_string(g) + ".jpg");
            cc->setHeader(chunk);
            logger->cppPerformLogging("Downloaded page (" + std::to_string(i) + '/' + std::to_string(pages.size()) + ").", type, logPath);
            g++;
            delay(1);
        }
    }

    logger->cppPerformLogging("All downloaded.", type, logPath);
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
}


void ExhentaiApi::viewFrontPage()
{
    CurlClass *cc = new CurlClass(chunk);
    std::string data = cc->performing("https://exhentai.org?inline_set=dm_e");
    pattern = "<div style=\"[^\"]+\"><a href=\"([^\"]+)\"><img style=\"[^\"]+\" alt=\"[^\"]+\" title=\"([^\"]+)\" src=\"([^\"]+)\" \\/><\\/a><\\/div>|<div class=\"gtl?\" title=\"([^:]+):([^:\"]+)\">([^<]+)<\\/div>";
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
    QRegularExpression re(pattern.c_str());
    QRegularExpressionMatchIterator i = re.globalMatch(data.c_str());
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
                currentTagType = match.captured(4);
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
