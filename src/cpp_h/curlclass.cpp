#include "curlclass.h"


CurlClass::CurlClass()
{
    if (!NativeFs::fileExist(fullCacertPath))
        QFile::copy(pathToCacertInQrc, fullCacertPath);
    //OptionsHandler::rootProgramPath + "/Cookie/";
    gCurlHandle = curl_easy_init();
    handlesList["main"] = gCurlHandle;
    currCookieMode = KEnums::CurlSettings::CookieMode::Void;
    currHeaderMode = KEnums::CurlSettings::HeaderMode::Custom;
    currRequestType = KEnums::CurlSettings::RequestType::Get;
    currHttpVersion = KEnums::CurlSettings::HttpVersion::Http2;
    currRequestMode = KEnums::CurlSettings::RequestMode::New;
}

CurlClass::~CurlClass()
{
    if (errFileSetted)
        unsetErrFile();

    QMap<QString, CURL*>::iterator end = handlesList.end();
    for (QMap<QString, CURL*>::iterator i = handlesList.begin(); i != end; ++i)
    {
        curl_easy_cleanup(i.value());
    }
}

QByteArray CurlClass::performing(const char* url)
{
    ForProggress fp;

    //curl_global_init(CURL_GLOBAL_ALL);
    QByteArray buffer = "";
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
    //curl_global_cleanup();

    if (res != CURLE_OK)
    {
        return "Error in CURL";
    }
    else
    {
        return buffer;
    }
}

quint64 CurlClass::writeMemoryCallback(char *data, quint64 size, quint64 nmemb, QByteArray *writerData)
{
    if (writerData == NULL)
        return 0;
    writerData->append(data, size*nmemb);
    return size * nmemb;
}

void CurlClass::setHeader(QVector<QByteArray> chunk, const KEnums::CurlSettings::SetHeaderMode mode)
{
    /*if (mode == KEnums::CurlSettings::SetHeaderMode::New)
        headerData = QMap<QString, QString>();

    for (int i = 0; i < chunk.size(); i++)
    {
        QList<QByteArray> list = chunk[i].split(':');
        headerData[list[0].trimmed()] = list[1].trimmed();
    }
    generateHeader();*/
    header = NULL;
    for (qint64 i = 0; i < chunk.size(); i++)
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

QByteArray CurlClass::request(const QString &url)
{
    if (currRequestMode == KEnums::CurlSettings::RequestMode::Old)
    {
        return performing(url.toStdString().c_str());
    }
    QByteArray buffer;

    curl_easy_setopt(gCurlHandle, CURLOPT_URL, url.toStdString().c_str()); // specify url to get
    curl_easy_setopt(gCurlHandle, CURLOPT_WRITEDATA, &buffer);

    if (currRequestType == KEnums::CurlSettings::RequestType::Post)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_POSTFIELDS, currPostParam.toStdString().c_str());
        curl_easy_setopt(gCurlHandle, CURLOPT_POSTFIELDSIZE, currPostParam.size());
    }

    savedHeaderData.clear();

    res = curl_easy_perform(gCurlHandle);
    curl_easy_getinfo(gCurlHandle, CURLINFO_RESPONSE_CODE, &responseCode);

    if (res != CURLE_OK)
    {
        Logging::writeError("Error in request. URL: " + url, "CurlClass");
        return "Error in CURL";
    }
    else
    {
        return buffer;
    }
}

void CurlClass::restartSession()
{
    curl_easy_cleanup(gCurlHandle);
    gCurlHandle = curl_easy_init();
}

quint64 CurlClass::headerCallback(char *buffer, quint64 size, quint64 nitems, QByteArray *userdata)
{
    userdata->append(buffer, nitems * size);
    return nitems * size;
}

void CurlClass::setOptions()
{
    curl_easy_setopt(gCurlHandle, CURLOPT_WRITEFUNCTION, writeMemoryCallback); // send all data to this function
    curl_easy_setopt(gCurlHandle, CURLOPT_CAINFO,  fullCacertPath.toStdString().c_str());
    curl_easy_setopt(gCurlHandle, CURLOPT_PROXY_SSL_VERIFYHOST, 1);
    curl_easy_setopt(gCurlHandle, CURLOPT_PROXY_SSL_VERIFYPEER, 1);
    curl_easy_setopt(gCurlHandle, CURLOPT_ACCEPT_ENCODING, "gzip, deflate, br");
    curl_easy_setopt(gCurlHandle, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(gCurlHandle, CURLOPT_MAXREDIRS, 5L);
    curl_easy_setopt(gCurlHandle, CURLOPT_NOPROGRESS, 0);
    curl_easy_setopt(gCurlHandle, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0");

    if (currHttpVersion == KEnums::CurlSettings::HttpVersion::Http2)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2TLS);
    }

    /*
     * This if else construction choose which request type do
     */
    setRequestType(currRequestType);

    /*
     * This if else construction choose what to do with cookies
     */
    if (currCookieMode == KEnums::CurlSettings::CookieMode::GetAndKeep) // Get cookie in first request and use it in next requests
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_COOKIEJAR, (cookiePath + cookieFileName).toStdString().c_str());
        currCookieMode = KEnums::CurlSettings::CookieMode::Keep;
    }
    else if (currCookieMode == KEnums::CurlSettings::CookieMode::Keep) // Use cookie from file
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_COOKIEFILE, (cookiePath + cookieFileName).toStdString().c_str());
    }
    else if (currCookieMode == KEnums::CurlSettings::CookieMode::GetAllTimes) // Get new cookie in each request
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_COOKIEJAR, (cookiePath + cookieFileName).toStdString().c_str());
        curl_easy_setopt(gCurlHandle, CURLOPT_COOKIEFILE, (cookiePath + cookieFileName).toStdString().c_str());
    }
    else if (currCookieMode == KEnums::CurlSettings::CookieMode::Void) // Only starts cookie engine
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_COOKIEFILE, "");
    }


    /*
     * This if construction choose what to do with header
     */
    if (currHeaderMode == KEnums::CurlSettings::HeaderMode::Custom) // Sets header
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_HTTPHEADER, header);
    }

    /*
     * This if construction choose send progress data or not (on default emitProgress = false)
     */
    ForProggress fp;
    if (emitProgress)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_PROGRESSFUNCTION, XFerInfoFunctionCallback);
        curl_easy_setopt(gCurlHandle, CURLOPT_PROGRESSDATA, &fp);
        fp.th = this;
        fp.timer = QElapsedTimer();
        fp.timer.start();
    }

    /*
     * This if construction choose set automatically refer field or not (on default autoRefer = true)
     */
    if (autoRefer)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_AUTOREFERER, 1L);
    }

    /*
     * This if construction choose set automatically refer field or not (on default autoRefer = true)
     */
    //savedHeaderData.clear();
    if (saveHeader)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_HEADERDATA, &savedHeaderData);
        curl_easy_setopt(gCurlHandle, CURLOPT_HEADERFUNCTION, headerCallback);
    }

    if (verboseOutput)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_VERBOSE, 1L);
        curl_easy_setopt(gCurlHandle, CURLOPT_STDERR, stdErr);
    }
}

void CurlClass::setRequestType(KEnums::CurlSettings::RequestType requType)
{
    currRequestType = requType;
    if (requType == KEnums::CurlSettings::RequestType::Get)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_CUSTOMREQUEST, "GET");
        //curl_easy_setopt(gCurlHandle, CURLOPT_HTTPGET, 1L);
    }
    else if (requType == KEnums::CurlSettings::RequestType::Post)
    {
        curl_easy_setopt(gCurlHandle, CURLOPT_CUSTOMREQUEST, "POST");
        //curl_easy_setopt(gCurlHandle, CURLOPT_POST, 1L);
    }
}

void CurlClass::generateHeader()
{
    header = NULL;
    QMap<QString, QString>::iterator end = headerData.end();
    for (QMap<QString, QString>::iterator i = headerData.begin(); i != end; ++i)
    {
        header = curl_slist_append(header, (i.key() + ": " + i.value()).toStdString().c_str());
    }
}

void CurlClass::setHeader(const QMap<QString, QString> &chunk)
{
    QMap<QString, QString>::const_iterator end = chunk.end();
    for (QMap<QString, QString>::const_iterator i = chunk.begin(); i != end; ++i)
    {
        headerData[i.key()] = i.value();
    }
    headerData = chunk;
    generateHeader();
}

void CurlClass::setHeaderLine(const std::pair<QString, QString> &headerLine)
{
    headerData[headerLine.first] = headerLine.second;
    generateHeader();
}

void CurlClass::delHeaderLine(const QString &key)
{
    headerData.remove(key);
    generateHeader();
}

void CurlClass::setErrFile(const QString &path, const QString &fileName)
{
    stdErr = fopen((path + "/" + fileName).toStdString().c_str(), "w");
    errFileSetted = true;
    verboseOutput = true;
}

void CurlClass::unsetErrFile()
{
    if (errFileSetted)
    {
        fclose(stdErr);
        errFileSetted = false;
        verboseOutput = false;
    }
}

void CurlClass::addHandle(const QString &handleName)
{
    CURL* newHandle = curl_easy_init();
    handlesList[handleName] = newHandle;
}

void CurlClass::swichHandle(const QString &handleName)
{
    gCurlHandle = handlesList[handleName];
}
