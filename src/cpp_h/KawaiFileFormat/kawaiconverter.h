#ifndef KAWAICONVERTER_H
#define KAWAICONVERTER_H

#include <QByteArray>
#include <QString>

class KawaiConverter
{
public:
    KawaiConverter();

    template<typename T>
    static T byteArrayToT(const QByteArray &bArr);
};

#endif // KAWAICONVERTER_H
