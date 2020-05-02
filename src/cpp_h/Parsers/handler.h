#ifndef PARSERS_HANDLER_H
#define PARSERS_HANDLER_H

#include "sites/pixiv.h"
#include "sites/exhentai.h"
#include "sites/mangadex.h"
#include "sites/vk.h"
#include "sites/mangairo.h"
#include "sites/youtube.h"
#include "sites/twitter.h"
#include "sites/ninehentai.h"
#include "sites/mangakakalot.h"
#include "sites/nhentaidotcom.h"
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

namespace Parsers
{
    class Handler
    {
    public:
        Handler();

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
