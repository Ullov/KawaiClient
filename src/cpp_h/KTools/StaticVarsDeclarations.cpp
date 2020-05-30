#include "options.h"
#include "log.h"
#include "curl.h"
#include "enums.h"
#include "ktoolsqmlinterface.h"
#include "../Parsers/parsersqmlinterface.h"
#include "fileidentifier.h"
#include "../Parsers/parserclass.h"

#include <QStandardPaths>
#include <QDir>
#include <QDateTime>

// Start OptionsHandler
QString KTools::Options::configFile = "config.txt";
QString KTools::Options::configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/KawaiClient/";
QString KTools::Options::rootProgramPath = "";
QString KTools::Options::logRootPath = "";

QMap<Parsers::Parsers, QString> Parsers::ParserClass::parsersWritePathes = {
    {Parsers::ExHentai, KTools::Options::rootProgramPath + "/Downloads/Manga/ExHentai/"},
    {Parsers::MangaDex, KTools::Options::rootProgramPath + "/Downloads/Manga/MangaDex/"},
    {Parsers::MangaIro, KTools::Options::rootProgramPath + "/Downloads/Manga/MangaIro/"},
    {Parsers::NHentaiDotNet, KTools::Options::rootProgramPath + "/Downloads/Manga/NHentai.net/"},
    {Parsers::Pixiv, KTools::Options::rootProgramPath + "/Downloads/Images/Pixiv/"},
    {Parsers::Twitter, KTools::Options::rootProgramPath + "/Downloads/Mixed/Twitter/"},
    {Parsers::VK, KTools::Options::rootProgramPath + "/Downloads/Mixed/VK/"},
    {Parsers::YouTube, KTools::Options::rootProgramPath + "/Downloads/Video/YouTube/"},
    {Parsers::NineHentai, KTools::Options::rootProgramPath + "/Downloads/Manga/9Hentai/"},
    {Parsers::MangaKakalot, KTools::Options::rootProgramPath + "/Downloads/Manga/MangaKakalot/"},
    {Parsers::NHentaiDotCom, KTools::Options::rootProgramPath + "/Downloads/Manga/Nhentai.com/"}
};
QMap<Parsers::Parsers, QString> Parsers::ParserClass::parsersNames = {
    {Parsers::ExHentai, "ExHentai"},
    {Parsers::MangaDex, "MangaDex"},
    {Parsers::MangaIro, "MangaIro"},
    {Parsers::NHentaiDotNet, "NHentai.net"},
    {Parsers::Pixiv, "Pixiv"},
    {Parsers::Twitter, "Twitter"},
    {Parsers::VK, "VK"},
    {Parsers::YouTube, "YouTube"},
    {Parsers::NineHentai, "9Hentai"},
    {Parsers::MangaKakalot, "MangaKakalot"},
    {Parsers::NHentaiDotCom, "NHentai.com"}
};
QJsonObject *KTools::Options::configsObj = new QJsonObject();
// End OptionsHandler
// Start Log
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
// End Log
// Start CurlClass
QString KTools::Curl::cacertPath = QDir::temp().path() + "/KawaiClient";
QString KTools::Curl::cacertFileName = "cacert.pem";
QString KTools::Curl::fullCacertPath = cacertPath + '/' + cacertFileName;
QString KTools::Curl::pathToCacertInQrc = ":/resources/other/cacert.pem";
QString KTools::Curl::cookiePath = "";
// End CurlClass
// Start KTolsQmlInterface
KToolsQmlInterface KToolsQmlInterface::obj = KToolsQmlInterface();
// End KTolsQmlInterface
// Start ParsersQmlInterface
ParsersQmlInterface ParsersQmlInterface::obj = ParsersQmlInterface();
// End ParsersQmlInterface
