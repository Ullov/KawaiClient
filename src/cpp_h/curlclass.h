#ifndef CURLCLASS_H
#define CURLCLASS_H

#include <curl/curl.h>
#include <string>
#include <vector>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QElapsedTimer>
#include "logging.h"

class CurlClass : public QObject
{
    Q_OBJECT
public:
    CurlClass();
    CurlClass(std::vector<std::string> chunk);
    ~CurlClass();

    const char* url;
    static std::string buffer;
    QByteArray performing(const char* url);
    void setHeader(std::vector<std::string> chunk);

    Logging *log;
    QString downloaderType;
private:
    CURL *curlHandle;
    CURLcode res;
    static size_t writeMemoryCallback(char *data, size_t size, size_t nmemb, std::string *writerData);
    static int XFerInfoFunctionCallback(void *p, double dlTotal, double dlNow, double ulTotal, double ulNow);
    struct curl_slist *header;
    std::string cacert;
    std::string cacertPath;
    std::string fullCacertPath;

    struct ForProggress
    {
        CurlClass *th;
        QElapsedTimer *timer;
        double lastDlTotal;
        double lastUlTotal;
        double lastDlNow;
        double lastUlNow;
    };

signals:
    void progressSignal(const QList<double> list, const qint64 millisecondsFromStart, const QString downloaderType);
};

#endif // CURLCLASS_H
