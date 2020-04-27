#include "optionshandler.h"
#include "logging.h"
#include "curlclass.h"
#include "kenums.h"
#include "ktoolsqmlinterface.h"

// Start OptionsHandler
QString OptionsHandler::configFile = "config.txt";
QString OptionsHandler::configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/KawaiClient/";
QString OptionsHandler::rootProgramPath = "";
QString OptionsHandler::logRootPath = "";

QMap<KEnums::Parsers, QString> OptionsHandler::parsersWritePathes = {
    {KEnums::Parsers::ExHentai, rootProgramPath + "/Downloads/Manga/ExHentai/"},
    {KEnums::Parsers::MangaDex, rootProgramPath + "/Downloads/Manga/MangaDex/"},
    {KEnums::Parsers::MangaIro, rootProgramPath + "/Downloads/Manga/MangaIro/"},
    {KEnums::Parsers::NHentaiDotNet, rootProgramPath + "/Downloads/Manga/NHentai.net/"},
    {KEnums::Parsers::Pixiv, rootProgramPath + "/Downloads/Images/Pixiv/"},
    {KEnums::Parsers::Twitter, rootProgramPath + "/Downloads/Mixed/Twitter/"},
    {KEnums::Parsers::VK, rootProgramPath + "/Downloads/Mixed/VK/"},
    {KEnums::Parsers::YouTube, rootProgramPath + "/Downloads/Video/YouTube/"},
    {KEnums::Parsers::NineHentai, rootProgramPath + "/Downloads/Manga/9Hentai/"},
    {KEnums::Parsers::MangaKakalot, rootProgramPath + "/Downloads/Manga/MangaKakalot/"},
    {KEnums::Parsers::NHentaiDotCom, rootProgramPath + "/Downloads/Manga/Nhentai.com/"}
};
QMap<KEnums::Parsers, QString> OptionsHandler::parsersNames = {
    {KEnums::Parsers::ExHentai, "ExHentai"},
    {KEnums::Parsers::MangaDex, "MangaDex"},
    {KEnums::Parsers::MangaIro, "MangaIro"},
    {KEnums::Parsers::NHentaiDotNet, "NHentai.net"},
    {KEnums::Parsers::Pixiv, "Pixiv"},
    {KEnums::Parsers::Twitter, "Twitter"},
    {KEnums::Parsers::VK, "VK"},
    {KEnums::Parsers::YouTube, "YouTube"},
    {KEnums::Parsers::NineHentai, "9Hentai"},
    {KEnums::Parsers::MangaKakalot, "MangaKakalot"},
    {KEnums::Parsers::NHentaiDotCom, "NHentai.com"}
};
QJsonObject OptionsHandler::configsObj = QJsonObject();
// End OptionsHandler
// Start Logging
QString KTools::Log::logFileName = QDateTime::currentDateTime().toString("yyyy.MM.dd") + ".log";

QMap<KEnums::LogType, QString> KTools::Log::logTypePath = {
    {KEnums::LogType::Info, "/info/"},
    {KEnums::LogType::Debug, "/debug/"},
    {KEnums::LogType::Error, "/error/"},
    {KEnums::LogType::Custom, "/custom/"}
};
QMap<KEnums::LogType, QString> KTools::Log::logTypeNames = {
    {KEnums::LogType::Info, "Info"},
    {KEnums::LogType::Debug, "Debug"},
    {KEnums::LogType::Error, "Error"},
    {KEnums::LogType::Custom, "Custom"}
};
// End Logging
// Start CurlClass
QString KTools::Curl::cacertPath = QDir::temp().path() + "/KawaiClient";
QString KTools::Curl::cacertFileName = "cacert.pem";
QString KTools::Curl::fullCacertPath = cacertPath + '/' + cacertFileName;
QString KTools::Curl::pathToCacertInQrc = ":/resources/other/cacert.pem";
QString KTools::Curl::cookiePath = "";
// End CurlClass
// Start KEnusString
QMap<KEnums::Parsers, QString> keParsers = {
    {KEnums::Parsers::ExHentai, "ExHentai"},
    {KEnums::Parsers::MangaDex, "MangaDex"},
    {KEnums::Parsers::MangaIro, "MangaIro"},
    {KEnums::Parsers::NHentaiDotNet, "NHentai"},
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
QMap<KEnums::ParserModes::NHentaiDotNet, QString> pmNHentai = {
    {KEnums::ParserModes::NHentaiDotNet::Download, "Download"}
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
// Start KTolsQmlInterface
KToolsQmlInterface KToolsQmlInterface::obj = KToolsQmlInterface();
// End KTolsQmlInterface
