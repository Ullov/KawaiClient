#ifndef OPTIONSHANDLER_H
#define OPTIONSHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QFileInfo>
#include <QVariant>
#include "nativefs.h"
#include "kawaiconverter.h"
#include "kenums.h"
#include "logging.h"
#include "curlclass.h"


class OptionsHandler : public QObject
{
    Q_OBJECT
public:

    OptionsHandler();
    QString getRootProgramPath();

    static QJsonObject configsObj;
    static QString configPath;
    static QString configFile;
    static QString rootProgramPath;
    static QString logRootPath;
    static QMap<KEnums::Parsers, QString> parsersWritePathes;
    static QMap<KEnums::Parsers, QString> parsersNames;

    static void setParam(const QString &pathToParam, const QString &param); // wrapper for privateSetParam() for C++
    static QVariant getParam(const QString &pathToParam); // wrapper for privateGetParam() for C++

public slots:
    void setRootProgramPath(QString path);
    void emitRootProgramPath();
    void slotSetParam(const QString pathToParam, const QString param); // wrapper for privateSetParam() for QML
    void slotGetParam(const QString pathToParam); // wrapper for privateGetParam() for QML

private:
    static bool save(); // saving current settings in native file system
    static QJsonValue privateSetParam(QList<QString> pathToParam, QJsonValue currLevel, const QVariant param); // private method because for it need wrapper
    static QJsonValue privateGetParam(QList<QString> pathToParam, const QJsonValue &previousLevel); // private method because for it need wrapper


signals:
    void sendRootProgramPath(QString path);
    void signalParam(const QString pathToParam, const QJsonValue param); // sends setting parameter to QML
};

#endif // OPTIONSHANDLER_H
