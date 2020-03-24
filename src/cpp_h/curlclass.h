#ifndef CURLCLASS_H
#define CURLCLASS_H

#include <curl/curl.h>
#include <string>
#include <vector>
#include <QDir>
#include <QFile>
#include <QObject>
#include <QElapsedTimer>
#include "KTools/nativefs.h"
#include "KTools/kenums.h"

class CurlClass : public QObject
{
    Q_OBJECT
public:
    CurlClass();
    ~CurlClass();

    const char* url;
    QByteArray performing(const char* url);
    void setHeader(QVector<QByteArray> chunk);

    KEnums::Parsers downloaderType;
private:
    CURLcode res;
    static size_t writeMemoryCallback(char *data, size_t size, size_t nmemb, std::string *writerData);
    static int XFerInfoFunctionCallback(void *p, double dlTotal, double dlNow, double ulTotal, double ulNow);
    struct curl_slist *header;
    static QString cacertPath;
    static QString cacertFileName;
    static QString fullCacertPath;
    static QString pathToCacertInQrc;

    struct ForProggress
    {
        CurlClass *th;
        QElapsedTimer timer;
        double lastDlTotal;
        double lastUlTotal;
        double lastDlNow;
        double lastUlNow;
    };

signals:
    void progressSignal(const QList<double> list, const qint64 millisecondsFromStart, const KEnums::Parsers downloaderType);
};

#endif // CURLCLASS_H
