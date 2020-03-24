#include "optionshandler.h"

OptionsHandler::OptionsHandler()
{
    bool wtf = NativeFs::fileExist(configPath + configFile);
    if (wtf)
    {
        rootProgramPath = NativeFs::readFile<QString>(configPath, configFile, QIODevice::ReadOnly | QIODevice::Text);
    }
    else
    {
        rootProgramPath = configPath;
        NativeFs::writeFile(configPath.toUtf8(), configPath, configFile, QIODevice::WriteOnly | QIODevice::Text);
    }
    logRootPath = OptionsHandler::rootProgramPath + "/log/";

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
    NativeFs::writeFile(KawaiConverter::convert<QJsonObject, QByteArray>(appConfigs), rootProgramPath, "appConfigs.json");
}

void OptionsHandler::setRootProgramPath(QString path)
{
    rootProgramPath = path;
    NativeFs::writeFile(rootProgramPath.toUtf8(), configPath, configFile, QIODevice::WriteOnly | QIODevice::Text);
}

void OptionsHandler::emitRootProgramPath()
{
    emit sendRootProgramPath(rootProgramPath);
}

QString OptionsHandler::getRootProgramPath()
{
    return rootProgramPath;
}
