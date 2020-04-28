#include "ninehentaiapi.h"

NinehentaiApi::NinehentaiApi()
{
    setParserType(KTools::Enums::Parsers::NineHentai);
}

void NinehentaiApi::download()
{
    QMap<QString, QString> hea = {
        {"Host", "9hentai.com"},
        {"User-Agent", "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0"},
        {"Accept", "application/json,text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"},
        {"Accept-Language", "ja,en-US;q=0.7,en;q=0.3"},
        {"Accept-Encoding", "gzip, deflate, br"},
        {"X-Requested-With", "XMLHttpRequest"},
        {"Content-Type", "application/json;charset=utf-8"},
        {"Origin", "https://9hentai.com"},
        {"DNT", "1"},
        {"Connection", "keep-alive"},
        {"TE", "Trailers"},
        {"Pragma", "no-cache"},
        {"Cache-Control", "no-cache"}
    };
    QMap<QString, QString> imgHea = {
        {"Host", "cdn.9hentai.com"},
        {"Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"},
        {"Upgrade-Insecure-Requests", "1"}
    };

    cc->setHeader(hea);
    cc->setRequestType(KTools::Enums::Curl::RequestType::Post);
    cc->currCookieMode = KTools::Enums::Curl::CookieMode::Void;
    cc->setOptions();

    cc->currPostParam = "{\"id\":" + galleryId + "}";
    currUrl = "https://9hentai.com/api/getBookByID";
    QByteArray data = cc->request(currUrl);
    QJsonObject obj = KTools::Converter::convert<QString, QJsonObject>(data);

    if (!obj["status"].toBool())
    {
        KTools::Log::writeError("Error in API call. URL: " + currUrl + " ; PostParam: " + cc->currPostParam, "NineHentai");
        endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::NineHentai::Download));
        return;
    }

    QString titleName = obj["results"].toObject().value("title").toString();
    QString id = QString::number(obj["results"].toObject().value("id").toInt());
    KTools::Converter::toNtfsCompatibleString(titleName);

    rootPath = basePath + "/[" + id + "](" + titleName + ")";
    for (int i = 0; KTools::File::dirExist(rootPath); i++)
        rootPath = basePath + "/[" + id + "](" + titleName + ")[" + QString::number(i);

    writeInfoLog("Downloading started.");
    KTools::File::writeFile(KTools::Converter::convert<QJsonObject, QByteArray>(obj), rootPath, "info.json");
    writeInfoLog("Info downloaded.");


    cc->delHeaderLine("X-Requested-With");
    cc->delHeaderLine("Content-Type");
    cc->setHeader(imgHea);
    cc->setRequestType(KTools::Enums::Curl::RequestType::Get);
    cc->restartSession();
    cc->setOptions();
    currUrl = obj["results"].toObject().value("image_server").toString() + id +"/";
    for (int i = 1; i <= obj["results"].toObject().value("total_page").toInt(); i++)
    {
        data = cc->request(currUrl + QString::number(i) + ".jpg");
        KTools::File::writeFile(data, rootPath + "/pages", QString::number(i) + ".jpg");
        writeInfoLog("Page #" + QString::number(i) + " downloaded.");
    }

    writeInfoLog("All pages downloaded.");
    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::NineHentai::Download));
}
