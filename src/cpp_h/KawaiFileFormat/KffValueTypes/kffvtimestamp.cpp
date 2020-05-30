#include "kffvtimestamp.h"

#include "../../KTools/converter.h"

KffVTimestamp::KffVTimestamp() {}

QByteArray KffVTimestamp::toKffRawData()
{
    return KTools::Converter::convert<qint64, QByteArray>(data);
}

void KffVTimestamp::fromKffRawData(KTools::File &file, const qint64 startPos)
{
    file.seek(startPos);
    data = file.read<qint64>();
}

QString KffVTimestamp::getData(const QString &format)
{
    QDateTime tmp;
    tmp.setMSecsSinceEpoch(data);
    return tmp.toString(format);
}

qint64& KffVTimestamp::getData()
{
    return data;
}

void KffVTimestamp::setToCurrentTime()
{
    data = QDateTime().currentMSecsSinceEpoch();
}
