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

private:
    void startDownloading(const QStringList &params, const KEnums::ParserModes::ExHentai parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::Pixiv parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::MangaDex parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::VK parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::MangaIro parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::YouTube parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::Twitter parserMode);

    template<typename T>
    void connectSlotsAndSignals(const QThread *thread, const T *apiClass);

public slots:
    void slotStartDownloding(const QStringList &params, const QList<int> &mode);

private slots:
    void slotDownloadingFinished(const QList<int> mode, const QJsonObject data);
    void slotDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType);

signals:
    void signalDownloadingStarted(const QList<int> mode);
    void signalDownloadingFinished(const QList<int> mode, const QJsonObject data);
    void signalDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType);
};

#endif // APIHANDLER_H
