#include "optionshandler.h"

OptionsHandler::OptionsHandler()
{
    bool wtf = NativeFs::fileExist(configPath + configFile);
    if (wtf)
    {
        rootProgramPath = NativeFs::readFile<QString>(configPath, configFile, QIODevice::ReadOnly | QIODevice::Text);
    }
    else
    {
        rootProgramPath = configPath;
        NativeFs::writeFile(configPath.toUtf8(), configPath, configFile, QIODevice::WriteOnly | QIODevice::Text);
    }
    logRootPath = OptionsHandler::rootProgramPath + "/log/";

    /*QFileInfo checkFil(rootProgramPath + "appConfigs.json");
    if (checkFil.exists() && checkFil.isFile())
    {
        QFile file(rootProgramPath + "appConfigs.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString data = file.readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(data.toUtf8());
        appConfigs = jDoc.object();
    }
    else
    {
        QJsonObject first;
        QJsonObject tmp;
        tmp[""]
    }*/
}

QString OptionsHandler::configFile = "config.txt";
QString OptionsHandler::configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/KawaiClient/";
QString OptionsHandler::rootProgramPath = "";
QString OptionsHandler::logRootPath = "";

QMap<KEnums::Parsers, QString> OptionsHandler::parsersWritePathes = {
    {KEnums::Parsers::ExHentai, rootProgramPath + "/Downloads/Manga/ExHentai/"},
    {KEnums::Parsers::MangaDex, rootProgramPath + "/Downloads/Manga/MangaDex/"},
    {KEnums::Parsers::MangaIro, rootProgramPath + "/Downloads/Manga/MangaIro/"},
    {KEnums::Parsers::NHentai, rootProgramPath + "/Downloads/Manga/NHentai/"},
    {KEnums::Parsers::Pixiv, rootProgramPath + "/Downloads/Images/Pixiv/"},
    {KEnums::Parsers::Twitter, rootProgramPath + "/Downloads/Mixed/Twitter/"},
    {KEnums::Parsers::VK, rootProgramPath + "/Downloads/Mixed/VK/"},
    {KEnums::Parsers::YouTube, rootProgramPath + "/Downloads/Video/YouTube/"}
};
QMap<KEnums::Parsers, QString> OptionsHandler::parsersNames = {
    {KEnums::Parsers::ExHentai, "ExHentai"},
    {KEnums::Parsers::MangaDex, "MangaDex"},
    {KEnums::Parsers::MangaIro, "MangaIro"},
    {KEnums::Parsers::NHentai, "NHentai"},
    {KEnums::Parsers::Pixiv, "Pixiv"},
    {KEnums::Parsers::Twitter, "Twitter"},
    {KEnums::Parsers::VK, "VK"},
    {KEnums::Parsers::YouTube, "YouTube"}
};

void OptionsHandler::writeOnDrive()
{
    NativeFs::writeFile(KawaiConverter::convert<QJsonObject, QByteArray>(appConfigs), rootProgramPath, "appConfigs.json");
}

void OptionsHandler::setRootProgramPath(QString path)
{
    rootProgramPath = path;
    NativeFs::writeFile(rootProgramPath.toUtf8(), configPath, configFile, QIODevice::WriteOnly | QIODevice::Text);
}

void OptionsHandler::emitRootProgramPath()
{
    emit sendRootProgramPath(rootProgramPath);
}

QString OptionsHandler::getRootProgramPath()
{
    return rootProgramPath;
}
