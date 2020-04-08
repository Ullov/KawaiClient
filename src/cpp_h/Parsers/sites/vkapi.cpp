#include "vkapi.h"

VkApi::VkApi() {}

void VkApi::downloadPost()
{
    chunk = {
        "Host: vk.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://vk.com/bookmarks",
        "Connection: keep-alive",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: remixrefkey=3c7b150f28a23c49be; remixflash=0.0.0; remixscreen_depth=24; remixdt=-10800; remixab=1; remixseenads=0; remixfeed=*.*.*.*.*.*.ps%2Ctp.photos%2Cvideos%2Cfriends%2Cgroups%2Cpodcasts%2Ckrsk2019; remixstid=1782892298_b06dee564c8becaa47; remixlang=20; remixsid=1c9285b2e5f34f18daa73dc0f2cecbc7ce8526c8b5c74a4dcadc6ac65e17c; remixua=29%7C-1%7C277%7C-1721256372; remixmdevice=1680/1050/1/!!-!!!!; remixscreen_orient=1; remixvoice=0; remixusid=NWZkY2YwODFjZDYyYWZjNDYyNmVhN2Ex; remixgp=6ce88c32eb383bb03c2c786b26128d75; remixcurr_audio=236071586_456241410; remixsts=%7B%22data%22%3A%5B%5B1576979208%2C%22time_spent%22%2C%7B%22bookmarks%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979204779%2C%22options%22%3A%7B%7D%7D%2C%22im%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979205127%2C%22options%22%3A%7B%7D%7D%2C%22wall%22%3A%7B%22full%22%3A1971%2C%22last%22%3A1576979207637%2C%22options%22%3A%7B%7D%7D%7D%5D%2C%5B1576979209%2C%22time_spent%22%2C%7B%22im%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979208129%2C%22options%22%3A%7B%7D%7D%2C%22wall%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979208667%2C%22options%22%3A%7B%7D%7D%2C%22groups%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979208749%2C%22options%22%3A%7B%7D%7D%2C%22bookmarks%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979208776%2C%22options%22%3A%7B%7D%7D%7D%5D%2C%5B1576979209%2C%22app_use_time%22%2C%22wall%7C1576940116020%7C1576940116020%7C1576979209273%7C154061%7C0%22%5D%2C%5B1576979219%2C%22time_spent%22%2C%7B%22wall%22%3A%7B%22full%22%3A6003%2C%22last%22%3A1576979216641%2C%22options%22%3A%7B%7D%7D%2C%22im%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979217133%2C%22options%22%3A%7B%7D%7D%7D%5D%2C%5B1576979230%2C%22time_spent%22%2C%7B%22wall%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979229680%2C%22options%22%3A%7B%7D%7D%2C%22groups%22%3A%7B%22full%22%3A0%2C%22last%22%3A1576979229754%2C%22options%22%3A%7B%7D%7D%7D%5D%5D%2C%22uniqueId%22%3A472534307%7D",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };
    QVector<QByteArray> alterChunk = {
        "Host: saucenao.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:72.0) Gecko/20100101 Firefox/72.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Cookie: _ga=GA1.2.1219073593.1547232016; __utma=4212273.1219073593.1547232016.1547417279.1547417279.1; __cfduid=d2086943cd7470681f3e46dcbd8163a051579295836",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    //this->cc->setHeader(chunk);
    //QByteArray data = cc->performing(postUrl.toUtf8());
    this->cc->setHeader(alterChunk);
    QByteArray data = cc->performing("https://saucenao.com/");
    //KawaiHtmlParser *khp = new KawaiHtmlParser();
    //khp->open(data);

    QString page = KawaiConverter::nationalEncodingToUtf8("Windows-1251", data);

    QVector<QVector<QVector<QString>>> regexResult;
    QVector<QString> patterns;
    patterns.push_back("&#(\\d+);");
    for (int j = 0; j < 2; j++)
    {
        regexResult.clear();
        StringOperations::executeRegex(page, patterns, regexResult);
        for (int i = 0; i < regexResult[0].size(); i++)
        {
            regexResult[0][i][1] = KawaiConverter::numberToUtf8(regexResult[0][i][1].toInt());
            page.replace(regexResult[0][i][0], regexResult[0][i][1]);
        }
        KawaiConverter::convertHtmlEntities(page);
    }

    patterns.clear();
    regexResult.clear();
    patterns.push_back("<a class=\"author\" href=\"([\\S]+)\" data-from-id=\"[\\S]+\" data-post-id=\"[\\S]+\" data-post-click-type=\"[\\S]+\">([^<]+)<\\/a>");
    patterns.push_back("<div class=\"post_date\"><a  class=\"post_link\"  href=\"([\\S]+)\"  onclick=\"return showWiki\\({[\\S]+: '[\\S]+'}, [\\S]+, [\\S]+\\);\" ><span class=\"rel_date\">([^<]+)<\\/span>");
    patterns.push_back("<div class=\"wall_text\"><div id=\"[\\S]+\" class=\"wall_post_cont _wall_post_cont\"><div class=\"wall_post_text\">([^\\n]+)<\\/div><div class=\"page_post_sized_thumbs");
    patterns.push_back("{[^ ]+}");
    patterns.push_back("<a class=\"author\" href=\"([\\S]+)\" data-from-id=\"[\\S]+\">([^\\n]+)<\\/a>");
    patterns.push_back("<div class=\"wall_reply_text\">([^\\n]+)<\\/div><\\/div><\\/div>");
    patterns.push_back("<div class=\"reply_date\"><a class=\"wd_lnk\"  class=\"post_link\"  href=\"([\\S]+)\"  onclick=\"return showWiki\\({w: '[\\S]+', reply: '[\\S]+'}, false, event\\);\" ><span class=\"rel_date\">([^\\n]+)<\\/span><\\/a><\\/div>");
    StringOperations::executeRegex(page, patterns, regexResult);

    QVector<QJsonObject> object;
    QStringList artUrls;
    for (int i = 0; i < regexResult[3].size(); i++)
    {
        QJsonObject tmpObject = KawaiConverter::convert<QString, QJsonObject>(regexResult[3][i][0]);
        if (!tmpObject.isEmpty())
            object.push_back(tmpObject);
        if (!tmpObject.value("temp").toObject().isEmpty())
        {
            QStringList keys = tmpObject.value("temp").toObject().keys();
            artUrls.append(tmpObject.value("temp").toObject().value(keys[keys.size() - 2]).toString());
        }
    }

    rootPath = basePath + "\\" + regexResult[0][0][2] + " [" + regexResult[0][0][1].mid(1) + "]\\" + regexResult[1][0][1].mid(6);

    for (int i = 0; i < artUrls.length(); i++)
        downloadAndWriteFileWithDefinedExtension(artUrls[i], rootPath + "\\imgs", QString::number(i));
    NativeFs::writeFile(regexResult[2][0][1].replace("<br>", "\n").toUtf8(), rootPath, "postText.txt");

    QJsonObject info;
    QJsonArray tmpArr;
    QJsonObject tmpObj;
    for (int i = 0; i < regexResult[4].size(); i++)
    {
        tmpObj = QJsonObject();
        tmpObj["authorLink"] = regexResult[4][i][1];
        tmpObj["authorName"] = regexResult[4][i][2];
        tmpObj["date"] = regexResult[6][i][2];
        tmpObj["commentLink"] = regexResult[6][i][1];
        tmpArr.push_back(tmpObj);
    }
    info["1"] = tmpArr;
    tmpArr = QJsonArray();
    for (int i = 0; i < regexResult[5].size(); i++)
    {
        tmpObj = QJsonObject();
        tmpObj["commentText"] = regexResult[5][i][1];
        tmpArr.push_back(tmpObj);
    }
    info["2"] = tmpArr;
    writeJsonDataInFile(info, rootPath, "info.txt");

    NativeFs::writeFile(page.toUtf8(), basePath, "test.txt");
    //writeFile(data, basePath, "test1.txt");

    std::string someth;

    // <a class="author" href="([\S]+)" data-from-id="[\S]+" data-post-id="[\S]+" data-post-click-type="[\S]+">([^<]+)<\/a>   - Post author link and name
    // <div class="post_date"><a  class="post_link"  href="([\S]+)"  onclick="return showWiki\({[\S]+: '[\S]+'}, [\S]+, [\S]+\);" ><span class="rel_date">([^<]+)<\/span> - Post link and date
    // <div class="wall_text"><div id="[\S]+" class="wall_post_cont _wall_post_cont"><div class="wall_post_text">([^\n]+)<\/div><div class="page_post_sized_thumbs - Post text
    // <a class="author" href="([\S]+)" data-from-id="[\S]+">([^\n]+)<\/a> - Comment author and him link
    // <div class="wall_reply_text">([^\n]+)<\/div><\/div><\/div> - Comment content
    // <div class="reply_date"><a class="wd_lnk"  class="post_link"  href="([\S]+)"  onclick="return showWiki\({w: '[\S]+', reply: '[\S]+'}, false, event\);" ><span class="rel_date">([^\n]+)<\/span><\/a><\/div> - Comment lnk and date
}
