#include "logging.h"

Logging::Logging() {}

void Logging::writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type)
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz");
    QString dt = '[' + from + ']' + dateTime + ' ' + message + '\n';
    NativeFs::writeFile(dt.toUtf8(), OptionsHandler::logRootPath + logTypePath[type], logFileName, QIODevice::Append | QIODevice::WriteOnly);
}

void Logging::writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type, const QString &path, const QString &fileName)
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz");
    QString dt = '[' + logTypeNames[type] + "][" + from + ']' + dateTime + ' ' + message + '\n';
    NativeFs::writeFile(dt.toUtf8(), path, fileName, QIODevice::Append | QIODevice::WriteOnly);
}

void Logging::writeInfo(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Info);
}

void Logging::writeError(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Error);
}

void Logging::writeDebug(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Debug);
}
