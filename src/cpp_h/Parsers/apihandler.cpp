#include "apihandler.h"

ApiHandler::ApiHandler() {}

void ApiHandler::slotStartDownloding(const QStringList &params, const QList<int> &mode)
{
    emit signalDownloadingStarted(mode);
    KTools::Enums::Parsers parserType = static_cast<KTools::Enums::Parsers>(mode[0]);
    if (parserType == KTools::Enums::Parsers::ExHentai)
    {
        KTools::Enums::ParserModes::ExHentai parserMode = static_cast<KTools::Enums::ParserModes::ExHentai>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::Pixiv)
    {
        KTools::Enums::ParserModes::Pixiv parserMode = static_cast<KTools::Enums::ParserModes::Pixiv>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::MangaDex)
    {
        KTools::Enums::ParserModes::MangaDex parserMode = static_cast<KTools::Enums::ParserModes::MangaDex>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::VK)
    {
        KTools::Enums::ParserModes::VK parserMode = static_cast<KTools::Enums::ParserModes::VK>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::MangaIro)
    {
        KTools::Enums::ParserModes::MangaIro parserMode = static_cast<KTools::Enums::ParserModes::MangaIro>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::YouTube)
    {
        KTools::Enums::ParserModes::YouTube parserMode = static_cast<KTools::Enums::ParserModes::YouTube>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::Twitter)
    {
        KTools::Enums::ParserModes::Twitter parserMode = static_cast<KTools::Enums::ParserModes::Twitter>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::NineHentai)
    {
        KTools::Enums::ParserModes::NineHentai parserMode = static_cast<KTools::Enums::ParserModes::NineHentai>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::MangaKakalot)
    {
        KTools::Enums::ParserModes::MangaKakalot parserMode = static_cast<KTools::Enums::ParserModes::MangaKakalot>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KTools::Enums::Parsers::NHentaiDotCom)
    {
        KTools::Enums::ParserModes::NHentaiDotCom parserMode = static_cast<KTools::Enums::ParserModes::NHentaiDotCom>(mode[1]);
        startDownloading(params, parserMode);
    }
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::ExHentai parserMode)
{
    QThread *thread = new QThread();
    ExhentaiApi *api = new ExhentaiApi();

    api->galleryCode = params[0];
    if (parserMode == KTools::Enums::ParserModes::ExHentai::FrontPage)
        api->numberNeddedPage = params[1].toInt();

    api->moveToThread(thread);
    if (parserMode == KTools::Enums::ParserModes::ExHentai::Download)
        connect(thread, SIGNAL(started()), api, SLOT(slotDownload()));
    else if (parserMode == KTools::Enums::ParserModes::ExHentai::FrontPage)
        connect(thread, SIGNAL(started()), api, SLOT(slotGetFrontPage()));

    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Pixiv parserMode)
{
    QThread *thread = new QThread();
    PixivApi *api = new PixivApi();

    api->userId = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaDex parserMode)
{
    QThread *thread = new QThread();
    MangadexApi *api = new MangadexApi();

    api->mangaId = params[0];
    api->enDownload = params[1];
    api->ruDownload = params[2];
    api->otherDownload = params[3];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::VK parserMode)
{
    QThread *thread = new QThread();
    VkApi *api = new VkApi();
    api->postUrl = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(downloadPost()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaIro parserMode)
{
    QThread *thread = new QThread();
    MangairoApi *api = new MangairoApi();

    api->mangaId = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::YouTube parserMode)
{
    QThread *thread = new QThread();
    YoutubeApi *api = new YoutubeApi();

    api->videoUrl = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::Twitter parserMode)
{
    QThread *thread = new QThread();
    TwitterApi *api = new TwitterApi();

    api->userName = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NineHentai parserMode)
{
    QThread *thread = new QThread();
    NinehentaiApi *api = new NinehentaiApi();

    api->galleryId = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::MangaKakalot parserMode)
{
    QThread *thread = new QThread();
    MangakakalotApi *api = new MangakakalotApi();

    api->mangaSystemName = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KTools::Enums::ParserModes::NHentaiDotCom parserMode)
{
    QThread *thread = new QThread();
    NHentaiDotComApi *api = new NHentaiDotComApi();

    api->slugName = params[0];

    api->moveToThread(thread);
    connect(thread, SIGNAL(started()), api, SLOT(download()));
    connectSlotsAndSignals(thread, api);
    thread->start();
}

void ApiHandler::slotDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryData)
{
    emit signalDownloadingFinished(mode, data, binaryData);
}

void ApiHandler::slotDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KTools::Enums::Parsers downloaderType)
{
    emit signalDownloadStatus(list, millisecondsFromStart, downloaderType);
}

template<typename T>
void ApiHandler::connectSlotsAndSignals(const QThread *thread, const T *apiClass)
{
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject, QVector<QByteArray>)), thread, SLOT(quit()));
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject, QVector<QByteArray>)), apiClass, SLOT(deleteLater()));
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject, QVector<QByteArray>)), this, SLOT(slotDownloadingFinished(QList<int>, QJsonObject, QVector<QByteArray>)));
    //connect(apiClass->cc, SIGNAL(progressSignal(QList<double>,qint64,KEnums::Parsers)), this, SLOT(slotDownloadStatus(QList<double>,qint64,KEnums::Parsers)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}
