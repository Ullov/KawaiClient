#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <string>
#include <QDir>
#include <QDataStream>
#include <QVariant>

class Logging : public QObject
{
    Q_OBJECT
public:
    Logging();

    std::string filePath;
    std::string systemLogPath;
    void cppPerformLogging(std::string message, std::string &type, std::string &path);

public slots:
    void performLogging(const QString &message, const QString &type);
    void performDelayedLogging(const QString &message, const QString &type);
    void flushDelayedMessages();


private:
    std::string delayedMessagesBuffer;

signals:
    void logMessage(const QString &message);
};

#endif // LOGGING_H
