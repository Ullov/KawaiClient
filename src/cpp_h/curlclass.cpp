#include "curlclass.h"

CurlClass::CurlClass(std::vector<std::string> chunk)
{
    header = NULL;
    for (int i = 0; i < chunk.size(); i++)
    {
        header = curl_slist_append(header, chunk[i].c_str());
    }
    cacertPath = QDir::temp().path().toStdString() + "/KawaiClient";

    QDir dir = QDir(cacertPath.c_str());
    bool qexi = dir.exists();
    if (!qexi)
    {
        qexi = dir.mkpath(".");
    }
    fullCacertPath = cacertPath + "/cacert.pem";
    QFile::copy(":/resources/other/cacert.pem", fullCacertPath.c_str());
}

CurlClass::~CurlClass() { }

std::string CurlClass::performing(const char* url)
{
    curl_global_init(CURL_GLOBAL_ALL);
    std::string buffer = "";
    //std::string resHea = "";
    curlHandle = curl_easy_init(); // init curl session

    curl_easy_setopt(curlHandle, CURLOPT_URL, url); // specifu url to get
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeMemoryCallback); // send all data to this function
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curlHandle, CURLOPT_CAINFO,  fullCacertPath.c_str()/*cacert.c_str()*//*"W:\\data\\programs\\sources\\cacert.pem"*/);
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate, gzip");
    curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_MAXREDIRS, 5L);
    //curl_easy_setopt(curlHandle, CURLOPT_HEADER, 1L);
    //curl_easy_setopt(curlHandle, CURLOPT_HEADERFUNCTION, headerCallback);
    //curl_easy_setopt(curlHandle, CURLOPT_HEADERDATA, &resHea);
    //curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 1L);
    //curl_easy_setopt(curlHandle, CURLOPT_STDERR, &errString);

    res = curl_easy_perform(curlHandle);

    curl_easy_cleanup(curlHandle);
    curl_global_cleanup();

    if (res != CURLE_OK)
    {
        return "Error in CURL";
    }
    else
    {
        return buffer;
    }
}

size_t CurlClass::writeMemoryCallback(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (writerData == NULL)
        return 0;
    writerData->append(data, size*nmemb);

    //downloadedSize = size * nmemb;
    return size * nmemb;
}

/*size_t CurlClass::headerCallback(char *buffer, size_t size, size_t nitems, void *userdata)
{
    return size * nitems;
}*/

std::string CurlClass::postPerforming(const char* url, std::vector<std::string> &postData, std::vector<std::string> &postKeys)
{
    std::string postFields = "";
    for (int i = 0; i < postKeys.size(); i++)
    {
        postFields = postKeys[i] + '=' + postData[i] + '&';
    }
    postFields.pop_back();

    curl_global_init(CURL_GLOBAL_ALL);
    std::string buffer = "";
    curlHandle = curl_easy_init(); // init curl session

    curl_easy_setopt(curlHandle, CURLOPT_URL, url); // specifu url to get
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeMemoryCallback); // send all data to this function
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curlHandle, CURLOPT_CAINFO, "W:\\data\\programs\\sources\\cacert.pem");
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate, gzip");
    curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, postFields.c_str());

    res = curl_easy_perform(curlHandle);

    curl_easy_cleanup(curlHandle);
    curl_global_cleanup();

    if (res != CURLE_OK)
    {
        return "";
    }
    else
    {
        return buffer;
    }
}

void CurlClass::setHeader(std::vector<std::string> chunk)
{
    header = NULL;
    for (int i = 0; i < chunk.size(); i++)
    {
        header = curl_slist_append(header, chunk[i].c_str());
    }
}
