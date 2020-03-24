#include "apihandler.h"

ApiHandler::ApiHandler() {}

void ApiHandler::slotStartDownloding(const QStringList &params, const QList<int> &mode)
{
    emit signalDownloadingStarted(mode);
    KEnums::Parsers parserType = static_cast<KEnums::Parsers>(mode[0]);
    if (parserType == KEnums::Parsers::ExHentai)
    {
        KEnums::ParserModes::ExHentai parserMode = static_cast<KEnums::ParserModes::ExHentai>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::Pixiv)
    {
        KEnums::ParserModes::Pixiv parserMode = static_cast<KEnums::ParserModes::Pixiv>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::MangaDex)
    {
        KEnums::ParserModes::MangaDex parserMode = static_cast<KEnums::ParserModes::MangaDex>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::VK)
    {
        KEnums::ParserModes::VK parserMode = static_cast<KEnums::ParserModes::VK>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::MangaIro)
    {
        KEnums::ParserModes::MangaIro parserMode = static_cast<KEnums::ParserModes::MangaIro>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::YouTube)
    {
        KEnums::ParserModes::YouTube parserMode = static_cast<KEnums::ParserModes::YouTube>(mode[1]);
        startDownloading(params, parserMode);
    }
    else if (parserType == KEnums::Parsers::Twitter)
    {
        KEnums::ParserModes::Twitter parserMode = static_cast<KEnums::ParserModes::Twitter>(mode[1]);
        startDownloading(params, parserMode);
    }
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::ExHentai parserMode)
{
    QThread *thread = new QThread();
    ExhentaiApi *eApi = new ExhentaiApi();

    eApi->galleryCode = params[0];
    if (parserMode == KEnums::ParserModes::ExHentai::FrontPage)
        eApi->numberNeddedPage = params[1].toInt();

    eApi->moveToThread(thread);
    if (parserMode == KEnums::ParserModes::ExHentai::Download)
        connect(thread, SIGNAL(started()), eApi, SLOT(slotDownload()));
    else if (parserMode == KEnums::ParserModes::ExHentai::FrontPage)
        connect(thread, SIGNAL(started()), eApi, SLOT(slotGetFrontPage()));

    connect(eApi, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), thread, SLOT(quit()));
    connect(eApi, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), eApi, SLOT(deleteLater()));
    connect(eApi, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    connect(eApi->cc, SIGNAL(progressSignal(QList<double>,qint64,KEnums::Parsers)), this, SLOT(downloadStatus(QList<double>,qint64,KEnums::Parsers)));

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::Pixiv parserMode)
{
    QThread *thread = new QThread();
    PixivApi *pApi = new PixivApi();

    pApi->userId = params[0];

    pApi->moveToThread(thread);
    connectSlotsAndSignals(thread, pApi);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::MangaDex parserMode)
{
    QThread *thread = new QThread();
    MangadexApi *mdApi = new MangadexApi();

    mdApi->mangaId = params[0];
    mdApi->enDownload = params[1];
    mdApi->ruDownload = params[2];
    mdApi->otherDownload = params[3];

    mdApi->moveToThread(thread);
    connectSlotsAndSignals(thread, mdApi);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::VK parserMode)
{
    QThread *thread = new QThread();
    VkApi *vApi = new VkApi();
    vApi->postUrl = params[0];

    vApi->moveToThread(thread);
    connectSlotsAndSignals(thread, vApi);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::MangaIro parserMode)
{
    QThread *thread = new QThread();
    MangairoApi *maApi = new MangairoApi();

    maApi->mangaId = params[0];

    maApi->moveToThread(thread);
    connectSlotsAndSignals(thread, maApi);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::YouTube parserMode)
{
    QThread *thread = new QThread();
    YoutubeApi *yApi = new YoutubeApi();

    yApi->videoUrl = params[0];

    yApi->moveToThread(thread);
    connectSlotsAndSignals(thread, yApi);
    thread->start();
}

void ApiHandler::startDownloading(const QStringList &params, const KEnums::ParserModes::Twitter parserMode)
{
    QThread *thread = new QThread();
    TwitterApi *tApi = new TwitterApi();

    tApi->userName = params[0];

    tApi->moveToThread(thread);
    connectSlotsAndSignals(thread, tApi);
    thread->start();
}

void ApiHandler::slotDownloadingFinished(const QList<int> mode, const QJsonObject data)
{
    emit signalDownloadingFinished(mode, data);
}

void ApiHandler::slotDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType)
{
    emit signalDownloadStatus(list, millisecondsFromStart, downloaderType);
}

template<typename T>
void ApiHandler::connectSlotsAndSignals(const QThread *thread, const T *apiClass)
{
    connect(thread, SIGNAL(started()), apiClass, SLOT(download()));
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), thread, SLOT(quit()));
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), apiClass, SLOT(deleteLater()));
    connect(apiClass, SIGNAL(downloadingFinished(QList<int>, QJsonObject)), this, SLOT(slotDownloadingFinished(QList<int>, QJsonObject)));
    connect(apiClass->cc, SIGNAL(progressSignal(QList<double>,qint64,KEnums::Parsers)), this, SLOT(slotDownloadStatus(QList<double>,qint64,KEnums::Parsers)));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}
