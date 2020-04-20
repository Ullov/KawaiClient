#include "optionshandler.h"
#include "logging.h"
#include "curlclass.h"
#include "kenums.h"

// Start OptionsHandler
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
    {KEnums::Parsers::YouTube, rootProgramPath + "/Downloads/Video/YouTube/"},
    {KEnums::Parsers::NineHentai, rootProgramPath + "/Downloads/Manga/9Hentai/"},
    {KEnums::Parsers::MangaKakalot, rootProgramPath + "/Downloads/Manga/MangaKakalot/"}
};
QMap<KEnums::Parsers, QString> OptionsHandler::parsersNames = {
    {KEnums::Parsers::ExHentai, "ExHentai"},
    {KEnums::Parsers::MangaDex, "MangaDex"},
    {KEnums::Parsers::MangaIro, "MangaIro"},
    {KEnums::Parsers::NHentai, "NHentai"},
    {KEnums::Parsers::Pixiv, "Pixiv"},
    {KEnums::Parsers::Twitter, "Twitter"},
    {KEnums::Parsers::VK, "VK"},
    {KEnums::Parsers::YouTube, "YouTube"},
    {KEnums::Parsers::NineHentai, "9Hentai"},
    {KEnums::Parsers::MangaKakalot, "MangaKakalot"}
};
QJsonObject OptionsHandler::configsObj = QJsonObject();
// End OptionsHandler
// Start Logging
QString Logging::logFileName = QDateTime::currentDateTime().toString("yyyy.MM.dd") + ".log";

QMap<KEnums::LogType, QString> Logging::logTypePath = {
    {KEnums::LogType::Info, "/info/"},
    {KEnums::LogType::Debug, "/debug/"},
    {KEnums::LogType::Error, "/error/"},
    {KEnums::LogType::Custom, "/custom/"}
};
QMap<KEnums::LogType, QString> Logging::logTypeNames = {
    {KEnums::LogType::Info, "Info"},
    {KEnums::LogType::Debug, "Debug"},
    {KEnums::LogType::Error, "Error"},
    {KEnums::LogType::Custom, "Custom"}
};
// End Logging
// Start CurlClass
QString CurlClass::cacertPath = QDir::temp().path() + "/KawaiClient";
QString CurlClass::cacertFileName = "cacert.pem";
QString CurlClass::fullCacertPath = cacertPath + '/' + cacertFileName;
QString CurlClass::pathToCacertInQrc = ":/resources/other/cacert.pem";
QString CurlClass::cookiePath = "";
// End CurlClass
// Start KEnusString
QMap<KEnums::Parsers, QString> keParsers = {
    {KEnums::Parsers::ExHentai, "ExHentai"},
    {KEnums::Parsers::MangaDex, "MangaDex"},
    {KEnums::Parsers::MangaIro, "MangaIro"},
    {KEnums::Parsers::NHentai, "NHentai"},
    {KEnums::Parsers::Pixiv, "Pixiv"},
    {KEnums::Parsers::Twitter, "Twitter"},
    {KEnums::Parsers::VK, "VK"},
    {KEnums::Parsers::YouTube, "YouTube"},
};
QMap<KEnums::LogType, QString> keLogType = {
    {KEnums::LogType::Info, "Info"},
    {KEnums::LogType::Debug, "Debug"},
    {KEnums::LogType::Error, "Error"},
    {KEnums::LogType::Custom, "Custom"}
};
QMap<KEnums::ParserModes::ExHentai, QString> pmExHentai = {
    {KEnums::ParserModes::ExHentai::Download, "Download"},
    {KEnums::ParserModes::ExHentai::FrontPage, "FrontPage"}
};
QMap<KEnums::ParserModes::MangaDex, QString> pmMangaDex = {
    {KEnums::ParserModes::MangaDex::Download, "Download"}
};
QMap<KEnums::ParserModes::MangaIro, QString> pmMangaIro = {
    {KEnums::ParserModes::MangaIro::Download, "Download"}
};
QMap<KEnums::ParserModes::NHentai, QString> pmNHentai = {
    {KEnums::ParserModes::NHentai::Download, "Download"}
};
QMap<KEnums::ParserModes::Pixiv, QString> pmPixiv = {
    {KEnums::ParserModes::Pixiv::Download, "Download"}
};
QMap<KEnums::ParserModes::Twitter, QString> pmTwitter = {
    {KEnums::ParserModes::Twitter::Download, "Download"}
};
QMap<KEnums::ParserModes::VK, QString> pmVK = {
    {KEnums::ParserModes::VK::Download, "Download"}
};
QMap<KEnums::ParserModes::YouTube, QString> pmYouTube = {
    {KEnums::ParserModes::YouTube::Download, "Download"}
};
// End KEnusString
