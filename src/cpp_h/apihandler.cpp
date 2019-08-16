#include "apihandler.h"

ApiHandler::ApiHandler(){
    pixivWorkInProggress = false;
    mangarockWorkInProggress = false;
}

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
        pApi->logging = this->logging;

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
        pApi->logging = this->logging;

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



void ApiHandler::mangarockStartDownloading(const QString &userId)
{
    if (!mangarockWorkInProggress)
    {
        mangarockWorkInProggress = true;
        emit pixivDownloadingStarted();

        QThread *thread = new QThread();
        PixivApi *pApi = new PixivApi();

        pApi->userId = userId.toStdString();
        pApi->basePath = "H:\\KawaiClient\\downloaded\\pixiv";
        pApi->logging = this->logging;

        pApi->moveToThread(thread);

        connect(thread, SIGNAL(started()), pApi, SLOT(downloadUser()));
        connect(pApi, SIGNAL(downloadingFinished()), thread, SLOT(quit()));

        connect(pApi, SIGNAL(downloadingFinished()), pApi, SLOT(deleteLater()));
        connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

        connect(pApi, SIGNAL(downloadingFinished()), this, SLOT(pixivEmitSignalDownloadingFinished()));

        thread->start();
    }
}

void ApiHandler::mangarockEmitSignalDownloadingFinished()
{
    mangarockWorkInProggress = false;
    emit mangarockDownloadingFinished();
}
