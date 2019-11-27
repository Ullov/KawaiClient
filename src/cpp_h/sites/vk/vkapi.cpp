#include "vkapi.h"

VkApi::VkApi() {}

void VkApi::downloadPost()
{
    chunk = {
        "Host: vk.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:70.0) Gecko/20100101 Firefox/70.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://vk.com/bookmarks",
        "Connection: keep-alive",
        "Cookie: remixrefkey=1810e9d5c75c140a64; remixflash=0.0.0; remixscreen_depth=24; remixdt=-10800; remixab=1; remixseenads=0; remixfeed=*.*.*.*.*.*.ps%2Ctp.photos%2Cvideos%2Cfriends%2Cgroups%2Cpodcasts%2Ckrsk2019; remixusid=OThlODJkYWI0MzdmNDBhY2Y2YTAyYTJj; remixstid=1782892298_b06dee564c8becaa47; remixlang=20; remixsid=34e47df86bf4d8fe2ec156d9fed8c03f670910146a8501c0b73979bb92a67; remixua=29%7C-1%7C277%7C1824161884; remixmdevice=1680/1050/1/!!-!!!!; remixscreen_orient=1; remixvoice=0; remixgp=6ce88c32eb383bb03c2c786b26128d75; tmr_detect=1%7C1573908207829; remixcurr_audio=236071586_456242024; remixsts=%7B%22data%22%3A%5B%5B1573908210%2C%22time_spent%22%2C%7B%22wall%22%3A%7B%22full%22%3A3001%2C%22last%22%3A1573908210009%2C%22options%22%3A%7B%7D%7D%2C%22public%22%3A%7B%22full%22%3A0%2C%22last%22%3A1573908207058%2C%22options%22%3A%7B%7D%7D%2C%22audio%22%3A%7B%22full%22%3A0%2C%22last%22%3A1573908208380%2C%22options%22%3A%7B%7D%7D%2C%22bookmarks%22%3A%7B%22full%22%3A0%2C%22last%22%3A1573908209876%2C%22options%22%3A%7B%7D%7D%7D%5D%2C%5B1573908212%2C%22app_use_time%22%2C%22wall%7C1573908206902%7C1573908206902%7C1573908212083%7C4473%7C0%22%5D%5D%2C%22uniqueId%22%3A958277578%7D",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    CurlClass *cc = new CurlClass(chunk);
    //std::string pattern;
    std::vector<std::string> regexResult;
    std::vector<std::string> all;
    std::vector<std::string> part;
    currUrl = "https://vk.com/wall-34215577_1200355?hash=6f6a005dc253d8e7e0";
    std::string data = cc->performing(currUrl.c_str());
    //pattern = "=*({(\")(.)+})+";
    //findMatchChars(data, pattern, regexResult);

    pattern = "&#(\\d+);";
    findMatchChars(data, pattern, regexResult);

    QRegularExpression re(pattern.c_str());
    QRegularExpressionMatchIterator i = re.globalMatch(data.c_str());
    while (i.hasNext())
    {
        QRegularExpressionMatch match = i.next();
        QString word = match.captured(1);
        part.push_back(word.toStdString());
        all.push_back(match.captured(0).toStdString());
    }
    for (int i = 0; i < part.size(); i++)
    {
        //unsigned short tmp = static_cast<unsigned short>(std::stoi(part[i]));
        //QString tmp2 = QString::fromUtf16(&tmp);
        //tmp2.resize(1);
        //part[i] = tmp2.toStdString();
        part[i] = intToUtf8(std::stoi(part[i]));
        //std::u16string source = QString::fromUtf16(&tmp).toStdU16String();
        //source.resize(1);
        //std::wstring_convert<std::codecvt_utf8_utf16<char16_t>,char16_t> convert;
        //part[i] = convert.to_bytes(source);

    }
    replace(data, all, part);
    //textWithWindows1251ToUtf8(data);


    writeFile(data, "E:\\Win7アプリ\\downloads", "test.txt");

    std::string someth;
}
