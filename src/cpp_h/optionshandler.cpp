#include "optionshandler.h"

OptionsHandler::OptionsHandler()
{
    QFileInfo checkFile(configPath);
    if (checkFile.exists() && checkFile.isFile())
    {
        QFile file(configPath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        rootProgramPath = file.readAll();
    }
    else
    {
        rootProgramPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation) + '\\';
        QFile file(configPath);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        file.write(rootProgramPath.toStdString().c_str(), rootProgramPath.size());
    }

    /*QFileInfo checkFil(rootProgramPath + "appConfigs.json");
    if (checkFil.exists() && checkFil.isFile())
    {
        QFile file(rootProgramPath + "appConfigs.json");
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString data = file.readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(data.toUtf8());
        appConfigs = jDoc.object();
    }
    else
    {
        QJsonObject first;
        QJsonObject tmp;
        tmp[""]
    }*/
}

void OptionsHandler::writeOnDrive()
{
    QFile file(rootProgramPath + "appConfigs.json");
    file.open(QIODevice::WriteOnly);
    QJsonDocument jDoc(appConfigs);
    file.write(jDoc.toJson());
    file.close();
}

void OptionsHandler::setRootProgramPath(QString path)
{
    rootProgramPath = path;
    QFile file(configPath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(rootProgramPath.toStdString().c_str(), rootProgramPath.size());
}

void OptionsHandler::emitRootProgramPath()
{
    emit sendRootProgramPath(rootProgramPath);
}

QString OptionsHandler::getRootProgramPath()
{
    return rootProgramPath;
}
