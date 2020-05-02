#include "nhentaidotcomapi.h"

Parsers::Sites::NHentaiDotCom::NHentaiDotCom()
{
    setParserType(KTools::Enums::Parsers::NHentaiDotCom);
}

void Parsers::Sites::NHentaiDotCom::download()
{
    cc->currHeaderMode = KTools::Enums::Curl::HeaderMode::None;
    cc->setOptions();
    cc->request("https://nhentai.com");
    QString url = "https://nhentai.com/api/comics/" + slugName;
    QByteArray data = cc->request(url);
    QJsonObject info = KTools::Converter::convert<QString, QJsonObject>(data);
    QString title = info.value("title").toString();
    QString id = QString::number(info.value("id").toInt());
    KTools::Converter::toNtfsCompatibleString(title);

    rootPath = basePath + "/[" + id + "](" + title + ')';
    for (int i = 0; KTools::File::dirExist(rootPath); i++)
        rootPath = basePath + "/[" + id + "](" + title + ")[" + QString::number(i) + ']';

    writeInfoLog("Downloading started.");

    data = cc->request(url + "/images");
    QJsonObject pages = KTools::Converter::convert<QString, QJsonObject>(data);
    writeInfoLog("Info and pages JSON downloaded.");
    KTools::File::writeFile(KTools::Converter::convert<QJsonObject, QByteArray>(pages), rootPath, "pages.json");
    KTools::File::writeFile(KTools::Converter::convert<QJsonObject, QByteArray>(info), rootPath, "info.json");
    writeInfoLog("Info and pages JSON writed.");

    QJsonArray pagesLinks = pages.value("images").toArray();
    for (int i = 0; i < pagesLinks.size(); i++)
    {
        writeInfoLog("Starting download page #" + QString::number(i) + '.');
        data = cc->request(pagesLinks[i].toObject().value("source_url").toString());
        KTools::File::writeFile(data, rootPath + "/pages", QString::number(i) + defineExtension(data));
    }
    writeInfoLog("All pages downloaded.");

    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::NHentaiDotCom::Download));
}
