#ifndef KFFVSTRING_H
#define KFFVSTRING_H

#include "../../KTools/converter.h"
#include "../../KTools/file.h"

class KffVString
{
public:
    KffVString();

    QString& operator=(const QString &right);
    QString& getData();
    QByteArray toKffRawData();
    void fromKffRawData(KTools::File &file, const qint64 startPos);

private:
    QString data;
};

#endif // KFFVSTRING_H
