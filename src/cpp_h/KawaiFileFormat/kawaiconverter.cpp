#include "kawaiconverter.h"

KawaiConverter::KawaiConverter() {}

template<typename T>
T KawaiConverter::byteArrayToT(const QByteArray &bArr)
{
    if (typeid(T) == typeid(qint32))        // int[32]
        return bArr.toInt();
    else if (typeid(T) == typeid(quint32))  // uint[32]
        return bArr.toUInt();

    else if (typeid(T) == typeid(qint64))   // int[64]
        return bArr.toLong();
    else if (typeid(T) == typeid(quint64))  // uint[64]
        return bArr.toULong();

    else if (typeid(T) == typeid(qint16))   // int[16]
        return bArr.toShort();
    else if (typeid(T) == typeid(quint16))  // uint[16]
        return bArr.toUShort();
}

template<>
const char* KawaiConverter::byteArrayToT<const char*>(const QByteArray &bArr)
{
    return bArr.data();
}

template<>
QString KawaiConverter::byteArrayToT<QString>(const QByteArray &bArr)
{
    return bArr;
}

template<>
QByteArray KawaiConverter::byteArrayToT<QByteArray>(const QByteArray &bArr)
{
    return bArr;
}
