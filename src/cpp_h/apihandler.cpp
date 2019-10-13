#include "apihandler.h"

ApiHandler::ApiHandler(){
    //pixivWorkInProggress = false;
    //mangarockWorkInProggress = false;
    //exhentaiWorkInProggress = false;
}
/*
void ApiHandler::pixivStartDownloading(const QString &userId)
{
    if (!pixivWorkInProggress)
    {
        pixivWorkInProggress = true;
        emit pixivDownloadingStarted();

        QThread *thread = new QThread();
        PixivApi *pApi = new PixivApi();

        pApi->userId = userId.toStdString();
        pApi->basePath = "H:\\KawaiClient\\downloaded\\pixiv";
        pApi->logger = this->logger;

        pApi->moveToThread(thread);

        connect(thread, SIGNAL(started()), pApi, SLOT(downloadUser()));
        connect(pApi, SIGNAL(downloadingFinished()), thread, SLOT(quit()));

        connect(pApi, SIGNAL(downloadingFinished()), pApi, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(pApi, SIGNAL(downloadingFinished()), this, SLOT(pixivEmitSignalDownloadingFinished()));

        thread->start();
    }
}

void ApiHandler::pixivEmitSignalDownloadingFinished()
{
    pixivWorkInProggress = false;
    emit pixivDownloadingFinished();
}

void ApiHandler::pixivViewUser(const QString &userId)
{
    if (!pixivWorkInProggress)
    {
        pixivWorkInProggress = true;
        emit pixivDownloadingStarted();

        QThread *thread = new QThread();
        PixivApi *pApi = new PixivApi();

        pApi->userId = userId.toStdString();
        pApi->basePath = "H:\\KawaiClient\\downloaded\\pixiv";
        pApi->logger = this->logger;

        pApi->moveToThread(thread);

        connect(thread, SIGNAL(started()), pApi, SLOT(viewUser()));
        connect(pApi, SIGNAL(downloadingFinished()), thread, SLOT(quit()));

        connect(pApi, SIGNAL(downloadingFinished()), pApi, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(pApi, SIGNAL(downloadingFinished()), this, SLOT(emitSignalDownloadingFinished()));
        connect(pApi, SIGNAL(pixivViewDataDownloaded(QJsonObject, QJsonObject, QStringList)), this, SLOT(pixivEmitViewDataDownloaded(QJsonObject, QJsonObject, QStringList)));

        thread->start();
    }
}

void ApiHandler::pixivEmitViewDataDownloaded(QJsonObject userData, QJsonObject userAllData, QStringList imagesFromApi)
{
    engine->rootContext()->setContextProperty("userData", userData);
    engine->rootContext()->setContextProperty("userAllData", userAllData);
    engine->rootContext()->setContextProperty("imagesFromApi", imagesFromApi);
    pixivWorkInProggress = false;
    emit pixivViewDataDownloaded();
}



void ApiHandler::mangarockStartDownloading(const QString &oid)
{
    if (!mangarockWorkInProggress)
    {
        mangarockWorkInProggress = true;
        emit mangarockDownloadingStarted();

        QThread *thread = new QThread();
        MangarockApi *mApi = new MangarockApi();

        mApi->oid = oid.toStdString();
        mApi->basePath = "H:\\KawaiClient\\downloaded\\mangarock";
        mApi->logger = this->logger;

        mApi->moveToThread(thread);

        connect(thread, SIGNAL(started()), mApi, SLOT(downloadUser()));
        connect(mApi, SIGNAL(downloadingFinished()), thread, SLOT(quit()));

        connect(mApi, SIGNAL(downloadingFinished()), mApi, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(mApi, SIGNAL(downloadingFinished()), this, SLOT(mangarockEmitSignalDownloadingFinished()));

        thread->start();
    }
}

void ApiHandler::mangarockEmitSignalDownloadingFinished()
{
    mangarockWorkInProggress = false;
    emit mangarockDownloadingFinished();
}


void ApiHandler::exhentaiStartDownloading(const QString &url, const QString &mode)
{
    if (!exhentaiWorkInProggress)
    {
        exhentaiWorkInProggress = true;
        emit exhentaiDownloadingStarted();

        QThread *thread = new QThread();
        ExhentaiApi *eApi = new ExhentaiApi();

        eApi->url = url.toStdString();
        eApi->basePath = "H:\\KawaiClient\\downloaded\\exhentai";
        eApi->logger = this->logger;

        eApi->moveToThread(thread);

        if (mode == "download")
            connect(thread, SIGNAL(started()), eApi, SLOT(download()));
        else if (mode == "viewFrontPage")
            connect(thread, SIGNAL(started()), eApi, SLOT(viewFrontPage()));

        connect(eApi, SIGNAL(downloadingFinished()), thread, SLOT(quit()));

        connect(eApi, SIGNAL(downloadingFinished()), eApi, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(eApi, SIGNAL(downloadingFinished(QString, QJsonObject)), this, SLOT(exhentaiEmitSignalDownloadingFinished(QString, QJsonObject)));

        thread->start();
    }
}

void ApiHandler::exhentaiEmitSignalDownloadingFinished(QString mode, QJsonObject data)
{
    exhentaiWorkInProggress = false;
    if (mode == "void")
        emit exhentaiDownloadingFinished(mode, QJsonObject());
    else if (mode == "viewFrontPage")
        emit exhentaiDownloadingFinished(mode, data);
}
*/

void ApiHandler::universalStartDownloading(const QStringList &param, const QStringList &mode)
{
    emit universalDownloadingStarted(mode);
    QThread *thread = new QThread();
    PixivApi *pApi;
    MangarockApi *mApi;
    ExhentaiApi *eApi;
    MangadexApi *mdApi;

    if (mode[0] == "pixiv")
    {
        pApi = new PixivApi();
        pApi->userId = param[0].toStdString();
        pApi->basePath = "H:\\KawaiClient\\downloaded\\pixiv";
        pApi->logger = this->logger;

        pApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), pApi, SLOT(downloadUser()));
        connect(pApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(pApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), pApi, SLOT(deleteLater()));
        connect(pApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    else if (mode[0] == "mangarock")
    {
        mApi = new MangarockApi();
        mApi->oid = param[0].toStdString();
        mApi->basePath = "H:\\KawaiClient\\downloaded\\mangarock";
        mApi->logger = this->logger;

        mApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), mApi, SLOT(downloadUser()));
        connect(mApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(mApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), mApi, SLOT(deleteLater()));
        connect(mApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    else if (mode[0] == "exhentai")
    {
        eApi = new ExhentaiApi();
        eApi->url = param[0].toStdString();
        eApi->basePath = "H:\\KawaiClient\\downloaded\\exhentai";
        eApi->logger = this->logger;

        eApi->moveToThread(thread);
        if (mode[1] == "download")
            connect(thread, SIGNAL(started()), eApi, SLOT(download()));
        else if (mode[1] == "viewFrontPage")
            connect(thread, SIGNAL(started()), eApi, SLOT(viewFrontPage()));

        connect(eApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(eApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), eApi, SLOT(deleteLater()));
        connect(eApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    else if (mode[0] == "mangadex")
    {
        mdApi = new MangadexApi();
        mdApi->mangaId = param[0].toStdString();
        mdApi->enDownload = param[1].toStdString();
        mdApi->ruDownload = param[2].toStdString();
        mdApi->otherDownload = param[3].toStdString();
        mdApi->basePath = "H:\\KawaiClient\\downloaded\\mangadex";
        mdApi->logger = this->logger;

        mdApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), mdApi, SLOT(download()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), mdApi, SLOT(deleteLater()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void ApiHandler::universalEmitSignalDownloadingFinished(QStringList mode, QJsonObject data)
{
    if (mode[0] == "pixiv")
    {
        emit universalDownloadingFinished(mode, QJsonObject());
    }
    else if (mode[0] == "mangarock")
    {
        emit universalDownloadingFinished(mode, QJsonObject());
    }
    else if (mode[0] == "exhentai")
    {
        if (mode[1] == "void")
            emit universalDownloadingFinished(mode, QJsonObject());
        else if (mode[1] == "viewFrontPage")
            emit universalDownloadingFinished(mode, data);
    }
    else if (mode[0] == "mangadex")
    {
        emit universalDownloadingFinished(mode, QJsonObject());
    }
}
