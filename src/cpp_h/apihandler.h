#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "sites/pixiv/pixivapi.h"
#include "sites/mangarock/mangarockapi.h"
#include "sites/exhentai/exhentaiapi.h"
#include "sites/mangadex/mangadexapi.h"
#include <QObject>
#include <QThread>
#include "logging.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    ApiHandler();

    Logging *logger;
    QQmlApplicationEngine *engine;

//private:
    //bool pixivWorkInProggress;
    //bool mangarockWorkInProggress;
    //bool exhentaiWorkInProggress;

public slots:
    /*void pixivStartDownloading(const QString &userId);
    void pixivViewUser(const QString &userId);

    void mangarockStartDownloading(const QString &oid);

    void exhentaiStartDownloading(const QString &url, const QString &mode = "download");*/

    void universalStartDownloading(const QStringList &param, const QStringList &mode);

private slots:
    //void pixivEmitSignalDownloadingFinished();
    //void pixivEmitViewDataDownloaded(QJsonObject userData, QJsonObject userAllData, QStringList imagesFromApi);

    //void mangarockEmitSignalDownloadingFinished();

    //void exhentaiEmitSignalDownloadingFinished(QString mode, QJsonObject data);

    void universalEmitSignalDownloadingFinished(QStringList mode, QJsonObject data);

signals:
    //void pixivDownloadingStarted();
    //void pixivDownloadingFinished();
    //void pixivViewDataDownloaded();

    //void mangarockDownloadingStarted();
    //void mangarockDownloadingFinished();

    //void exhentaiDownloadingStarted();
    //void exhentaiDownloadingFinished(QString mode, QJsonObject data);

    void universalDownloadingStarted(QStringList mode);
    void universalDownloadingFinished(QStringList mode, QJsonObject data);
};

#endif // APIHANDLER_H
