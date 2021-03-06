#include "pixiv.h"

#include "../../KTools/curl.h"
#include "../../KTools/converter.h"
#include "../../KTools/file.h"
#include "../../KTools/enums.h"
#include <QVariant>

Parsers::Sites::Pixiv::Pixiv()
{
    setParserType(Parsers::Pixiv);
}

Parsers::Sites::Pixiv::~Pixiv() { }


void Parsers::Sites::Pixiv::download()
{
    chunk = {
        "Another: yes",
        "Host: www.pixiv.net",
        "Accept: application/json",
        "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://www.pixiv.net/member.php?id=18065282",
        "x-user-id: 18488812",
        "Connection: keep-alive",
        "Cookie: p_ab_id=1; p_ab_id_2=7; __utma=235335808.355378163.1494447379.1558943621.1558944813.130; __utmz=235335808.1558900071.128.53.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); __utmv=235335808.|2=login%20ever=yes=1^3=plan=normal=1^5=gender=male=1^6=user_id=18488812=1^9=p_ab_id=1=1^10=p_ab_id_2=7=1^11=lang=en=1; tag_view_ranking=RTJMXD26Ak~Lt-oEicbBr~ETjPkL0e6r~0xsDLqCEW6~WcTW9TCOx9~iFcW6hPGPU~pzzjRSV6ZO~EGefOqA6KB~52-15K-YXl~OT4SuGenFI~EUwzYuPRbU~zIv0cf5VVk~KN7uxuR89w~75zhzbk0bS~XGVDO5sORD~AihybUX3P-~kP7msdIeEU~eVxus64GZU~LJo91uBPz4~_hSAdpN9rx~BtXd1-LPRH~K8esoIs2eW~UX647z2Emo~qHE8UcOyMy~BEa426Zwwo~AQAq0FA_rP~jH0uD88V6F~-sp-9oh8uv~1F9SMtTyiX~CLR9k9dHAQ~Ie2c51_4Sp~YRDwjaiLZn~CrFcrMFJzz~QviSTvyfUE~v3f3nUY-vS~q3eUobDMJW~2gFeb6g4wP~q-S6HsPgp5~kxSeeOQL7R~0CtNNtdNS1~qtVr8SCFs5~bXMh6mBhl8~ECJv9QeOpm~B8KB6p6d7I~q303ip6Ui5~_pwIgrV8TB~VN7cgWyMmg~PwDMGzD6xn~BSkdEJ73Ii~-Lny-nXdRn~_gqyYStNPs~MIH8Vyk9qM~dJhzkwjS8s~Ltq1hgLZe3~cbmDKjZf9z~gpglyfLkWs~JV3RDzj_oP~hXe3jglu8l~XRs93UFEiK~KZjz93K9LX~oCry9yTawY~Q5yDy3jUo3~nbhKdqn9zY~EdHvbaqh4D~nbsmIXaCVu~Nbvc4l7O_x~r_Oj1GtRHw~45lBTXMujG~tdaIUxsdd1~-f8f9Ryaje~xDNMOGqgU-~RHf0cOJqH7~r6wU2cFbEP~vmBE9Rxxmi~losiurMy1p~--ZZY7WnE3~Bo1xMRD4DT~tIqkVZurKP~f8pnWEIf9Z~7-Z8cQo2up~ibtDlA-vhh~kdkWnz2DyL~BBqIDMQ8fd~AySgACkvx3~9O50QqcNJJ~2tZVEF6l6T~J6V3OmA4Jc~tf0x8pUL6L~4TDL3X7bV9~HcBlC3F1Sy~ay54Q_G6oX~tgP8r-gOe_~FPCeANM2Bm~zyKU3Q5L4C~RybylJRnhJ~hHXjRsPIa6~9qyG0MuN7x~gSv9Z7FIPR~MXwFJxP6uY~3kJ6ohuHPh; _ga=GA1.2.355378163.1494447379; login_ever=yes; _td=ad3f9f15-1246-4f39-bd9f-3ce8058abd19; c_type=18; a_type=0; b_type=1; module_orders_mypage=%5B%7B%22name%22%3A%22sketch_live%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22tag_follow%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22recommended_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22fanbox%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22user_events%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22sensei_courses%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D; first_visit_datetime_pc=2018-05-29+08%3A22%3A51; privacy_policy_agreement=1; p_ab_d_id=1190730061; yuid_b=cwY5ZYA; ki_t=1538829237068%3B1558958322869%3B1558958322869%3B4%3B4; ki_s=191516%3A0.0.0.0.0%3B194280%3A0.0.0.0.0%3B197685%3A0.0.0.0.0; ki_r=; __utmc=235335808; is_sensei_service_user=1; _gid=GA1.2.2009628348.1558900071; __utmb=235335808.32.9.1558960550252; login_bc=1; device_token=c0900d0a0c8057f292d2963b7f77f03a; PHPSESSID=18488812_1a9b146f844b9afefafc1f5aba1ad870; _gat=1",
        "TE: Trailers"
    };
    novelCoverChunk = {
        "Host: s.pximg.net",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache"
    };

    QVector<QByteArray> imagesChunk = {
        "Host: i-f.pximg.net",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:73.0) Gecko/20100101 Firefox/73.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://www.pixiv.net/en/artworks/77845097",
        "DNT: 1",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };

    QVector<QByteArray> ugoiraChunk = {
        "Host: i-f.pximg.net",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:73.0) Gecko/20100101 Firefox/73.0",
        "Accept: */*",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://www.pixiv.net/en/artworks/77802991",
        "Origin: https://www.pixiv.net",
        "DNT: 1",
        "Connection: keep-alive",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };

    this->cc->setHeader(chunk);
    QString type = "Pixiv";
    QString logPath;

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId);
    userName = object.value("body").toObject().value("name").toString();
    KTools::Converter::toNtfsCompatibleString(userName);
    rootPath = basePath + "\\" + '[' + userId + "](" + userName + ')';
    for (int i = 0; KTools::File::dirExist(rootPath); i++)
        rootPath = basePath + "\\" + '[' + userId + "](" + userName + ")[" + QString::number(i) + ']';
    logPath = rootPath;
    writeInfoLog("Downloading user with ID " + userId + " started.");
    writeJsonDataInFile(object, rootPath + "\\txt", "userProfile.txt");

    currUrl = object.value("body").toObject().value("imageBig").toString();
    downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "\\", "icon");

    currUrl = object.value("body").toObject().value("background").toObject().value("url").toString();
    if (!currUrl.isEmpty())
    {
        downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "\\", "background");
        writeInfoLog("User background downloaded.");
    }
    else
        writeInfoLog("User have an empty background.");

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/top");
    writeJsonDataInFile(object, rootPath + "\\txt", "userProfileTop.txt");

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/all");
    writeJsonDataInFile(object, rootPath + "\\txt", "userProfileAll.txt");

    writeInfoLog("All profile files successfully downloaded.");

    QStringList illusts = object.value("body").toObject().value("illusts").toObject().keys();
    QStringList mangas = object.value("body").toObject().value("manga").toObject().keys();
    QStringList novels = object.value("body").toObject().value("novels").toObject().keys();

    writeInfoLog("Find " + QString::number(illusts.size()) + " illustrations.");

    for (int i = 0; i < illusts.size(); i++) // pictures download
    {
        writeInfoLog("(" + QString::number(i) + '/' + QString::number(illusts.size()) + ") Start downloading post with ID " + illusts[i]);

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i]);
        QString illustType = object.value("body").toObject().value("illustType").toVariant().toString();
        writeJsonDataInFile(object, rootPath + "\\txt\\illust\\about", illusts[i] + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + illusts[i] + "&limit=1000");
        writeJsonDataInFile(object, rootPath + "\\txt\\illust\\comments", illusts[i] + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i] + "/pages");
        writeJsonDataInFile(object, rootPath + "\\txt\\illust\\pages", illusts[i] + ".txt");

        arrJ = object.value("body").toArray();

        if(illustType == "0")
        {
            cc->setHeader(imagesChunk);
            for (int j = 0; j < arrJ.size(); j++)
            {
                currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString();
                if (arrJ.size() > 1)
                    downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "\\illust\\" + illusts[i], QString::number(j));
                else
                    downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "\\illust", illusts[i]);
            }
            cc->setHeader(chunk);
        }
        else
        {
            object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i] + "/ugoira_meta");
            currUrl = object.value("body").toObject().value("originalSrc").toString();
            cc->setHeader(ugoiraChunk);
            downloadAndWriteFile(currUrl, rootPath + "\\ugoira", illusts[i] + ".zip");
            cc->setHeader(chunk);
        }


        writeInfoLog("Post with ID " + illusts[i] + " successfully downloaded.");
    }

    writeInfoLog("Find " + QString::number(mangas.size()) + " manga posts.");
    for (int i = 0; i < mangas.size(); i++) // mangas download
    {
        writeInfoLog("(" + QString::number(i) + '/' + QString::number(mangas.size()) + ") Start downloading post with ID " + mangas[i]);

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i]);
        writeJsonDataInFile(object, rootPath + "\\txt\\manga\\about", mangas[i] + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + mangas[i] + "&limit=1000");
        writeJsonDataInFile(object, rootPath + "\\txt\\manga\\comments", mangas[i] + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i] + "/pages");
        writeJsonDataInFile(object, rootPath + "\\txt\\manga\\pages", mangas[i] + ".txt");

        arrJ = object.value("body").toArray();
        cc->setHeader(imagesChunk);
        for (int j = 0; j < arrJ.size(); j++)
        {
            currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString();
            downloadAndWriteFileWithDefinedExtension(currUrl, rootPath + "\\manga\\" + mangas[i], QString::number(j));
        }
        cc->setHeader(chunk);

        writeInfoLog("Post with ID " + mangas[i] + " successfully downloaded.");
    }

    writeInfoLog("Find " + QString::number(novels.size()) + " novels.");
    for (int i = 0; i < novels.size(); i++)
    {
        writeInfoLog("(" + QString::number(i) + '/' + QString::number(novels.size()) + ") Start downloading novel with ID " + novels[i]);

        object = downloadJson("https://www.pixiv.net/ajax/novels/comments/roots?novel_id=" + novels[i] + "&limit=1000");
        writeJsonDataInFile(object, rootPath + "\\txt\\novels\\comments", novels[i] + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/novel/" + novels[i]);
        writeJsonDataInFile(object, rootPath + "\\txt\\novels\\about", novels[i] + ".txt");

        cc->setHeader(novelCoverChunk);
        currUrl = object.value("body").toObject().value("coverUrl").toString();
        downloadAndWriteFile(currUrl, rootPath + "\\novel\\" + novels[i], "cover.jpg");
        cc->setHeader(chunk);

        novelContent = object.value("body").toObject().value("content").toVariant().toByteArray();
        KTools::File::writeFile(novelContent, rootPath + "\\novel\\" + novels[i], "content.txt");

        writeInfoLog("Novel with ID " + novels[i] + " successfully downloaded.");
    }

    writeInfoLog("Downloading user with ID " + userId + " and name " + userName + " completed.");
    endDownloadingFunction(static_cast<int>(KTools::Enums::ParserModes::Pixiv::Download));
}

void Parsers::Sites::Pixiv::viewUser()
{
    chunk = {
        "Another: yes",
        "Host: www.pixiv.net",
        "Accept: application/json",
        "Accept-Language: ru-RU,ru;q=0.8,en-US;q=0.5,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "Referer: https://www.pixiv.net/member.php?id=18065282",
        "x-user-id: 18488812",
        "Connection: keep-alive",
        "Cookie: p_ab_id=1; p_ab_id_2=7; __utma=235335808.355378163.1494447379.1558943621.1558944813.130; __utmz=235335808.1558900071.128.53.utmcsr=google|utmccn=(organic)|utmcmd=organic|utmctr=(not%20provided); __utmv=235335808.|2=login%20ever=yes=1^3=plan=normal=1^5=gender=male=1^6=user_id=18488812=1^9=p_ab_id=1=1^10=p_ab_id_2=7=1^11=lang=en=1; tag_view_ranking=RTJMXD26Ak~Lt-oEicbBr~ETjPkL0e6r~0xsDLqCEW6~WcTW9TCOx9~iFcW6hPGPU~pzzjRSV6ZO~EGefOqA6KB~52-15K-YXl~OT4SuGenFI~EUwzYuPRbU~zIv0cf5VVk~KN7uxuR89w~75zhzbk0bS~XGVDO5sORD~AihybUX3P-~kP7msdIeEU~eVxus64GZU~LJo91uBPz4~_hSAdpN9rx~BtXd1-LPRH~K8esoIs2eW~UX647z2Emo~qHE8UcOyMy~BEa426Zwwo~AQAq0FA_rP~jH0uD88V6F~-sp-9oh8uv~1F9SMtTyiX~CLR9k9dHAQ~Ie2c51_4Sp~YRDwjaiLZn~CrFcrMFJzz~QviSTvyfUE~v3f3nUY-vS~q3eUobDMJW~2gFeb6g4wP~q-S6HsPgp5~kxSeeOQL7R~0CtNNtdNS1~qtVr8SCFs5~bXMh6mBhl8~ECJv9QeOpm~B8KB6p6d7I~q303ip6Ui5~_pwIgrV8TB~VN7cgWyMmg~PwDMGzD6xn~BSkdEJ73Ii~-Lny-nXdRn~_gqyYStNPs~MIH8Vyk9qM~dJhzkwjS8s~Ltq1hgLZe3~cbmDKjZf9z~gpglyfLkWs~JV3RDzj_oP~hXe3jglu8l~XRs93UFEiK~KZjz93K9LX~oCry9yTawY~Q5yDy3jUo3~nbhKdqn9zY~EdHvbaqh4D~nbsmIXaCVu~Nbvc4l7O_x~r_Oj1GtRHw~45lBTXMujG~tdaIUxsdd1~-f8f9Ryaje~xDNMOGqgU-~RHf0cOJqH7~r6wU2cFbEP~vmBE9Rxxmi~losiurMy1p~--ZZY7WnE3~Bo1xMRD4DT~tIqkVZurKP~f8pnWEIf9Z~7-Z8cQo2up~ibtDlA-vhh~kdkWnz2DyL~BBqIDMQ8fd~AySgACkvx3~9O50QqcNJJ~2tZVEF6l6T~J6V3OmA4Jc~tf0x8pUL6L~4TDL3X7bV9~HcBlC3F1Sy~ay54Q_G6oX~tgP8r-gOe_~FPCeANM2Bm~zyKU3Q5L4C~RybylJRnhJ~hHXjRsPIa6~9qyG0MuN7x~gSv9Z7FIPR~MXwFJxP6uY~3kJ6ohuHPh; _ga=GA1.2.355378163.1494447379; login_ever=yes; _td=ad3f9f15-1246-4f39-bd9f-3ce8058abd19; c_type=18; a_type=0; b_type=1; module_orders_mypage=%5B%7B%22name%22%3A%22sketch_live%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22tag_follow%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22recommended_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22fanbox%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22user_events%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22sensei_courses%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D; first_visit_datetime_pc=2018-05-29+08%3A22%3A51; privacy_policy_agreement=1; p_ab_d_id=1190730061; yuid_b=cwY5ZYA; ki_t=1538829237068%3B1558958322869%3B1558958322869%3B4%3B4; ki_s=191516%3A0.0.0.0.0%3B194280%3A0.0.0.0.0%3B197685%3A0.0.0.0.0; ki_r=; __utmc=235335808; is_sensei_service_user=1; _gid=GA1.2.2009628348.1558900071; __utmb=235335808.32.9.1558960550252; login_bc=1; device_token=c0900d0a0c8057f292d2963b7f77f03a; PHPSESSID=18488812_1a9b146f844b9afefafc1f5aba1ad870; _gat=1",
        "TE: Trailers"
    };

    this->cc->setHeader(chunk);
    //CurlClass *cc = new CurlClass(chunk);
    std::string type = "Pixiv";
    std::string logPath;

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId);
    userData = object;
    //imagesFromApi = downloadAllUrls(object, *cc);
    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/all");
    userAllData = object;
    //imagesFromApi.append(downloadAllUrls(object, *cc));
    //emit viewDataDownloaded(userData, userAllData, imagesFromApi);
}

/*
    // https://www.pixiv.net/ajax/user/18065282/profile/all
    // https://www.pixiv.net/ajax/user/1457424/profile/top
    // https://www.pixiv.net/ajax/user/1457424
    // https://www.pixiv.net/ajax/illust/75259345/pages
    // https://www.pixiv.net/ajax/illust/58504977
    // https://www.pixiv.net/ajax/illust/56621259
    // https://www.pixiv.net/ajax/illust/72297344
    // https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=72297344&limit=10000
    // https://www.pixiv.net/ajax/illust/comments/roots?illust_id=74630293
    // https://www.pixiv.net/ajax/illust/74113204/ugoira_meta
    // https://www.pixiv.net/ajax/novel/11280232
    // https://www.pixiv.net/ajax/novels/comments/roots?novel_id=11280232&limit=1000
    // https://www.pixiv.net/ajax/novel/11280232
    // https://www.pixiv.net/ajax/novel/8407773
*/

void Parsers::Sites::Pixiv::getRecomendedUsers()
{
    chunk = {
        "Host: www.pixiv.net",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:74.0) Gecko/20100101 Firefox/74.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8",
        "Accept-Language: ja,en-US;q=0.7,en;q=0.3",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Upgrade-Insecure-Requests: 1",
        "Connection: keep-alive",
        "Cookie: first_visit_datetime_pc=2020-03-15+21%3A19%3A40; PHPSESSID=18488812_ePaEVOtpaPRa3DrJpoXngn3bMPzLF23w; p_ab_id=9; p_ab_id_2=5; p_ab_d_id=162095390; yuid_b=FDRpgVQ; tag_view_ranking=RTJMXD26Ak~Lt-oEicbBr~0xsDLqCEW6~ETjPkL0e6r~zIv0cf5VVk~BU9SQkS-zU~EZQqoW9r8g~m3EJRa33xU~ay54Q_G6oX~OT4SuGenFI~kP7msdIeEU~y8GNntYHsi~q3eUobDMJW~EGefOqA6KB~RcahSSzeRf~Fq4K_8PGib~90n3-8i-qU~LJo91uBPz4~iFcW6hPGPU~pzzjRSV6ZO~EUwzYuPRbU~nQRrj5c6w_~-98s6o2-Rp~Y6fKlRsRt6~LVSDGaCAdn~tf0x8pUL6L~qtVr8SCFs5~RRFW9UEFcZ~n39RQWfHku~_hSAdpN9rx~Ce-EdaHA-3~CrFcrMFJzz~rqvM6GS14_~WcTW9TCOx9~-sp-9oh8uv~3mLXnunyNA~xgA3yCXKWS~VQA20ZDKeQ~bkSTvfrPKL~-MlX-zJDYF~v8hYE7ZOhd~BEa426Zwwo~QKeXYK2oSR~5oPIfUbtd6~abNIEh2zTB~2R7RYffVfj~EmhsFxSBo-~JmUnt_Iy_U~rkLi5JvRDj~J6V3OmA4Jc~KN7uxuR89w~52-15K-YXl~UX647z2Emo~mSipZ8R7EW~PwDMGzD6xn~yBnMz57lw_~JtHr1OyMVc~IEelj7HCPz~kZyLZDtxMx~K8_BEpmEzt~75zhzbk0bS~uzTh6oIVtD~GXriz-nrnQ~Oa9b6mEc1T~tyFEDMZCsd~CLR9k9dHAQ~qJ0gM6EMFd~sGIuAFCqQo~0Sds1vVNKR~FZibYFIIMZ~65aiw_5Y72~aKhT3n4RHZ~pYlUxeIoeg~azESOjmQSV~G_f4j5NH8i~CM9TZgYuXr~K8esoIs2eW~LSG3qSZIDS~21GI87QvUa~MQRzWUNTuf~8PDkVxzRxX~_hR5RtCi3o~9s62wUfVkX~0ZSEuSNvpZ~ECJv9QeOpm~JNUzt5TTQi~flb2ZnuOIx~XEuS3TPyCa~aUKGRzPd6e~FqVQndhufZ~qWFESUmfEs~wtFYZb5e1D~Avyrt8Dl6U~UrhMyHY4-s~g-QqiAp4D1~q7YTLRZUZb~2VFvdpks8q~DADQycFGB0~oaiId5Os_B~JBFbzljAuI; device_token=3bbf1934ce753c15819030cdfd73020c; privacy_policy_agreement=1; c_type=19; a_type=0; b_type=1; module_orders_mypage=%5B%7B%22name%22%3A%22sketch_live%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22tag_follow%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22recommended_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22everyone_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22following_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22mypixiv_new_illusts%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22spotlight%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22fanbox%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22featured_tags%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22contests%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22user_events%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22sensei_courses%22%2C%22visible%22%3Atrue%7D%2C%7B%22name%22%3A%22booth_follow_items%22%2C%22visible%22%3Atrue%7D%5D; __cfduid=df70f408ec755f18955632e82e83432bf1584641439; __utmc=235335808; is_sensei_service_user=1; login_ever=yes",
        "Cache-Control: max-age=0",
        "TE: Trailers"
    };
    cc->setHeader(chunk);
    currUrl = "https://www.pixiv.net/rpc/index.php?mode=get_recommend_users_and_works_by_user_ids&user_ids=2583663,8851285,257542,8189060,11&user_num=30&work_num=5";
    QJsonObject obj = KTools::Converter::convert<QString, QJsonObject>(cc->performing(currUrl.toUtf8()));
    QJsonArray illusts = obj["body"].toArray();
    // https://www.pixiv.net/rpc/index.php?mode=get_recommend_users_and_works_by_user_ids&user_ids=2583663,8851285,257542,8189060,11&user_num=30&work_num=5
}
