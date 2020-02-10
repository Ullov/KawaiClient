#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <string>
#include <QDir>
#include <QDataStream>
#include <QVariant>
#include <QDate>
#include <QTime>
#include <QElapsedTimer>
#include <QTimer>

class Logging : public QObject
{
    Q_OBJECT
public:
    Logging();

    std::string filePath;
    std::string systemLogPath;
    void cppPerformLogging(const QString &message, const QString &type, const QString &path);
    void startTimer();

    int currentItem;
    int allItems;
    int allTime;
    int previousTime;
    quint64 fileSize;
    QTimer *timer;
    QElapsedTimer *eTimer;

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
