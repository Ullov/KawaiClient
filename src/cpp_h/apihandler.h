#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "sites/pixiv/pixivapi.h"
#include "sites/mangarock/mangarockapi.h"
#include "sites/exhentai/exhentaiapi.h"
#include "sites/mangadex/mangadexapi.h"
#include "sites/vk/vkapi.h"
#include "sites/mangairo/mangairoapi.h"
#include "sites/youtube/youtubeapi.h"
#include "sites/twitter/twitterapi.h"
#include <QObject>
#include <QThread>
#include "logging.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "optionshandler.h"

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    ApiHandler();

    Logging *logger;
    QQmlApplicationEngine *engine;
    OptionsHandler *options;

public slots:
    void universalStartDownloading(const QStringList &param, const QStringList &mode);

private slots:
    void universalEmitSignalDownloadingFinished(QStringList mode, QJsonObject data);
    void downloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const QString downloaderType);

signals:
    void universalDownloadingStarted(QStringList mode);
    void universalDownloadingFinished(QStringList mode, QJsonObject data);
    void downloadStatusSignal(const QList<double> list, const qint64 millisecondsFromStart, const QString downloaderType);
};

#endif // APIHANDLER_H
