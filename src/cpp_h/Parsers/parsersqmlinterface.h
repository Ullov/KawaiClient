#ifndef PARSERSQMLINTERFACE_H
#define PARSERSQMLINTERFACE_H

#include <QObject>
#include <QJsonObject>


class ParsersQmlInterface : public QObject
{
    Q_OBJECT
public:
    ParsersQmlInterface();

    static ParsersQmlInterface obj;
    void emitParserClassDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryContent);

public slots:
    void apiHandlerStartDownloading(const QStringList &params, const QList<int> &mode);

signals:
    void parserClassDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryContent);
    void apiHandlerSignalDownloadingStarted(const QList<int> mode);
    void apiHandlerSignalDownloadingFinished(const QList<int> mode, const QJsonObject data, const QVector<QByteArray> binaryData);
};

#endif // PARSERSQMLINTERFACE_H
