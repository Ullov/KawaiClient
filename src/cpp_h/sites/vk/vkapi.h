#ifndef VKAPI_H
#define VKAPI_H

#include "cpp_h/parserclass.h"
#include <QXmlStreamReader>
#include <locale>
#include <codecvt>

class VkApi : public ParserClass
{
    Q_OBJECT
public:
    VkApi();

    std::string postUrl;

public slots:
    void downloadPost();
};

#endif // VKAPI_H
