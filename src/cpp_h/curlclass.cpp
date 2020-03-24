#include "curlclass.h"

CurlClass::CurlClass()
{
    if (!NativeFs::fileExist(fullCacertPath))
        QFile::copy(pathToCacertInQrc, fullCacertPath);

    //log = new Logging();
}

CurlClass::~CurlClass()
{
    //delete log;
}

QByteArray CurlClass::performing(const char* url)
{
    ForProggress fp;

    curl_global_init(CURL_GLOBAL_ALL);
    std::string buffer = "";
    CURL *curlHandle = curl_easy_init(); // init curl session

    curl_easy_setopt(curlHandle, CURLOPT_URL, url); // specifu url to get
    curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, writeMemoryCallback); // send all data to this function
    curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, header);
    curl_easy_setopt(curlHandle, CURLOPT_CAINFO,  fullCacertPath.toStdString().c_str());
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYHOST, 1);
    curl_easy_setopt(curlHandle, CURLOPT_PROXY_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate, gzip");
    curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curlHandle, CURLOPT_MAXREDIRS, 5L);
    curl_easy_setopt(curlHandle, CURLOPT_PROGRESSFUNCTION, XFerInfoFunctionCallback);
    curl_easy_setopt(curlHandle, CURLOPT_PROGRESSDATA, &fp);
    curl_easy_setopt(curlHandle, CURLOPT_NOPROGRESS, 0);

    fp.th = this;
    fp.timer = QElapsedTimer();
    fp.timer.start();
    res = curl_easy_perform(curlHandle);

    curl_easy_cleanup(curlHandle);
    curl_global_cleanup();

    if (res != CURLE_OK)
    {
        return "Error in CURL";
    }
    else
    {
        return QByteArray::fromStdString(buffer);
    }
}

size_t CurlClass::writeMemoryCallback(char *data, size_t size, size_t nmemb, std::string *writerData)
{
    if (writerData == NULL)
        return 0;
    writerData->append(data, size*nmemb);
    return size * nmemb;
}

void CurlClass::setHeader(QVector<QByteArray> chunk)
{
    header = NULL;
    for (quint64 i = 0; i < chunk.size(); i++)
    {
        header = curl_slist_append(header, chunk[i]);
    }
}

int CurlClass::XFerInfoFunctionCallback(void *p, double dlTotal, double dlNow, double ulTotal, double ulNow)
{ // all here in bytes
    ForProggress *fp = static_cast<ForProggress*>(p);
    if (fp->lastDlNow != dlNow || fp->lastDlTotal != dlTotal || fp->lastUlTotal != ulTotal || fp->lastUlNow != ulNow)
    {
        QList<double> list;
        list.append(dlNow);
        list.append(dlTotal);
        list.append(ulNow);
        list.append(ulTotal);
        emit fp->th->progressSignal(list, fp->timer.elapsed(), fp->th->downloaderType);
        fp->lastDlNow = dlNow;
        fp->lastDlTotal = dlTotal;
        fp->lastUlTotal = ulTotal;
        fp->lastUlNow = ulNow;
    }
    return CURLE_OK;
}
