#include "logging.h"

KTools::Log::Log() {}

void KTools::Log::writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type)
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz");
    QString dt = '[' + from + ']' + dateTime + ' ' + message + '\n';
    NativeFs::writeFile(dt.toUtf8(), OptionsHandler::logRootPath + logTypePath[type], logFileName, QIODevice::Append | QIODevice::WriteOnly);
}

void KTools::Log::writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type, const QString &path, const QString &fileName)
{
    QString dateTime = QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss:zzz");
    QString dt = '[' + logTypeNames[type] + "][" + from + ']' + dateTime + ' ' + message + '\n';
    NativeFs::writeFile(dt.toUtf8(), path, fileName, QIODevice::Append | QIODevice::WriteOnly);
}

void KTools::Log::writeInfo(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Info);
}

void KTools::Log::writeError(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Error);
}

void KTools::Log::writeDebug(const QString &message, const QString &from)
{
    writeCustomLog(message, from, KEnums::LogType::Debug);
}
