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


class OptionsHandler : public QObject
{
    Q_OBJECT
public:

    OptionsHandler();
    QString getRootProgramPath();

    QJsonObject appConfigs;
    static QString configPath;
    static QString configFile;
    static QString rootProgramPath;
    static QString logRootPath;
    static QMap<KEnums::Parsers, QString> parsersWritePathes;
    static QMap<KEnums::Parsers, QString> parsersNames;

public slots:
    void setRootProgramPath(QString path);
    void emitRootProgramPath();

private:
    void writeOnDrive();


signals:
    void sendRootProgramPath(QString path);
};

#endif // OPTIONSHANDLER_H
