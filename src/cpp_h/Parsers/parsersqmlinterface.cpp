#include "parsersqmlinterface.h"
#include "apihandler.h" // included here because of circular include issue

ParsersQmlInterface::ParsersQmlInterface() {}

void ParsersQmlInterface::apiHandlerStartDownloading(const QStringList &params, const QList<int> &mode)
{
    emit apiHandlerSignalDownloadingStarted(mode);
    ApiHandler::slotStartDownloding(params, mode);
}

void ParsersQmlInterface::emitParserClassDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryContent)
{
    emit parserClassDownloadingFinished(mode, data, binaryContent);
}