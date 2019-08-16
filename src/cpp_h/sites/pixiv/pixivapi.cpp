#include "pixivapi.h"

PixivApi::PixivApi() { }
PixivApi::~PixivApi() { }


void PixivApi::downloadUser()
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

    CurlClass *cc = new CurlClass(chunk);
    std::string type = "Pixiv";
    std::string logPath;


    //logging("Downloading user with ID " + userId + " started.");

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId, *cc);
    userName = object.value("body").toObject().value("name").toString().toStdString();
    halfPath = basePath + "\\" + '[' + userId + "](" + userName + ')';
    logPath = halfPath;
    logging->cppPerformLogging("Downloading user with ID " + userId + " started.", type, logPath);
    writeJsonDataInFile(object, halfPath + "\\txt", "userProfile.txt");

    currUrl = object.value("body").toObject().value("imageBig").toString().toStdString();
    downloadAndWriteFile(currUrl, *cc, halfPath + "\\", "icon.png");

    currUrl = object.value("body").toObject().value("background").toObject().value("url").toString().toStdString();
    if (!currUrl.empty())
    {
        downloadAndWriteFile(currUrl, *cc, halfPath + "\\", "background.png");
        logging->cppPerformLogging("User background downloaded.", type, logPath);
    }
    else
    {
        logging->cppPerformLogging("User have an empty background.", type, logPath);
    }

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/top", *cc);
    writeJsonDataInFile(object, halfPath + "\\txt", "userProfileTop.txt");

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/all", *cc);
    writeJsonDataInFile(object, halfPath + "\\txt", "userProfileAll.txt");

    logging->cppPerformLogging("All profile files successfully downloaded.", type, logPath);

    QStringList illusts = object.value("body").toObject().value("illusts").toObject().keys();
    QStringList mangas = object.value("body").toObject().value("manga").toObject().keys();
    QStringList novels = object.value("body").toObject().value("novels").toObject().keys();

    logging->cppPerformLogging("Find " + std::to_string(illusts.size()) + " illustrations.", type, logPath);

    for (int i = 0; i < illusts.size(); i++) // pictures download
    {
        logging->cppPerformLogging("(" + std::to_string(i) + '/' + std::to_string(illusts.size()) + ") Start downloading post with ID " + illusts[i].toStdString(), type, logPath);

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i].toStdString(), *cc);
        QString illusttype = object.value("body").toObject().value("illustType").toVariant().toString();
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\about", illusts[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + illusts[i].toStdString() + "&limit=1000", *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\comments", illusts[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i].toStdString() + "/pages", *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\pages", illusts[i].toStdString() + ".txt");

        arrJ = object.value("body").toArray();

        if(illusttype == "0")
        {
            for (int j = 0; j < arrJ.size(); j++)
            {
                currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString().toStdString();
                if (arrJ.size() > 1)
                {
                    downloadAndWriteFile(currUrl, *cc, halfPath + "\\illust\\" + illusts[i].toStdString(), std::to_string(j) + ".png");
                }
                else
                {
                    downloadAndWriteFile(currUrl, *cc, halfPath + "\\illust", illusts[i].toStdString() + ".png");
                }
            }
        }
        else
        {
            object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i].toStdString() + "/ugoira_meta", *cc);
            currUrl = object.value("body").toObject().value("originalSrc").toString().toStdString();
            downloadAndWriteFile(currUrl, *cc, halfPath + "\\ugoira", illusts[i].toStdString() + ".zip");
        }


        logging->cppPerformLogging("Post with ID " + illusts[i].toStdString() + " successfully downloaded.", type, logPath);
    }

    logging->cppPerformLogging("Find " + std::to_string(mangas.size()) + " manga posts.", type, logPath);
    for (int i = 0; i < mangas.size(); i++) // mangas download
    {
        logging->cppPerformLogging("(" + std::to_string(i) + '/' + std::to_string(mangas.size()) + ") Start downloading post with ID " + mangas[i].toStdString(), type, logPath);

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i].toStdString(), *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\about", mangas[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + mangas[i].toStdString() + "&limit=1000", *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\comments", mangas[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i].toStdString() + "/pages", *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\pages", mangas[i].toStdString() + ".txt");

        arrJ = object.value("body").toArray();
        for (int j = 0; j < arrJ.size(); j++)
        {
            currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString().toStdString();
            downloadAndWriteFile(currUrl, *cc, halfPath + "\\manga\\" + mangas[i].toStdString(), std::to_string(j) + ".png");
        }

        logging->cppPerformLogging("Post with ID " + mangas[i].toStdString() + " successfully downloaded.", type, logPath);
    }

    logging->cppPerformLogging("Find " + std::to_string(novels.size()) + " novels.", type, logPath);
    for (int i = 0; i < novels.size(); i++)
    {
        logging->cppPerformLogging("(" + std::to_string(i) + '/' + std::to_string(novels.size()) + ") Start downloading novel with ID " + novels[i].toStdString(), type, logPath);

        object = downloadJson("https://www.pixiv.net/ajax/novels/comments/roots?novel_id=" + novels[i].toStdString() + "&limit=1000", *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\novels\\comments", novels[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/novel/" + novels[i].toStdString(), *cc);
        writeJsonDataInFile(object, halfPath + "\\txt\\novels\\about", novels[i].toStdString() + ".txt");

        cc->setHeader(novelCoverChunk);
        currUrl = object.value("body").toObject().value("coverUrl").toString().toStdString();
        downloadAndWriteFile(currUrl, *cc, halfPath + "\\novel\\" + novels[i].toStdString(), "cover.jpg");
        cc->setHeader(chunk);

        novelContent = object.value("body").toObject().value("content").toString().toStdString();
        writeFile(novelContent, halfPath + "\\novel\\" + novels[i].toStdString(), "content.txt");

        logging->cppPerformLogging("Novel with ID " + novels[i].toStdString() + " successfully downloaded.", type, logPath);
    }

    logging->cppPerformLogging("Downloading user with ID " + userId + " and name " + userName + " completed.", type, logPath);
    emit downloadingFinished();
}

void PixivApi::viewUser()
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

    CurlClass *cc = new CurlClass(chunk);
    std::string type = "Pixiv";
    std::string logPath;

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId, *cc);
    userData = object;
    imagesFromApi = downloadAllUrls(object, *cc);
    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/all", *cc);
    userAllData = object;
    imagesFromApi.append(downloadAllUrls(object, *cc));
    emit viewDataDownloaded(userData, userAllData, imagesFromApi);
}

/*
void PixivApi::doWork()
{
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

    halfPath = basePath + "\\" + '[' + userId + ']';
    logging("[I] Downloading user with ID " + userId + " started.");
    CurlClass *pq = new CurlClass();

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId, *pq);
    userName = object.value("body").toObject().value("name").toString().toStdString();
    writeJsonDataInFile(object, halfPath + "\\txt", "userProfile.txt");

    currUrl = object.value("body").toObject().value("imageBig").toString().toStdString();
    downloadAndWriteFile(currUrl, *pq, halfPath + "\\", "icon.png");

    currUrl = object.value("body").toObject().value("background").toObject().value("url").toString().toStdString();
    if (!currUrl.empty())
    {
        downloadAndWriteFile(currUrl, *pq, halfPath + "\\", "background.png");
        logging("[I] User background downloaded.");
    }
    else
    {
        logging("[I] User have an empty background.");
    }

    object = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/top", *pq);
    writeJsonDataInFile(object, halfPath + "\\txt", "userProfileTop.txt");

    rootObject = downloadJson("https://www.pixiv.net/ajax/user/" + userId + "/profile/all", *pq);
    writeJsonDataInFile(rootObject, halfPath + "\\txt", "userProfileAll.txt");

    logging("[I] All profile files successfully downloaded.");

    QStringList illusts = rootObject.value("body").toObject().value("illusts").toObject().keys();

    logging("[I] Find " + std::to_string(illusts.size()) + " illustrations.");

    for (int i = 0; i < illusts.size(); i++) // pictures download
    {
        logging("[I] (" + std::to_string(i) + '/' + std::to_string(illusts.size()) + ") Start downloading post with ID " + illusts[i].toStdString());

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i].toStdString(), *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\about", illusts[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + illusts[i].toStdString() + "&limit=1000", *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\comments", illusts[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + illusts[i].toStdString() + "/pages", *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\illust\\pages", illusts[i].toStdString() + ".txt");

        arrJ = object.value("body").toArray();
        for (int j = 0; j < arrJ.size(); j++)
        {
            currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString().toStdString();
            if (arrJ.size() > 1)
            {
                downloadAndWriteFile(currUrl, *pq, halfPath + "\\illust\\" + illusts[i].toStdString(), std::to_string(j) + ".png");
            }
            else
            {
                downloadAndWriteFile(currUrl, *pq, halfPath + "\\illust", illusts[i].toStdString() + ".png");
            }
        }

        logging("[I] Post with ID " + illusts[i].toStdString() + " successfully downloaded.");
    }

    QStringList mangas = rootObject.value("body").toObject().value("manga").toObject().keys();
    logging("[I] Find " + std::to_string(mangas.size()) + " manga posts.");
    for (int i = 0; i < mangas.size(); i++) // mangas download
    {
        logging("[I] (" + std::to_string(i) + '/' + std::to_string(mangas.size()) + ") Start downloading post with ID " + mangas[i].toStdString());

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i].toStdString(), *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\about", mangas[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illusts/comments/roots?illust_id=" + mangas[i].toStdString() + "&limit=1000", *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\comments", mangas[i].toStdString() + ".txt");

        object = downloadJson("https://www.pixiv.net/ajax/illust/" + mangas[i].toStdString() + "/pages", *pq);
        writeJsonDataInFile(object, halfPath + "\\txt\\manga\\pages", mangas[i].toStdString() + ".txt");

        arrJ = object.value("body").toArray();
        for (int j = 0; j < arrJ.size(); j++)
        {
            currUrl = arrJ[j].toObject().value("urls").toObject().value("original").toString().toStdString();
            downloadAndWriteFile(currUrl, *pq, halfPath + "\\manga\\" + mangas[i].toStdString(), std::to_string(j) + ".png");
        }

        logging("[I] Post with ID " + mangas[i].toStdString() + " successfully downloaded.");
    }

    logging("[I] Downloading user with ID " + userId + " and name " + userName + " completed.");
    emit downloadingFinished();
}

QJsonObject PixivApi::jsonObjectFromString(QString &content)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());

    if (!doc.isNull())
    {
        if (doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            return {}; // document is not an object
        }
    }
    else
    {
        return {}; // invalid JSON
    }

    return obj;
}

bool PixivApi::writeFile(std::vector<byte> data, std::string directory, std::string fileName)
{
    QDir dir = QDir(directory.c_str());
    bool qexi = dir.exists();
    if (!qexi)
    {
        qexi = dir.mkpath(".");
    }
    std::ofstream file(directory + '\\' + fileName, std::ios::out | std::ios::binary);
    if (file.is_open())
    {
        file.write((const char*)&data[0], data.size());
        if (!file.good())
        {
            file.close();
            return false;
        }
    }
    else
    {
        file.close();
        return false;
    }
    file.close();
    return true;
}

void PixivApi::recExtractJson(QJsonObject rootObject, std::string offset, std::string &data)
{
    std::string tmp;
    QStringList keysChain = rootObject.keys(); // Number; Null; Array; String; Object(aka array); Bool;
    for (int i = 0; i < keysChain.length(); i++)
    {
        if (rootObject.value(keysChain[i]).isString()) // is string
        {
            tmp = offset + keysChain[i].toStdString() + ": " + rootObject.value(keysChain[i]).toString().toStdString() + '\n';
            data += tmp;
        }
        else if (rootObject.value(keysChain[i]).isObject()) // is object
        {
            data += offset + "\\+" + keysChain[i].toStdString() + '\n';
            recExtractJson(rootObject.value(keysChain[i]).toObject(), offset + '\t', data);
        }
        else if (rootObject.value(keysChain[i]).isNull()) // is null
        {
            data += offset + keysChain[i].toStdString() + ": Is Null\n";
        }
        else if (rootObject.value(keysChain[i]).isBool()) // is bool
        {
            if (rootObject.value(keysChain[i]).toBool())
            {
                tmp = offset + keysChain[i].toStdString() + ": True\n";
            }
            else
            {
                tmp = offset + keysChain[i].toStdString() + ": False\n";
            }
            data += tmp;
        }
        else if (rootObject.value(keysChain[i]).isArray()) // is array
        {
            data += offset + "\\+" + keysChain[i].toStdString() + '\n';
            QJsonValue val = rootObject.value(keysChain[i]);
            QJsonArray arr = val.toArray();
            int c = 0;
            offset += '\t';
            foreach (const QJsonValue &v, arr)
            {
                if (v.isBool())
                {
                    if (v.toBool())
                    {
                        tmp = offset + std::to_string(c) + ": True\n";
                    }
                    else
                    {
                        tmp = offset + std::to_string(c) + ": False\n";
                    }
                    data += tmp;
                }
                else if (v.isDouble())
                {
                    tmp = offset + std::to_string(c) + ": " + v.toString().toStdString() + '\n';
                    data += tmp;
                }
                else if (v.isNull())
                {
                    data += offset + std::to_string(c) + ": Is Null\n";
                }
                else if (v.isObject())
                {
                    data += offset + "\\+" + std::to_string(c) + '\n';
                    recExtractJson(v.toObject(), offset + '\t', data);
                }
                else if (v.isString())
                {
                    tmp = offset + std::to_string(c) + ": " + v.toString().toStdString() + '\n';
                    data += tmp;
                }
                c++;
            }
            offset.pop_back();
        }
        else if (rootObject.value(keysChain[i]).isDouble()) // is double (aka number)
        {
            tmp = offset + keysChain[i].toStdString() + ": " + rootObject.value(keysChain[i]).toVariant().toString().toStdString() + '\n';
            data += tmp;
        }
    }
    offset.pop_back();
}

void PixivApi::writeJsonDataInFile(QJsonObject &object, std::string path, std::string fileName)
{
    std::string jData;
    jData.erase();
    recExtractJson(object, "", jData);
    std::vector<byte> bJContent(jData.begin(), jData.end());
    writeFile(bJContent, path, fileName);
}

QJsonObject PixivApi::downloadJson(std::string url, CurlClass &pq)
{
    std::string result = pq.performing(url.c_str(), chunk);
    QString tmpString = QString::fromStdString(result);
    QJsonObject object = jsonObjectFromString(tmpString);
    return object;
}

void PixivApi::downloadAndWriteFile(std::string url, CurlClass &pq, std::string path, std::string fileName)
{
    std::string result = pq.performing(url.c_str(), chunk);
    std::vector<byte> bContent(result.begin(), result.end());
    writeFile(bContent, path, fileName);
}

void PixivApi::logging(std::string message)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    dt = dt + ' ' + message + '\n';

    //emit output(dt);

    std::vector<byte> data(dt.begin(), dt.end());
    QDir dir = QDir(basePath.c_str());
    bool qexi = dir.exists();
    if (!qexi)
    {
        qexi = dir.mkpath(".");
    }
    std::ofstream file(halfPath + "\\log.txt", std::ios::out | std::ios::binary | std::ios::app);
    if (file.is_open())
    {
        file.write((const char*)&data[0], data.size());
        if (!file.good())
        {
            file.close();
        }
    }
    else
    {
        file.close();
    }
    file.close();
}
*/
