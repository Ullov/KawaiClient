#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "sites/pixiv/pixivapi.h"
#include "sites/mangarock/mangarockapi.h"
#include "sites/exhentai/exhentaiapi.h"
#include "sites/mangadex/mangadexapi.h"
#include "sites/vk/vkapi.h"
#include "sites/mangairo/mangairoapi.h"
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

signals:
    void universalDownloadingStarted(QStringList mode);
    void universalDownloadingFinished(QStringList mode, QJsonObject data);
};

#endif // APIHANDLER_H
