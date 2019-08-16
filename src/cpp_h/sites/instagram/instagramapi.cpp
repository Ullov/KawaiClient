#include "instagramapi.h"

InstagramApi::InstagramApi() { }

InstagramApi::~InstagramApi() { }


void InstagramApi::doWork()
{
    chunk = {
        "Host: www.instagram.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:67.0) Gecko/20100101 Firefox/67.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Referer: https://www.google.com/",
        "Cookie: mid=XO2zugAEAAHMt4ISM7ZLmK4-sJBG; csrftoken=f80zFTvzyHZLDLdICpFG0TYBlDJZ4Zxa; fbm_124024574287414=base_domain=.instagram.com; rur=FTW; urlgen=\"{\\\"188.134.74.134\\\": 41733}:1hkZcA:tfFDBoPKRIspoGY5-AIDWOvw6co\\\"; fbsr_124024574287414=vY4IkvHj21G88LFPrpJxessiDPHVLNyDC7Lzy9NPP2Q.eyJ1c2VyX2lkIjoiMTAwMDEzNjYzMDg0NjA2IiwiY29kZSI6IkFRQkl6aWFZV3lacV9Tc0ZrNzlSRV9sQlNvRVpXdHVkRDdHbHQ2ZHZHTnlBanpwVndxVFlTdVZCSkNnRncwU3JNb1djTUp1dHZfNHFZUG0yU1R5QzFnQmRfNW5BcTF3SW1BRkllTGFpNHQyZXBjcExtQWNoTEtGWlhoRWp5bUhyaWY0YUNRQ2RCLVhOaVkySENwd0VsN3g3azlVRXg4QWwxT1BvdW5qRFREazh0Q0kwZ0VHbnd1aElESC1tMDVhUTVlQ054UlZkUktENlhOSzJGUnBVSUNNbWkyQ0o5cUkta1Q4TkVydlpPQ3N2eC1NOW13Vm93XzRSSDlXZW5SekZwMVl4bTlLU25FaVdwaFB0cU5ReGhzRXR1NlNyYV9YZUR4dkZuRVBNMVZUNEFXejUtdHVRWGRPMjJ3ZzZoak1JcU9XUTNYdnVQc0JIYTlQb055Sm1SbEpZIiwib2F1dGhfdG9rZW4iOiJFQUFCd3pMaXhuallCQUhqQ0dKZkxvTklORXBBTmpaQzE0b2d2cGdaQTZqaGIzMFkzMW9DRjNvd1pBV09EZmQ3cnl4cU1MVlFpZGdPbzFzRE0yc1ZWU29HSkdHcVpDaU42OWs1RDBSMlJUanVhdlQ2ckpEdmhQQ3pwMFdaQ0dSa05jZmxXTmJ2ZkRUd3FQS1pDUUoyR1dKNmhJOU96YjV1bjg5dllzZkdOWkNrWkJpWkNvY1BNdGE3V2ciLCJhbGdvcml0aG0iOiJITUFDLVNIQTI1NiIsImlzc3VlZF9hdCI6MTU2MjYxNTE4Nn0",
        "Upgrade-Insecure-Requests: 1",
        "TE: Trailers"
    };
    postChunk = {
        "Host: scontent-arn2-1.cdninstagram.com",
        "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:68.0) Gecko/20100101 Firefox/68.0",
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
        "Accept-Language: en-GB,en;q=0.5",
        "Accept-Encoding: gzip, deflate, br",
        "DNT: 1",
        "Connection: keep-alive",
        "Upgrade-Insecure-Requests: 1",
        "Pragma: no-cache",
        "Cache-Control: no-cache",
        "TE: Trailers"
    };

    logging("Downloading user " + userName + " started.");
    halfPath = basePath + "\\[" + userName + ']';
    std::string data;
    CurlClass *cc = new CurlClass(chunk);
    QJsonObject personData;

    currUrl = "https://www.instagram.com/" + userName + '/';
    data = cc->performing(currUrl.c_str());
    pattern = "=*({(\")(.)+})+";
    findMatchChars(data, pattern, regexResult);
    int j = 0;
    for (int i = 0; i < regexResult.size(); i++)
    {
        QString tmp = regexResult[i].c_str();
        QJsonObject obj = jsonObjectFromString(tmp);
        if (!obj.isEmpty())
        {
            objects.push_back(obj);
            bool isIt = objects[j].value("bundle_variant").isString();
            if (isIt)
            {
                personData = objects[j];
            }
            writeJsonDataInFile(objects[j], halfPath + "\\metadata\\basePage", std::to_string(j) + ".txt");
            j++;
        }
    }

    logging("All auxiliary data downloaded.");

    userId = personData.value("entry_data").toObject().value("ProfilePage").toArray().at(0).toObject().value("graphql").toObject().value("user").toObject().value("id").toString().toStdString();
    QJsonArray posts = personData.value("entry_data").toObject().value("ProfilePage").toArray().at(0).toObject().value("graphql").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("edges").toArray();
    after = personData.value("entry_data").toObject().value("ProfilePage").toArray().at(0).toObject().value("graphql").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("page_info").toObject().value("end_cursor").toString().toStdString();
    hasNextPage = personData.value("entry_data").toObject().value("ProfilePage").toArray().at(0).toObject().value("graphql").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("page_info").toObject().value("has_next_page").toBool();
    objects.clear();
    shortcode.clear();

    for (int i = 0; i < posts.size(); i++)
    {
        shortcode.push_back(posts[i].toObject().value("node").toObject().value("shortcode").toString().toStdString());
        postId = posts[i].toObject().value("node").toObject().value("id").toString().toStdString();
        logging("Starting downloading post with ID " + postId + '.');
        currUrl = "https://www.instagram.com/graphql/query/?query_hash=" + queryHash + "&variables={\"shortcode\":\"" + shortcode[i] + "\",\"child_comment_count\":3,\"fetch_comment_count\":40,\"parent_comment_count\":24,\"has_threaded_comments\":true}";
        objects.push_back(downloadJson(currUrl, *cc));
        writeJsonDataInFile(objects[i], halfPath + "\\metadata\\posts", postId + ".txt");
        bool isVideo = objects[i].value("data").toObject().value("shortcode_media").toObject().value("is_video").toBool();
        if (isVideo)
        {
            currUrl = objects[i].value("data").toObject().value("shortcode_media").toObject().value("video_url").toString().toStdString();
            cc->setHeader(postChunk);
            downloadAndWriteFile(currUrl, *cc, halfPath + "\\videos", postId + ".mp4");
            cc->setHeader(chunk);
        }
        else
        {
            bool hereNotOneImage = objects[i].value("data").toObject().value("shortcode_media").toObject().value("edge_sidecar_to_children").toObject().value("edges").isArray();
            if (hereNotOneImage)
            {
                postImages = objects[i].value("data").toObject().value("shortcode_media").toObject().value("edge_sidecar_to_children").toObject().value("edges").toArray();
                for (int j = 0; j <  postImages.size(); j++)
                {
                    currUrl = postImages[j].toObject().value("node").toObject().value("display_url").toString().toStdString();
                    cc->setHeader(postChunk);
                    downloadAndWriteFile(currUrl, *cc, halfPath + "\\photos\\" + postId, std::to_string(j) + ".jpg");
                    cc->setHeader(chunk);
                    delay(3);
                }
            }
            else
            {
                currUrl = objects[i].value("data").toObject().value("shortcode_media").toObject().value("display_url").toString().toStdString();
                cc->setHeader(postChunk);
                downloadAndWriteFile(currUrl, *cc, halfPath + "\\photos", postId + ".jpg");
                cc->setHeader(chunk);
            }
        }
        logging("Post with ID " + postId + " downloaded.");
        delay(3);
    }

    while (hasNextPage)
    {
        objects.clear();
        shortcode.clear();
        currUrl = "https://www.instagram.com/graphql/query/?query_hash=" + queryHash + "&variables={\"id\":\"" + userId + "\",\"first\":12,\"after\":\"" + after + "\"}";
        QJsonObject obj = downloadJson(currUrl, *cc);
        after = obj.value("data").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("page_info").toObject().value("end_cursor").toString().toStdString();
        hasNextPage = obj.value("data").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("page_info").toObject().value("has_next_page").toBool();
        posts = obj.value("data").toObject().value("user").toObject().value("edge_owner_to_timeline_media").toObject().value("edges").toArray();

        for (int i = 0; i < posts.size(); i++)
        {
            shortcode.push_back(posts[i].toObject().value("node").toObject().value("shortcode").toString().toStdString());
            postId = posts[i].toObject().value("node").toObject().value("id").toString().toStdString();
            logging("Starting downloading post with ID " + postId + '.');
            currUrl = "https://www.instagram.com/graphql/query/?query_hash=" + queryHash + "&variables={\"shortcode\":\"" + shortcode[i] + "\",\"child_comment_count\":1000,\"fetch_comment_count\":1000,\"parent_comment_count\":1000,\"has_threaded_comments\":true}";
            objects.push_back(downloadJson(currUrl, *cc));
            writeJsonDataInFile(objects[i], halfPath + "\\metadata\\posts", postId + ".txt");
            bool isVideo = objects[i].value("data").toObject().value("shortcode_media").toObject().value("is_video").toBool();
            if (isVideo)
            {
                currUrl = objects[i].value("data").toObject().value("shortcode_media").toObject().value("video_url").toString().toStdString();
                cc->setHeader(postChunk);
                downloadAndWriteFile(currUrl, *cc, halfPath + "\\videos", postId + ".mp4");
                cc->setHeader(chunk);
           }
           else
           {
                bool hereNotOneImage = objects[i].value("data").toObject().value("shortcode_media").toObject().value("edge_sidecar_to_children").toObject().value("edges").isArray();
                if (hereNotOneImage)
                {
                    postImages = objects[i].value("data").toObject().value("shortcode_media").toObject().value("edge_sidecar_to_children").toObject().value("edges").toArray();
                    for (int j = 0; j <  postImages.size(); j++)
                    {
                        currUrl = postImages[j].toObject().value("node").toObject().value("display_url").toString().toStdString();
                        cc->setHeader(postChunk);
                        downloadAndWriteFile(currUrl, *cc, halfPath + "\\photos\\" + postId, std::to_string(j) + ".jpg");
                        cc->setHeader(chunk);
                        delay(3);
                    }
                }
                else
                {
                    currUrl = objects[i].value("data").toObject().value("shortcode_media").toObject().value("display_url").toString().toStdString();
                    cc->setHeader(postChunk);
                    downloadAndWriteFile(currUrl, *cc, halfPath + "\\photos", postId + ".jpg");
                    cc->setHeader(chunk);
                }
           }
           logging("Post with ID " + postId + " downloaded.");
           delay(3);
        }
    }

    emit downloadingFinished();
}


// http://jkorpela.fi/perl/regexp.html

// https://www.instagram.com/p/BzshZB6AbtH/
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables={%22shortcode%22%3A%22BzshZB6AbtH%22%2C%22child_comment_count%22%3A30%2C%22fetch_comment_count%22%3A40%2C%22parent_comment_count%22%3A24%2C%22has_threaded_comments%22%3Atrue}
// https://www.instagram.com/radasok/
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables=%7B%22shortcode%22%3A%22Bxe0r5ZiCiN%22%2C%22child_comment_count%22%3A3%2C%22fetch_comment_count%22%3A40%2C%22parent_comment_count%22%3A24%2C%22has_threaded_comments%22%3Atrue%7D
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables=%7B%22shortcode%22%3A%22Bxe0r5ZiCiN%22%2C%22child_comment_count%22%3A3%2C%22fetch_comment_count%22%3A40%2C%22parent_comment_count%22%3A24%2C%22has_threaded_comments%22%3Atrue%7D
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables=%7B%22shortcode%22%3A%22BzIWKbnCSF6%22%2C%22child_comment_count%22%3A3%2C%22fetch_comment_count%22%3A40%2C%22parent_comment_count%22%3A24%2C%22has_threaded_comments%22%3Atrue%7D
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables=%7B%22shortcode%22%3A%22BzshZB6AbtH%22%2C%22child_comment_count%22%3A3%2C%22fetch_comment_count%22%3A40%2C%22parent_comment_count%22%3A24%2C%22has_threaded_comments%22%3Atrue%7D
// https://www.instagram.com/graphql/query/?query_hash=aec5501414615eca36a9acf075655b1e&variables={%22user_id%22%3A%22277857910%22%2C%22include_chaining%22%3Atrue%2C%22include_reel%22%3Atrue%2C%22include_suggested_users%22%3Atrue%2C%22include_logged_out_extras%22%3Atrue%2C%22include_highlight_reels%22%3Atrue}
// https://www.instagram.com/graphql/query/?query_hash=477b65a610463740ccdb83135b2014db&variables={%22shortcode%22:%22BzshZB6AbtH%22,%22child_comment_count%22:3,%22fetch_comment_count%22:40,%22parent_comment_count%22:24,%22has_threaded_comments%22:true}
// https://scontent-arn2-1.cdninstagram.com/vp/b6a76124d252ab7415757e1ae62e2db4/5DA60F39/t51.2885-15/e35/17818994_1131979800264410_6020790751598739456_n.jpg?_nc_ht=scontent-arn2-1.cdninstagram.com

// f2405b236d85e8296cf30347c9f08c2a
// 477b65a610463740ccdb83135b2014db
// 477b65a610463740ccdb83135b2014db
// f2405b236d85e8296cf30347c9f08c2a
