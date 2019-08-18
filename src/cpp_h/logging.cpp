#include "logging.h"

Logging::Logging()
{
    delayedMessagesBuffer.erase();
    filePath = QDir::currentPath().toStdString();
    systemLogPath = "H:\\KawaiClient\\sysLog";
}

void Logging::performLogging(const QString &message, const QString &type)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    dt = '[' + type.toStdString() + ']' + dt + ' ' + message.toStdString() + '\n';

    /*std::string tmp = dt;
    tmp.pop_back();
    QString forSlot = tmp.c_str();
    emit logMessage(forSlot);*/

    QDir dir = QDir(systemLogPath.c_str());
    bool pathExist = dir.exists();
    if (!pathExist)
    {
        dir.mkpath(".");
    }

    QFile file(dir.path() + "\\log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.writeRawData(dt.c_str(), dt.length());
    }
    else
    {
        file.close();
    }
    file.close();
}

void Logging::performDelayedLogging(const QString &message, QString const &type)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    dt = '[' + type.toStdString() + ']' + dt + ' ' + message.toStdString() + '\n';

    /*std::string tmp = dt;
    tmp.pop_back();
    QString forSlot = tmp.c_str();
    emit logMessage(forSlot);*/

    delayedMessagesBuffer += dt;
}

void Logging::flushDelayedMessages()
{
    QDir dir = QDir(filePath.c_str());
    bool pathExist = dir.exists();
    if (!pathExist)
    {
        dir.mkpath(".");
    }

    QFile file(dir.path() + "\\log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.writeRawData(delayedMessagesBuffer.c_str(), delayedMessagesBuffer.length());
        delayedMessagesBuffer.erase();
    }
    else
    {
        delayedMessagesBuffer = "[Error] Last delayed messages not been flushed.";
    }
    file.close();
}

void Logging::cppPerformLogging(std::string message, std::string &type, std::string &path)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    dt = '[' + type + ']' + dt + ' ' + message + '\n';

    /*std::string tmp = dt;
    tmp.pop_back();
    QString forSlot = tmp.c_str();
    emit logMessage(forSlot);*/

    QDir dir = QDir(path.c_str());
    bool pathExist = dir.exists();
    if (!pathExist)
    {
        dir.mkpath(".");
    }

    QFile file(dir.path() + "\\log.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QDataStream stream(&file);
        stream.writeRawData(dt.c_str(), dt.length());
    }
    else
    {
        file.close();
    }
    file.close();
}
