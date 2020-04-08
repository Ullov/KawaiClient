#ifndef KENUMS_H
#define KENUMS_H

#include <QMap>
#include <QObject>
#include <QQmlEngine>

namespace KEnums
{
    Q_NAMESPACE
    Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
    enum class Parsers {
        ExHentai,
        MangaDex,
        MangaIro,
        NHentai,
        Pixiv,
        Twitter,
        VK,
        YouTube
    };
    enum class LogType {
        Custom,
        Info,
        Error,
        Debug
    };
    Q_ENUM_NS(Parsers)
    Q_ENUM_NS(LogType)
    namespace ParserModes
    {
        Q_NAMESPACE
        Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
        enum class ExHentai {
            Download,
            FrontPage
        };
        enum class MangaDex {
            Download
        };
        enum class MangaIro {
            Download
        };
        enum class NHentai {
            Download
        };
        enum class Pixiv {
            Download
        };
        enum class Twitter {
            Download
        };
        enum class VK {
            Download
        };
        enum class YouTube {
            Download
        };
        Q_ENUM_NS(ExHentai)
        Q_ENUM_NS(MangaDex)
        Q_ENUM_NS(MangaIro)
        Q_ENUM_NS(NHentai)
        Q_ENUM_NS(Pixiv)
        Q_ENUM_NS(Twitter)
        Q_ENUM_NS(VK)
        Q_ENUM_NS(YouTube)
        static void registerTypesForQml()
        {
            qmlRegisterUncreatableMetaObject(ParserModes::staticMetaObject, "KEnums", 1, 0, "ParserModes", "Is enum");
            qRegisterMetaType<KEnums::ParserModes::ExHentai>("ParserModesExHentai");
            qRegisterMetaType<KEnums::ParserModes::MangaDex>("ParserModesMangaDex");
            qRegisterMetaType<KEnums::ParserModes::MangaIro>("ParserModesMangaIro");
            qRegisterMetaType<KEnums::ParserModes::NHentai>("ParserModesNHentai");
            qRegisterMetaType<KEnums::ParserModes::Pixiv>("ParserModesPixiv");
            qRegisterMetaType<KEnums::ParserModes::Twitter>("ParserModesTwitter");
            qRegisterMetaType<KEnums::ParserModes::VK>("ParserModesVK");
            qRegisterMetaType<KEnums::ParserModes::YouTube>("ParserModesYouTube");
        }
    };
    namespace CurlSettings {
        Q_NAMESPACE
        Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
        enum class RequestType {
            Get,
            Post
        };
        enum class CookieMode {
            None,
            GetAllTimes,
            GetAndKeep,
            Keep,
            Void
        };
        enum class HeaderMode {
            None,
            Custom
        };
        enum class SetHeaderMode {
            Add,
            New
        };
        enum class HttpVersion {
            Http2,
            Standart
        };
        enum class RequestMode {
            Old,
            New
        };

        Q_ENUM_NS(SetHeaderMode)
        Q_ENUM_NS(RequestType)
        Q_ENUM_NS(CookieMode)
        Q_ENUM_NS(HeaderMode)
        static void registerTypesForQml()
        {
            qmlRegisterUncreatableMetaObject(CurlSettings::staticMetaObject, "KEnums", 1, 0, "CurlSettings", "Is enum");
            qRegisterMetaType<RequestType>("CurlSettingsRequestType");
            qRegisterMetaType<CookieMode>("CurlSettingsCookieMode");
            qRegisterMetaType<HeaderMode>("CurlSettingsHeaderMode");
            qRegisterMetaType<SetHeaderMode>("CurlSettingsSetHeaderMode");
        }
    }
    static void registerTypesForQml()
    {
        qmlRegisterUncreatableMetaObject(KEnums::staticMetaObject, "KEnums", 1, 0, "KEnums", "Is enum");
        qRegisterMetaType<KEnums::Parsers>("KEnumParsers");
        qRegisterMetaType<KEnums::LogType>("KEnumLogType");
        CurlSettings::registerTypesForQml();
        ParserModes::registerTypesForQml();
    }
};
class KEnusString
{
public:
    static QMap<KEnums::Parsers, QString> keParsers;
    static QMap<KEnums::LogType, QString> keLogType;

    static QMap<KEnums::ParserModes::ExHentai, QString> pmExHentai;
    static QMap<KEnums::ParserModes::MangaDex, QString> pmMangaDex;
    static QMap<KEnums::ParserModes::MangaIro, QString> pmMangaIro;
    static QMap<KEnums::ParserModes::NHentai, QString> pmNHentai;
    static QMap<KEnums::ParserModes::Pixiv, QString> pmPixiv;
    static QMap<KEnums::ParserModes::Twitter, QString> pmTwitter;
    static QMap<KEnums::ParserModes::VK, QString> pmVK;
    static QMap<KEnums::ParserModes::YouTube, QString> pmYouTube;
};

#endif // KENUMS_H
