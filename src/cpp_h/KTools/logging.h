#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <QDateTime>
#include "nativefs.h"
#include "optionshandler.h"
#include "kenums.h"

class Logging : public QObject
{
    Q_OBJECT
public:
    Logging();

private:
    static QString logFileName;
    static QMap<KEnums::LogType, QString> logTypePath;
    static QMap<KEnums::LogType, QString> logTypeNames;

signals:
    void logMessage(const QString message);

public:
    static void writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type = KEnums::LogType::Custom);
    static void writeCustomLog(const QString &message, const QString &from, const KEnums::LogType &type, const QString &path, const QString &fileName);
    static void writeInfo(const QString &message, const QString &from);
    static void writeError(const QString &message, const QString &from);
    static void writeDebug(const QString &message, const QString &from);
};

#endif // LOGGING_H
