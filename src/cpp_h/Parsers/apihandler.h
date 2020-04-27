#ifndef APIHANDLER_H
#define APIHANDLER_H

#include "sites/pixivapi.h"
#include "sites/mangarockapi.h"
#include "sites/exhentaiapi.h"
#include "sites/mangadexapi.h"
#include "sites/vkapi.h"
#include "sites/mangairoapi.h"
#include "sites/youtubeapi.h"
#include "sites/twitterapi.h"
#include "sites/ninehentaiapi.h"
#include "sites/mangakakalotapi.h"
#include <QObject>
#include <QThread>
#include "../KTools/logging.h"
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "../KTools/optionshandler.h"
#include "sites/nhentaidotcomapi.h"

class ApiHandler : public QObject
{
    Q_OBJECT
public:
    ApiHandler();

    Logging *logger;
    //QQmlApplicationEngine *engine;
    OptionsHandler *options;

private:
    void startDownloading(const QStringList &params, const KEnums::ParserModes::ExHentai parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::Pixiv parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::MangaDex parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::VK parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::MangaIro parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::YouTube parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::Twitter parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::NineHentai parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::MangaKakalot parserMode);
    void startDownloading(const QStringList &params, const KEnums::ParserModes::NHentaiDotCom parserMode);

    template<typename T>
    void connectSlotsAndSignals(const QThread *thread, const T *apiClass);

public slots:
    void slotStartDownloding(const QStringList &params, const QList<int> &mode);

private slots:
    void slotDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryData);
    void slotDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType);

signals:
    void signalDownloadingStarted(const QList<int> mode);
    void signalDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryData);
    void signalDownloadStatus(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType);
};

#endif // APIHANDLER_H
