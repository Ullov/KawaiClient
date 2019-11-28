#ifndef CURLCLASS_H
#define CURLCLASS_H

#include <curl/curl.h>
#include <string>
#include <vector>
#include <QDir>
#include <QFile>

class CurlClass
{
public:
    CurlClass(std::vector<std::string> chunk);
    ~CurlClass();

    const char* url;
    static std::string buffer;
    QByteArray performing(const char* url);
    std::string postPerforming(const char* url, std::vector<std::string> &postData, std::vector<std::string> &postKeys);
    //static unsigned long long downloadedSize; // in bytes
    void setHeader(std::vector<std::string> chunk);
    //static std::string responseHeader;
    //std::string resHea;
    //std::string errString;

private:
    CURL *curlHandle;
    CURLcode res;
    static size_t writeMemoryCallback(char *data, size_t size, size_t nmemb, std::string *writerData);
    struct curl_slist *header;
    std::string cacert;
    std::string cacertPath;
    std::string fullCacertPath;
    //static size_t headerCallback(char *buffer, size_t size, size_t nitems, void *userdata);
};

#endif // CURLCLASS_H
