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

QMap<KTools::Enums::Parsers, QString> OptionsHandler::parsersWritePathes = {
    {KTools::Enums::Parsers::ExHentai, rootProgramPath + "/Downloads/Manga/ExHentai/"},
    {KTools::Enums::Parsers::MangaDex, rootProgramPath + "/Downloads/Manga/MangaDex/"},
    {KTools::Enums::Parsers::MangaIro, rootProgramPath + "/Downloads/Manga/MangaIro/"},
    {KTools::Enums::Parsers::NHentaiDotNet, rootProgramPath + "/Downloads/Manga/NHentai.net/"},
    {KTools::Enums::Parsers::Pixiv, rootProgramPath + "/Downloads/Images/Pixiv/"},
    {KTools::Enums::Parsers::Twitter, rootProgramPath + "/Downloads/Mixed/Twitter/"},
    {KTools::Enums::Parsers::VK, rootProgramPath + "/Downloads/Mixed/VK/"},
    {KTools::Enums::Parsers::YouTube, rootProgramPath + "/Downloads/Video/YouTube/"},
    {KTools::Enums::Parsers::NineHentai, rootProgramPath + "/Downloads/Manga/9Hentai/"},
    {KTools::Enums::Parsers::MangaKakalot, rootProgramPath + "/Downloads/Manga/MangaKakalot/"},
    {KTools::Enums::Parsers::NHentaiDotCom, rootProgramPath + "/Downloads/Manga/Nhentai.com/"}
};
QMap<KTools::Enums::Parsers, QString> OptionsHandler::parsersNames = {
    {KTools::Enums::Parsers::ExHentai, "ExHentai"},
    {KTools::Enums::Parsers::MangaDex, "MangaDex"},
    {KTools::Enums::Parsers::MangaIro, "MangaIro"},
    {KTools::Enums::Parsers::NHentaiDotNet, "NHentai.net"},
    {KTools::Enums::Parsers::Pixiv, "Pixiv"},
    {KTools::Enums::Parsers::Twitter, "Twitter"},
    {KTools::Enums::Parsers::VK, "VK"},
    {KTools::Enums::Parsers::YouTube, "YouTube"},
    {KTools::Enums::Parsers::NineHentai, "9Hentai"},
    {KTools::Enums::Parsers::MangaKakalot, "MangaKakalot"},
    {KTools::Enums::Parsers::NHentaiDotCom, "NHentai.com"}
};
QJsonObject OptionsHandler::configsObj = QJsonObject();
// End OptionsHandler
// Start Logging
QString KTools::Log::logFileName = QDateTime::currentDateTime().toString("yyyy.MM.dd") + ".log";

QMap<KTools::Enums::LogType, QString> KTools::Log::logTypePath = {
    {KTools::Enums::LogType::Info, "/info/"},
    {KTools::Enums::LogType::Debug, "/debug/"},
    {KTools::Enums::LogType::Error, "/error/"},
    {KTools::Enums::LogType::Custom, "/custom/"}
};
QMap<KTools::Enums::LogType, QString> KTools::Log::logTypeNames = {
    {KTools::Enums::LogType::Info, "Info"},
    {KTools::Enums::LogType::Debug, "Debug"},
    {KTools::Enums::LogType::Error, "Error"},
    {KTools::Enums::LogType::Custom, "Custom"}
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
/*QMap<KEnums::Parsers, QString> keParsers = {
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
};*/
// End KEnusString
// Start KTolsQmlInterface
KToolsQmlInterface KToolsQmlInterface::obj = KToolsQmlInterface();
// End KTolsQmlInterface
