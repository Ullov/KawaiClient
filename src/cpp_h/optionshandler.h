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
    QString getRootProgramPath();

public slots:
    void setRootProgramPath(QString path);
    void emitRootProgramPath();

private:
    void writeOnDrive();

private:
    QJsonObject appConfigs;
    QString configPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + "/config.txt";
    QString rootProgramPath;

signals:
    void sendRootProgramPath(QString path);
};

#endif // OPTIONSHANDLER_H
