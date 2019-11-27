#include "apihandler.h"

ApiHandler::ApiHandler() {}

void ApiHandler::universalStartDownloading(const QStringList &param, const QStringList &mode)
{
    emit universalDownloadingStarted(mode);
    std::string rootPath = options->getRootProgramPath().toStdString();
    QThread *thread = new QThread();
    PixivApi *pApi;
    MangarockApi *mApi;
    ExhentaiApi *eApi;
    MangadexApi *mdApi;
    VkApi *vApi;
    MangairoApi *maApi;

    if (mode[0] == "pixiv")
    {
        pApi = new PixivApi();
        pApi->userId = param[0].toStdString();
        pApi->basePath = rootPath + "\\downloaded\\pixiv";
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
        mApi->basePath = rootPath + "\\downloaded\\mangarock";
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
        eApi->basePath = rootPath + "\\downloaded\\exhentai";
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
        mdApi->basePath = rootPath + "\\downloaded\\mangadex";
        mdApi->logger = this->logger;

        mdApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), mdApi, SLOT(download()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), mdApi, SLOT(deleteLater()));
        connect(mdApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    else if (mode[0] == "vk")
    {
        vApi = new VkApi();
        vApi->postUrl = param[0].toStdString();
        vApi->basePath = rootPath + "\\downloaded\\vk";
        vApi->logger = this->logger;

        vApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), vApi, SLOT(downloadPost()));
        connect(vApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(vApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), vApi, SLOT(deleteLater()));
        connect(vApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    else if (mode[0] == "mangairo")
    {
        maApi = new MangairoApi();
        maApi->mangaId = param[0].toStdString();
        maApi->basePath = rootPath + "\\downloaded\\MangaIro";
        maApi->logger = this->logger;

        maApi->moveToThread(thread);
        connect(thread, SIGNAL(started()), maApi, SLOT(download()));
        connect(maApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), thread, SLOT(quit()));
        connect(maApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), maApi, SLOT(deleteLater()));
        connect(maApi, SIGNAL(downloadingFinished(QStringList, QJsonObject)), this, SLOT(universalEmitSignalDownloadingFinished(QStringList, QJsonObject)));
    }
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void ApiHandler::universalEmitSignalDownloadingFinished(QStringList mode, QJsonObject data)
{
    if (mode[0] == "pixiv")
        emit universalDownloadingFinished(mode, QJsonObject());
    else if (mode[0] == "mangarock")
        emit universalDownloadingFinished(mode, QJsonObject());
    else if (mode[0] == "exhentai")
    {
        if (mode[1] == "void")
            emit universalDownloadingFinished(mode, QJsonObject());
        else if (mode[1] == "viewFrontPage")
            emit universalDownloadingFinished(mode, data);
    }
    else if (mode[0] == "mangadex")
        emit universalDownloadingFinished(mode, QJsonObject());
    else if (mode[0] == "vk")
        emit universalDownloadingFinished(mode, QJsonObject());
    else if (mode[0] == "mangairo")
        emit universalDownloadingFinished(mode, QJsonObject());
}
