#ifndef KTOOLS_ENUMS_H
#define KTOOLS_ENUMS_H

#include <QObject>
#include <QQmlEngine>
#include "../Parsers/parserclass.h"

namespace KTools::Enums
{
    Q_NAMESPACE
    Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
    /*enum class Parsers {
        ExHentai,
        MangaDex,
        MangaIro,
        NHentaiDotNet,
        Pixiv,
        Twitter,
        VK,
        YouTube,
        NineHentai,
        MangaKakalot,
        NHentaiDotCom
    };*/
    enum class LogType {
        Custom,
        Info,
        Error,
        Debug
    };
    //Q_ENUM_NS(Parsers)
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
        enum class NHentaiDotNet {
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
        enum class NineHentai {
            Download
        };
        enum class MangaKakalot {
            Download
        };
        enum class NHentaiDotCom {
            Download
        };

        Q_ENUM_NS(ExHentai)
        Q_ENUM_NS(MangaDex)
        Q_ENUM_NS(MangaIro)
        Q_ENUM_NS(NHentaiDotNet)
        Q_ENUM_NS(Pixiv)
        Q_ENUM_NS(Twitter)
        Q_ENUM_NS(VK)
        Q_ENUM_NS(YouTube)
        Q_ENUM_NS(NineHentai)
        Q_ENUM_NS(MangaKakalot)
        Q_ENUM_NS(NHentaiDotCom)
        static void registerTypesForQml()
        {
            qmlRegisterUncreatableMetaObject(ParserModes::staticMetaObject, "KEnums", 1, 0, "ParserModes", "Is enum");
            qRegisterMetaType<ExHentai>("ParserModesExHentai");
            qRegisterMetaType<MangaDex>("ParserModesMangaDex");
            qRegisterMetaType<MangaIro>("ParserModesMangaIro");
            qRegisterMetaType<NHentaiDotNet>("ParserModesNHentaiDotNet");
            qRegisterMetaType<Pixiv>("ParserModesPixiv");
            qRegisterMetaType<Twitter>("ParserModesTwitter");
            qRegisterMetaType<VK>("ParserModesVK");
            qRegisterMetaType<YouTube>("ParserModesYouTube");
            qRegisterMetaType<NineHentai>("ParserModesNineHentai");
            qRegisterMetaType<MangaKakalot>("ParserModesMangaKakalot");
            qRegisterMetaType<NHentaiDotCom>("ParserModesNHentaiDotCom");
        }
    };
    inline void registerTypesForQml()
    {
        qmlRegisterUncreatableMetaObject(staticMetaObject, "KEnums", 1, 0, "KEnums", "Is enum");
        /*qmlRegisterUncreatableMetaObject(Parsers::staticMetaObject, "KEnums", 1, 0, "KEnums", "Is enum");
        qRegisterMetaType<Parsers::Parsers>("KEnumParsers");*/
        qRegisterMetaType<LogType>("KEnumLogType");
        ParserModes::registerTypesForQml();
    }
};

#endif // KTOOLS_ENUMS_H
