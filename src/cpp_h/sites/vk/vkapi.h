#ifndef VKAPI_H
#define VKAPI_H

#include "cpp_h/parserclass.h"
#include "cpp_h/kawaihtmlparser.h"
#include <QXmlStreamReader>
#include <locale>
#include <codecvt>

class VkApi : public ParserClass
{
    Q_OBJECT
public:
    VkApi();

    QString postUrl;

public slots:
    void downloadPost();
};

#endif // VKAPI_H
