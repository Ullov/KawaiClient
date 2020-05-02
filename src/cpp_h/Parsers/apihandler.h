#ifndef PARSERS_HANDLER_H
#define PARSERS_HANDLER_H

#include "sites/pixivapi.h"
#include "sites/mangarockapi.h"
#include "sites/exhentaiapi.h"
#include "sites/mangadexapi.h"
#include "sites/vkapi.h"
#include "sites/mangairoapi.h"
#include "sites/youtubeapi.h"
#include "sites/twitterapi.h"
#include "sites/ninehentaiapi.h"
#include "sites/mangakakalotapi.h"
#include "sites/nhentaidotcomapi.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

namespace Parsers
{
    class Handler
    {
    public:
        Handler();

        //KTools::Log *logger;
        //KTools::Options *options;

        static void slotStartDownloding(const QStringList &params, const QList<int> &mode);

    private:
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::ExHentai parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Pixiv parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaDex parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::VK parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaIro parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::YouTube parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Twitter parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NineHentai parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaKakalot parserMode);
        static void startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NHentaiDotCom parserMode);
    };
}


#endif // PARSERS_HANDLER_H
