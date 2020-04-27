#ifndef KTOOLS_LOG_H
#define KTOOLS_LOG_H

#include <QDateTime>
#include "nativefs.h"
#include "optionshandler.h"
#include "kenums.h"

namespace KTools
{
    class Log
    {
    public:
        Log();

    private:
        static QString logFileName;
        static QMap<KEnums::LogType, QString> logTypePath;
        static QMap<KEnums::LogType, QString> logTypeNames;

    public:
        static void writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type = KEnums::LogType::Custom);
        static void writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type, const QString &path, const QString &fileName);
        static void writeInfo(const QString &message, const QString &from);
        static void writeError(const QString &message, const QString &from);
        static void writeDebug(const QString &message, const QString &from);
    };
}

#endif // KTOOLS_LOG_H
