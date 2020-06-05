#include "vk.h"

#include "../../KTools/curl.h"
#include "../../KTools/converter.h"
#include "../../KTools/exforstring.h"
#include "../../KTools/file.h"
#include "../../KTools/HtmlAstMaker/object.h"
#include <QJsonArray>

Parsers::Sites::Vk::Vk()
{
    setParserType(Parsers::VK);
}

void Parsers::Sites::Vk::downloadPost()
{
    chunk = {
        "Host: vk.com",
        //"User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: */*",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive"
    };

    KTools::File::makePath(basePath);
    cc->setHeaderMode(KTools::Curl::HeaderMode::Custom);
    cc->setHttpVersion(KTools::Curl::HttpVersion::Standart);
    cc->setHeader(chunk);
    cc->setErrFile(basePath, "errFile.txt");
    cc->setOptions();
    QByteArray data = cc->request("https://vk.com/wall-64992977_1472");
    QString page = KTools::Converter::nationalEncodingToUtf8("Windows-1251", data);
    KTools::HtmlAst::Object htmlObj = KTools::HtmlAst::Object();
    htmlObj.parseJs = true;
    htmlObj.makeAst(page);
    Vk &th = *this;
    th.cc->unsetErrFile();
    //KTools::File::writeFile(page.toUtf8(), basePath, "postHtml.txt");
    KTools::HtmlAst::Tag &tagObj = htmlObj.rootTag->find("1/9/0/0/1/1/1/0/0/0/0/0/0/0");
    QString posterName = tagObj.find("0/1/0").getInnerContent();
    QString postUrl;



    QVector<QVector<QVector<QString>>> regexResult;
    QVector<QString> patterns;
    patterns.push_back("&#(\\d+);");
    for (int j = 0; j < 2; j++)
    {
        regexResult.clear();
        KTools::ExForString::executeRegex(page, patterns, regexResult);
        for (int i = 0; i < regexResult[0].size(); i++)
        {
            regexResult[0][i][1] = KTools::Converter::numberToUtf8(regexResult[0][i][1].toInt());
            page.replace(regexResult[0][i][0], regexResult[0][i][1]);
        }
        KTools::Converter::convertHtmlEntities(page);
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
    KTools::ExForString::executeRegex(page, patterns, regexResult);

    QVector<QJsonObject> object;
    QStringList artUrls;
    for (int i = 0; i < regexResult[3].size(); i++)
    {
        QJsonObject tmpObject = KTools::Converter::convert<QString, QJsonObject>(regexResult[3][i][0]);
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
    KTools::File::writeFile(regexResult[2][0][1].replace("<br>", "\n").toUtf8(), rootPath, "postText.txt");

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

    KTools::File::writeFile(page.toUtf8(), basePath, "test.txt");
    //writeFile(data, basePath, "test1.txt");

    std::string someth;

    // <a class="author" href="([\S]+)" data-from-id="[\S]+" data-post-id="[\S]+" data-post-click-type="[\S]+">([^<]+)<\/a>   - Post author link and name
    // <div class="post_date"><a  class="post_link"  href="([\S]+)"  onclick="return showWiki\({[\S]+: '[\S]+'}, [\S]+, [\S]+\);" ><span class="rel_date">([^<]+)<\/span> - Post link and date
    // <div class="wall_text"><div id="[\S]+" class="wall_post_cont _wall_post_cont"><div class="wall_post_text">([^\n]+)<\/div><div class="page_post_sized_thumbs - Post text
    // <a class="author" href="([\S]+)" data-from-id="[\S]+">([^\n]+)<\/a> - Comment author and him link
    // <div class="wall_reply_text">([^\n]+)<\/div><\/div><\/div> - Comment content
    // <div class="reply_date"><a class="wd_lnk"  class="post_link"  href="([\S]+)"  onclick="return showWiki\({w: '[\S]+', reply: '[\S]+'}, false, event\);" ><span class="rel_date">([^\n]+)<\/span><\/a><\/div> - Comment lnk and date
}
