#include "youtubeapi.h"

YoutubeApi::YoutubeApi()
{
    setParserType(KEnums::Parsers::YouTube);
}

void YoutubeApi::download()
{
    chunk = {
        //"Host: www.youtube.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive",
        //"Cookie: SID=lAfsYOYpFLJHvoUSoTH3JM1UheCKE4iMGpxUOwJTyRLedXAThv4AUJE98J23V3P2sKdsEQ.; HSID=AOxpqdjadLDzDte1a; SSID=AWvekEmFqcJ3ADSCq; APISID=aMGgamUQeOIsTw4N/AVLtCkJnHDYt3k-1_; SAPISID=4NtiuSdVOM_BrGbN/A1H5vNQ4MzpuEpgRA; PREF=cvdm=grid&f1=50000000&f6=400&f5=30030&gl=GB&hl=en-GB; VISITOR_INFO1_LIVE=1-JUv3mR2yw; CONSENT=YES+GB.en-GB+V8; LOGIN_INFO=AFmmF2swRQIhAPagS6SnbevQQBzmik-e1Im9hz9xRU-uIGYaO7bSSQx-AiANzT57fJ7Rbn7aTjeNaHFZI58VWeHU1G6sa-4rwcAbEA:QUQ3MjNmeFdqM0s3bzlCR0Q3NE5mcGIycGw5SmN2c1V4S3VuSmZVdTFHRmRJNm9FQTdVSDZaTUczQUFNdFBZYi1DOU5xSDlXdkpDSzY2WEcybmxuY3BkT1ZBTTdERy1jQ240bEpQV3V0NXl6TlpEZjRrSDFjUFY3X0t2UEdxcUo2eWZlWHNvd05TNzhveXRyWFFRalM5Q3c1VkZyUWMzT1FTNFJ0a2xCLVc4OVFTV3RmUV8wVHVB; SIDCC=AN0-TYspHGJXgDNl9m7cy3-1M5nr9ElL94rcNrOHfOjtJVX5nf0YiYf9fyayVdk_P1dEP36Dd2E; YSC=3hbwK03tHYk; s_gl=e3ea30620a3c9e68880a30237b86c6cfcwIAAABHQg==",
        //"Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    //this->cc->setHeader(chunk);
    cc->currHeaderMode = KEnums::CurlSettings::HeaderMode::None;
    cc->setErrFile(basePath, "errFile.txt");
    cc->setOptions();
    QString url = "https://www.youtube.com/watch?v=9twiJbZ9-nQ";
    QString videoId = "9twiJbZ9-nQ";
    QByteArray data = cc->request(url); // https://www.youtube.com/watch?v=OCsqmC2KPsY&pbj=1
    KTools::HtmlAst::Object htmlObj = KTools::HtmlAst::Object();
    htmlObj.makeAst(data);
    //data = cc->request("https://www.youtube.com/get_video_info?video_id=" + videoId);
    QJsonObject playerResponse = KTools::Converter::convert<QString, QJsonObject>(htmlObj.arrsAndObjs.objects[3].value("args").toObject().value("player_response").toString());
    QString cipher = playerResponse.value("streamingData").toObject().value("adaptiveFormats").toArray()[1].toObject().value("cipher").toString();
    QList<QString> cipherList = cipher.split("&");
    QMap<QString, QString> cipherMap;
    for (int i = 0; i < cipherList.size(); i++)
    {
        QList<QString> tmpList = cipherList[i].split("=");
        cipherMap.insert(tmpList[0], tmpList[1]);
    }
    currUrl = cipherMap["url"];
    KTools::Converter::percentEncodingToString(currUrl);
    //currUrl += "&range=0-" + QString::number(100)/*playerResponse.value("streamingData").toObject().value("adaptiveFormats").toArray()[0].toObject().value("contentLength").toString()*/;
    data = cc->request(currUrl);
    //NativeFs::writeFile(currUrl.toUtf8(), basePath, "currUrl2.txt");

    data = cc->request("https://www.youtube.com/get_video_info?video_id=" + videoId);
    QList<QByteArray> info = data.split('&');
    data = info.join("\n");
    KTools::Converter::percentEncodingToString(data);
    data = data.split('&').join("\n\t");
    //NativeFs::writeFile(data, basePath, "getVideoInfo.txt");


    endDownloadingFunction(static_cast<int>(KEnums::ParserModes::YouTube::Download));
}


QJsonObject YoutubeApi::getParamsToJsonObject(const QString &data)
{
    QList<QString> tmp = data.split('&');
    QVector<QList<QString>> videoInfo;
    for (int i = 0; i < tmp.size(); i++)
    {
        videoInfo.push_back(tmp[i].split('='));
    }
    QJsonObject tmpObject;
    QJsonObject tmpObject2;
    QJsonObject result;
    for(int i = 0; i < videoInfo.size(); i++)
    {
        tmpObject2 = QJsonObject();
        //if (!videoInfo[i][1].isNull())
        QString forDecoding = videoInfo[i][1];
        KTools::Converter::percentEncodingToString(forDecoding);
        tmpObject2["value"] = forDecoding;
        tmpObject[videoInfo[i][0]] = forDecoding;
    }
    return tmpObject;
}
