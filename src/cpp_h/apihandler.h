#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "sites/pixiv/pixivapi.h"
#include "sites/mangarock/mangarockapi.h"
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

private:
    bool pixivWorkInProggress;
    bool mangarockWorkInProggress;

public slots:
    void pixivStartDownloading(const QString &userId);
    void pixivViewUser(const QString &userId);

    void mangarockStartDownloading(const QString &oid);

private slots:
    void pixivEmitSignalDownloadingFinished();
    void pixivEmitViewDataDownloaded(QJsonObject userData, QJsonObject userAllData, QStringList imagesFromApi);

    void mangarockEmitSignalDownloadingFinished();

signals:
    void pixivDownloadingStarted();
    void pixivDownloadingFinished();
    void pixivViewDataDownloaded();

    void mangarockDownloadingStarted();
    void mangarockDownloadingFinished();
};

#endif // APIHANDLER_H
