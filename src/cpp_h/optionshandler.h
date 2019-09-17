#ifndef OPTIONSHANDLER_H
#define OPTIONSHANDLER_H

#include <QObject>
#include <QJsonObject>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QFileInfo>
#include <QVariant>

class OptionsHandler : public QObject
{
    Q_OBJECT
public:
    OptionsHandler();

private:
    void writeOnDrive();
    void setParam(QStringList hierarchyPath, QString param);
    QString getParam(QStringList hierarchyPath);

private:
    QJsonObject config;
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/config.json";
};

#endif // OPTIONSHANDLER_H
