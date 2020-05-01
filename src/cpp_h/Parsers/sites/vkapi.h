#ifndef VKAPI_H
#define VKAPI_H

#include "../parserclass.h"
#include "../../KTools/HtmlAstMaker/htmlobject.h"
#include <QXmlStreamReader>
#include <locale>
#include <codecvt>

class VkApi : public ParserClass
{
public:
    VkApi();

    QString postUrl;

//public slots:
    void downloadPost();
};

#endif // VKAPI_H
