#include "kffvstring.h"

KffVString::KffVString() {}

QString& KffVString::operator=(const QString &right)
{
    if (data == right)
        return data;
    data = right;
    return data;
}

QString& KffVString::getData()
{
    return data;
}

QByteArray KffVString::toKffRawData()
{
    //return KawaiConverter::convert<qint32, QByteArray>(data.size()) + KawaiConverter::convert<QString, QByteArray>(data);
}

void KffVString::fromKffRawData(KTools::File &file, const qint64 startPos)
{
    file.seek(startPos);
    //qint32 dataSize = file.read<qint32>();
    //file.seek(startPos + sizeof(qint32));
    //data = file.read<QString>(dataSize);
}
