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
    CurlClass::cookiePath = OptionsHandler::rootProgramPath + "/Cookie/";


    if (!NativeFs::fileExist(rootProgramPath + "/Settings/configs.json"))
    {
        NativeFs::copyFile(":/resources/sampleFiles/configs.json", rootProgramPath + "/Settings", "configs.json");
    }
    QString fileContent = NativeFs::readFile<QString>(rootProgramPath + "/Settings", "configs.json");
    configsObj = KawaiConverter::convert<QString, QJsonObject>(fileContent);
}

bool OptionsHandler::save()
{
    return NativeFs::writeFile(KawaiConverter::convert<QJsonObject, QByteArray>(configsObj), rootProgramPath, "configs.json");
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

void OptionsHandler::slotSetParam(const QString pathToParam, const QString param)
{
    QList<QString> list = pathToParam.split("/", QString::SplitBehavior::SkipEmptyParts);
    QString name = list[0];
    list.pop_front();
    QJsonValue jsVal = configsObj[name];
    configsObj[name] = privateSetParam(list, jsVal, param);
    save();
}

void OptionsHandler::slotGetParam(const QString pathToParam)
{
    QList<QString> list = pathToParam.split("/", QString::SplitBehavior::SkipEmptyParts);
    QString name = list[0];
    list.pop_front();
    QJsonValue jsVal = configsObj[name];
    emit signalParam(pathToParam, privateGetParam(list, jsVal));
}

QJsonValue OptionsHandler::privateSetParam(QList<QString> pathToParam, QJsonValue currLevel, const QVariant param)
{
    QString name = pathToParam[0];
    pathToParam.pop_front();
    QJsonValue::Type jsValType = currLevel.type();
    if (jsValType == QJsonValue::Type::Undefined)
    {
        Logging::writeError("Attempt access to non existent parameter. name: " + name, "OptionsHandler::setParam()");
        return QJsonValue();
    }
    if (pathToParam.size() > 1)
    {
        if (jsValType == QJsonValue::Type::Array)
        {
            QJsonArray jsVal = currLevel.toArray();
            QJsonValueRef tmp = jsVal[name.toInt()];
            jsVal[name.toInt()] = privateSetParam(pathToParam, tmp, param);
            return jsVal;
        }
        else if (jsValType == QJsonValue::Type::Object)
        {
            QJsonObject jsVal = currLevel.toObject();
            QJsonValueRef tmp = jsVal[name];
            jsVal[name] = privateSetParam(pathToParam, tmp, param);
            return jsVal;
        }
        else
        {
            Logging::writeError("Wrong type. jsValType: " + static_cast<QString>(jsValType) + ", name: " + name, "OptionsHandler::setParam");
        }
    }
    else
    {
        if (jsValType != QJsonValue::Type::Array)
        {
            QJsonObject jsVal = currLevel.toObject();
            jsVal[name] = QJsonValue::fromVariant(param);
            return jsVal;
        }
        else if (jsValType == QJsonValue::Type::Array)
        {
            QJsonArray jsVal = currLevel.toArray();
            jsVal[name.toInt()] = QJsonValue::fromVariant(param);
            return jsVal;
        }
    }
    Logging::writeError("Something went wrong. name: " + name, "OptionsHandler::privateSetParam()");
    return QJsonValue();
}

QJsonValue OptionsHandler::privateGetParam(QList<QString> pathToParam, const QJsonValue &previousLevel)
{
    QString name = pathToParam[0];
    pathToParam.pop_front();
    QJsonValue::Type jsValType = previousLevel.type();
    if (jsValType == QJsonValue::Type::Undefined)
    {
        Logging::writeError("Attempt access to non existent parameter. name: " + name, "OptionsHandler::getParam()");
        return QJsonValue();
    }

    if (pathToParam.size() > 1)
    {
        if (jsValType == QJsonValue::Type::Array)
        {
            QJsonArray jsVal = previousLevel.toArray();
            QJsonValueRef tmp = jsVal[name.toInt()];
            return privateGetParam(pathToParam, tmp);
        }
        else if (jsValType == QJsonValue::Type::Object)
        {
            QJsonObject jsVal = previousLevel.toObject();
            QJsonValueRef tmp = jsVal[name];
            return privateGetParam(pathToParam, tmp);
        }
        else
        {
            Logging::writeError("Wrong type. jsValType: " + static_cast<QString>(jsValType) + ", name: " + name, "OptionsHandler::getParam");
            return QJsonValue();
        }
    }
    else
    {
        if (jsValType != QJsonValue::Type::Array)
        {
            QJsonObject jsVal = previousLevel.toObject();
            return jsVal[name];
        }
        else if (jsValType == QJsonValue::Type::Array)
        {
            QJsonArray jsVal = previousLevel.toArray();
            return jsVal[name.toInt()];
        }
    }
    Logging::writeError("Something went wrong. name: " + name, "OptionsHandler::privateGetParam()");
    return QJsonValue();
}

void OptionsHandler::setParam(const QString &pathToParam, const QString &param)
{
    QList<QString> list = pathToParam.split("/", QString::SplitBehavior::SkipEmptyParts);
    QString name = list[0];
    list.pop_front();
    QJsonValueRef jsVal = configsObj[name];
    configsObj[name] = privateSetParam(list, jsVal, param);
    save();
}

QVariant OptionsHandler::getParam(const QString &pathToParam)
{
    QList<QString> list = pathToParam.split("/", QString::SplitBehavior::SkipEmptyParts);
    QString name = list[0];
    list.pop_front();
    QJsonValue jsVal = configsObj[name];
    return privateGetParam(list, jsVal);
}
