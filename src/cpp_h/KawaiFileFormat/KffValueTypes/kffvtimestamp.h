#ifndef KFFVTIMESTAMP_H
#define KFFVTIMESTAMP_H

#include "../../KTools/file.h"
#include <QDateTime>

class KffVTimestamp
{
public:
    KffVTimestamp();

    QByteArray toKffRawData();
    void fromKffRawData(KTools::File &file, const qint64 startPos);
    QString getData(const QString &format);
    qint64& getData();
    void setToCurrentTime();

private:
    qint64 data;
};

#endif // KFFVTIMESTAMP_H
