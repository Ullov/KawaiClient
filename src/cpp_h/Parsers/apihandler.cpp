#include "apihandler.h"

Parsers::Handler::Handler() {}

void Parsers::Handler::slotStartDownloding(const QStringList &params, const QList<int> &mode)
{
    //emit ParsersQmlInterface::obj.apiHandlerSignalDownloadingStarted(mode);
    KTools::Enums::Parsers parserType = static_cast<KTools::Enums::Parsers>(mode[0]);
    if (parserType == KTools::Enums::Parsers::ExHentai)
    {
        KTools::Enums::ParserModes::ExHentai parserMode = static_cast<KTools::Enums::ParserModes::ExHentai>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::Pixiv)
    {
        KTools::Enums::ParserModes::Pixiv parserMode = static_cast<KTools::Enums::ParserModes::Pixiv>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::MangaDex)
    {
        KTools::Enums::ParserModes::MangaDex parserMode = static_cast<KTools::Enums::ParserModes::MangaDex>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::VK)
    {
        KTools::Enums::ParserModes::VK parserMode = static_cast<KTools::Enums::ParserModes::VK>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::MangaIro)
    {
        KTools::Enums::ParserModes::MangaIro parserMode = static_cast<KTools::Enums::ParserModes::MangaIro>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::YouTube)
    {
        KTools::Enums::ParserModes::YouTube parserMode = static_cast<KTools::Enums::ParserModes::YouTube>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::Twitter)
    {
        KTools::Enums::ParserModes::Twitter parserMode = static_cast<KTools::Enums::ParserModes::Twitter>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::NineHentai)
    {
        KTools::Enums::ParserModes::NineHentai parserMode = static_cast<KTools::Enums::ParserModes::NineHentai>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::MangaKakalot)
    {
        KTools::Enums::ParserModes::MangaKakalot parserMode = static_cast<KTools::Enums::ParserModes::MangaKakalot>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
    else if (parserType == KTools::Enums::Parsers::NHentaiDotCom)
    {
        KTools::Enums::ParserModes::NHentaiDotCom parserMode = static_cast<KTools::Enums::ParserModes::NHentaiDotCom>(mode[1]);
        QtConcurrent::run([=](){startDownloading(params, parserMode);});
    }
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::ExHentai parserMode)
{
    ExhentaiApi *api = new ExhentaiApi();
    api->galleryCode = params[0];
    if (parserMode == KTools::Enums::ParserModes::ExHentai::Download)
    {
        api->slotDownload();
    }
    else if (parserMode == KTools::Enums::ParserModes::ExHentai::FrontPage)
    {
        api->numberNeddedPage = params[1].toInt();
        api->slotGetFrontPage();
    }
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Pixiv parserMode)
{
    PixivApi *api = new PixivApi();
    api->userId = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaDex parserMode)
{
    MangadexApi *api = new MangadexApi();
    api->mangaId = params[0];
    api->enDownload = params[1];
    api->ruDownload = params[2];
    api->otherDownload = params[3];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::VK parserMode)
{
    VkApi *api = new VkApi();
    api->postUrl = params[0];
    api->downloadPost();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaIro parserMode)
{
    MangairoApi *api = new MangairoApi();
    api->mangaId = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::YouTube parserMode)
{
    YoutubeApi *api = new YoutubeApi();
    api->videoUrl = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Twitter parserMode)
{
    TwitterApi *api = new TwitterApi();
    api->userName = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NineHentai parserMode)
{
    NinehentaiApi *api = new NinehentaiApi();
    api->galleryId = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaKakalot parserMode)
{
    MangakakalotApi *api = new MangakakalotApi();
    api->mangaSystemName = params[0];
    api->download();
    delete api;
}

void Parsers::Handler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NHentaiDotCom parserMode)
{
    NHentaiDotComApi *api = new NHentaiDotComApi();
    api->slugName = params[0];
    api->download();
    delete api;
}
