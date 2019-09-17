#include "optionshandler.h"

OptionsHandler::OptionsHandler()
{
    QFileInfo checkFile(configPath);
    if (checkFile.exists() && checkFile.isFile())
    {
        QFile file(configPath);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        QString data = file.readAll();
        QJsonDocument jDoc = QJsonDocument::fromJson(data.toUtf8());
        config = jDoc.object();
    }
    else
    {
        QStringList hierPath;
        hierPath.push_back("paths");
        hierPath.push_back("root");
        QString param = "C:\\KawaiClient\\";
        setParam(hierPath, param);
        hierPath[1] = "pixiv";
        param = "downloads\\pixiv";
        setParam(hierPath, param);
        hierPath[1] = "mangarock";
        param = "downloads\\mangarock";
        setParam(hierPath, param);
        hierPath[1] = "nhentai";
        param = "downloads\\nhentai";
        setParam(hierPath, param);
        hierPath[1] = "sysLog";
        param = "log";
        setParam(hierPath, param);
    }
    QStringList testList;
    testList.push_back("paths");
    testList.push_back("sysLog");
    QString test = getParam(testList);
    std::string nothing;
}

void OptionsHandler::setParam(QStringList hierarchyPath, QString param)
{
    int hier = hierarchyPath.size() - 1;
    QString lastFieldInHier = hierarchyPath[hierarchyPath.size() - 1];
    std::vector<QJsonObject> maybi;
    maybi.push_back(config);
    for (int i = 0; i < hier; i++)
    {
        maybi.push_back(maybi[i][hierarchyPath[i]].toObject());
    }
    maybi[maybi.size() - 1][lastFieldInHier] = param;
    for (int i = hier; i > 0; i--)
    {
        maybi[i - 1][hierarchyPath[i - 1]] = maybi[i];
        maybi.pop_back();
    }
    config = maybi[0];
    writeOnDrive();
}

void OptionsHandler::writeOnDrive()
{
    QFile file(configPath);
    file.open(QIODevice::WriteOnly);
    QJsonDocument jDoc(config);
    file.write(jDoc.toJson());
    file.close();
}

QString OptionsHandler::getParam(QStringList hierarchyPath)
{
    int hier = hierarchyPath.size() - 1;
    QString lastFieldInHier = hierarchyPath[hier];
    std::vector<QJsonObject> tmp;
    tmp.push_back(config);
    for (int i = 0; i < hier; i++)
    {
        tmp.push_back(tmp[i][hierarchyPath[i]].toObject());
    }
    QString target;
    if (tmp[tmp.size() - 1][lastFieldInHier].isDouble())
    {
        target = tmp[tmp.size() - 1][lastFieldInHier].toVariant().toString();
    }
    else
    {
        target = tmp[tmp.size() - 1][lastFieldInHier].toString();
    }
    return target;
}
