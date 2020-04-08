#ifndef NHENTAIAPI_H
#define NHENTAIAPI_H

#include "cpp_h/parserclass.h"

class NhentaiApi : public ParserClass
{
    Q_OBJECT
public:
    NhentaiApi();
    ~NhentaiApi();

    QString id;

public slots:
    void doWork();
};

#endif // NHENTAIAPI_H
