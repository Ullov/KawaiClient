#ifndef OPTIONSHANDLER_H
#define OPTIONSHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QFileInfo>
#include <QVariant>
#include "KTools/nativefs.h"
#include "KTools/kawaiconverter.h"
#include "KTools/kenums.h"
#include "logging.h"
#include "curlclass.h"


class OptionsHandler : public QObject
{
    Q_OBJECT
public:

    OptionsHandler();
    QString getRootProgramPath();

    QJsonObject configsObj;
    static QString configPath;
    static QString configFile;
    static QString rootProgramPath;
    static QString logRootPath;
    static QMap<KEnums::Parsers, QString> parsersWritePathes;
    static QMap<KEnums::Parsers, QString> parsersNames;

public slots:
    void setRootProgramPath(QString path);
    void emitRootProgramPath();
    void setParam(const QString pathToParam);
    void getParam(const QString pathToParam);

private:
    //void writeOnDrive();


signals:
    void sendRootProgramPath(QString path);
    void signalParam(const QString pathToParam, const QString param);
};

#endif // OPTIONSHANDLER_H
