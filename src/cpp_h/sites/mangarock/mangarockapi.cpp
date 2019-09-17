#include "mangarockapi.h"

MangarockApi::MangarockApi() { }

MangarockApi::~MangarockApi() { }

void MangarockApi::downloadUser()
{

    chunk = {
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0",
        "Accept-Encoding: gzip, deflate, br",
        "Connection: keep-alive",
        "Cache-Control: max-age=0",
    };
    std::string logType = "MangaRock";
    std::string logPath;

    CurlClass *cc = new CurlClass(chunk);
    object = downloadJson("https://api.mangarockhd.com/query/web401/info?oid=mrs-serie-" + oid, *cc);
    titleName = object.value("data").toObject().value("name").toString().toStdString();
    eraseForbiddenChars(titleName);
    halfPath = basePath + "\\[" + oid + "](" + titleName + ')';
    logPath = halfPath;
    logger->cppPerformLogging("Starting download manga with OID " + oid + '.', logType, logPath);
    writeJsonDataInFile(object, halfPath + "\\txt", "mangaInfo.txt");

    downloadAndWriteFile(object.value("data").toObject().value("thumbnail").toString().toStdString(), *cc, halfPath, "thumbnail.jpg");
    downloadAndWriteFile(object.value("data").toObject().value("cover").toString().toStdString(), *cc, halfPath, "cover.jpg");
    logger->cppPerformLogging("Info page thumbnail and cover downloaded.",logType, logPath);

    arrJ = object.value("data").toObject().value("artworks").toArray();
    for (int i = 0; i < arrJ.size(); i++)
    {
        downloadAndWriteFile(arrJ[i].toString().toStdString(), *cc, halfPath + "\\artworks", std::to_string(i) + ".jpg");
    }
    logger->cppPerformLogging("Artworks downloaded.",logType, logPath);

    arrJ = object.value("data").toObject().value("chapters").toArray();
    logging("Finded " + std::to_string(arrJ.size()) + " chapters.");
    for (int i = 0; i < arrJ.size(); i++)
    {
        logger->cppPerformLogging("Starting download " + std::to_string(i) + '/' + std::to_string(arrJ.size()) + " chapter.",logType, logPath);

        chapterOid = arrJ[i].toObject().value("oid").toString().toStdString();
        chapterName = arrJ[i].toObject().value("name").toString().toStdString();
        order = arrJ[i].toObject().value("order").toVariant().toInt();
        eraseForbiddenChars(chapterName);

        currUrl = "https://api.mangarockhd.com/query/web401/pages?oid=" + chapterOid;
        object = downloadJson(currUrl, *cc);
        std::string tmp = halfPath + "\\txt\\chs\\" + "[" + std::to_string(order) + "](" + chapterName + ").txt";
        writeJsonDataInFile(object, halfPath + "\\txt\\chs", "[" + std::to_string(order) + "](" + chapterName + ").txt");
        pageLinks = object.value("data").toArray();

        for (int j = 0; j < pageLinks.size(); j++)
        {
            currUrl = pageLinks[j].toString().toStdString();
            downloadAndWriteMri(pageLinks[j].toString().toStdString(), *cc, halfPath + "\\chs\\[" + std::to_string(order) + "](" + chapterName + ')', std::to_string(j) + ".webp");
            logger->cppPerformLogging("Page #" + std::to_string(j) + " in chapter " + std::to_string(i) + " downloaded.",logType, logPath);
        }
    }

    QStringList mode;
    mode.push_back("mangarock");
    mode.push_back("void");
    emit downloadingFinished(mode, QJsonObject());
}


void MangarockApi::downloadAndWriteMri(std::string url, CurlClass &cc, std::string directory, std::string fileName)
{ // https://developers.google.com/speed/webp/docs/riff_container#webp_file_header
    std::string bytes = cc.performing(url.c_str());

    std::string buffer;
    char first = bytes[0];
    if (first == 69)
    {
        buffer.resize(bytes.size() + 15);
        int size = bytes.size() + 7;
        buffer[0] = 82; // R
        buffer[1] = 73; // I
        buffer[2] = 70; // F
        buffer[3] = 70; // F
        buffer[4] = 255 & size;
        buffer[5] = size >> 8 & 255;
        buffer[6] = size >> 16 & 255;
        buffer[7] = size >> 24 & 255;
        buffer[8] = 87; // V
        buffer[9] = 69; // E
        buffer[10] = 66; // B
        buffer[11] = 80; // P
        buffer[12] = 86; // V
        buffer[13] = 80; // P
        buffer[14] = 56; // 8
        for (int i = 0; i < bytes.size(); i++)
        {
            buffer[i + 15] = 101 ^ bytes[i];
        }
    }

    writeFile(buffer, directory, fileName);
}

// https://api.mangarockhd.com/query/web401/info?oid=mrs-serie-254590
// https://api.mangarockhd.com/query/web401/pages?oid=mrs-chapter-254595
// https://api.mangarockhd.com/query/web401/info?oid=mrs-serie-10427
// https://api.mangarockhd.com/query/web401/pages?oid=mrs-chapter-100244065
// https://graphql.mangarock.io/graphql
// https://api.mangarockhd.com/query/web401/license?country=Australia&msid=71
// https://api.mangarockhd.com/query/web401/manga_detail?country=Russian
// https://api.mangarockhd.com/query/web401/rec_btrn?msid=71&oid=mrs-serie-254590
