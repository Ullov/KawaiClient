#include "twitter.h"

#include "../../KTools/curl.h"
#include "../../KTools/converter.h"
#include "../../KTools/exforstring.h"

Parsers::Sites::Twitter::Twitter() {}

void Parsers::Sites::Twitter::download()
{
    chunk = {
        "Host: twitter.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:71.0) Gecko/20100101 Firefox/71.0",
        "Accept: application/json, text/javascript, */*; q=0.01",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "X-Twitter-Active-User: yes",
        "X-Requested-With: XMLHttpRequest",
        "DNT: 1",
        "Connection: keep-alive",
        "Referer: https://twitter.com/CeNanGam",
        "Cookie: personalization_id=\"v1_mVZwqk1OTA6wVzjkPc9RYA==\"; guest_id=v1%3A157436364565888699; _ga=GA1.2.1235834157.1574363664; _twitter_sess=BAh7CSIKZmxhc2hJQzonQWN0aW9uQ29udHJvbGxlcjo6Rmxhc2g6OkZsYXNo%250ASGFzaHsABjoKQHVzZWR7ADoPY3JlYXRlZF9hdGwrCEv4Yo9uAToMY3NyZl9p%250AZCIlY2QxYjFkNjVlM2MwODg5MmNmZDNiNWQ3OTgyNTE2NjA6B2lkIiViZmVl%250AMjQyNDliZTQwNjU2YzlkMTFiYTIxYTYyMjczZA%253D%253D--b026d9d16ff0b817c917ae7a4971582753fba921; lang=ja; external_referer=padhuUp37zilt9KL9%2B5PERZx%2FM6mz60u2uqd6t%2FHycQ%3D|0|8e8t2xd8A2w%3D; ct0=97f782d1286d72c0df2f4e38539665cd",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };

    cc->setHeader(chunk);

    QJsonObject object = downloadJson("https://twitter.com/i/profiles/show/CeNanGam/media_timeline?for_photo_rail=true");
    QVector<QString> patterns;
    patterns.append("<span class=\"tweet-media-img-placeholder\"\n[ ]+data-status-id=\"([\\d]+)\"\n[ ]+data-image-url=\"([\\S]+)\"\n[ ]+data-img-alt=\"[\\S]*\"\n[ ]+data-load-status=\"[\\S]*\"\n[ ]+background-color=\"[^\"]+\"\n[ ]+data-dominant-color=\"[\\S]+\"\n[ ]+\ndata-tweet-id=\"([\\d]+)\"\ndata-item-id=\"([\\d]+)\"\ndata-permalink-path=\"([^\"]+)\"\ndata-conversation-id=\"([\\d]+)\"\n\n\n\n\ndata-tweet-nonce=\"[-\\da-zA-Z]+\"\ndata-tweet-stat-initialized=\"[^\"]+\"\n\n\n\n\n\n\n[ ]+data-screen-name=\"([^\"]+)\" data-name=\"([^\"]+)\" data-user-id=\"([^\"]+)\"");
    QVector<QVector<QVector<QString>>> regexResult;
    KTools::ExForString::executeRegex(object.value("items_html").toString().toUtf8(), patterns, regexResult);
    QString data;
    QVector<QVector<QJsonObject>> postsJson;
    for (int i = 0; i < regexResult[0].size(); i++)
    {
        currUrl = "https://twitter.com" + regexResult[0][i][5];
        data = cc->performing(currUrl.toUtf8());
        KTools::Converter::convertHtmlEntities(data);
        postsJson.append(extractJsonObjectFromText(data));
    }


    //writeFile(object.value("items_html").toString().toUtf8(), "E:\\Win7アプリ\\downloads", "test.txt");
    QString nope;

    // <span class="tweet-media-img-placeholder"\n[ ]+data-status-id="([\d]+)"\n[ ]+data-image-url="([\S]+)"\n[ ]+data-img-alt="[\S]*"\n[ ]+data-load-status="[\S]*"\n[ ]+background-color="[^"]+"\n[ ]+data-dominant-color="[\S]+"\n[ ]+\ndata-tweet-id="([\d]+)"\ndata-item-id="([\d]+)"\ndata-permalink-path="([^"]+)"\ndata-conversation-id="([\d]+)"\n\n\n\n\ndata-tweet-nonce="[-\da-zA-Z]+"\ndata-tweet-stat-initialized="[^"]+"\n\n\n\n\n\n\n[ ]+data-screen-name="([^"]+)" data-name="([^"]+)" data-user-id="([^"]+)"
}
