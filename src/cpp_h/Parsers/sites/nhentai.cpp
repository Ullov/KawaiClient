#include "nhentai.h"

#include "../../KTools/enums.h"

Parsers::Sites::NHentai::NHentai() { }

Parsers::Sites::NHentai::~NHentai() { }

void Parsers::Sites::NHentai::doWork()
{
    chunk = {
        "Host: nhentai.net",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Referer: https://nhentai.net/g/151605/16/",
        "Cookie: __cfduid=d14477bf615033f90580fab4df4fcca911556728664; _ga=GA1.2.2002516359.1556717876; csrftoken=NGFqSUfDTmevXqVPgYadX7ox1AZtL2FOjIDT2YDYoxVLTsMivFranJxSkMbgNtmX",
        "Upgrade-Insecure-Requests: 1",
        "Cache-Control: max-age=0"
    };

    //CurlClass *cc = new CurlClass(chunk);
//    cc->proxy = "49.231.16.226:8080";
//    halfPath = basePath;

    //downloadAndWriteFile("https://i.nhentai.net/galleries/885361/2.png", *cc, halfPath, "example.txt");

    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::NHentaiDotNet::Download));
}


// https://nhentai.net/g/151605/
// https://nhentai.net/g/151605/1/
// https://nhentai.net/api/gallery/151605
// https://nhentai.net/api/gallery/123/related
// https://nhentai.net/api/gallery/123
// https://nhentai.net/api/galleries/tagged?tag_id=123&page=2
// https://nhentai.net/api/galleries/all?page=3
// https://nhentai.net/api/galleries/search?query=naruto&page=2
