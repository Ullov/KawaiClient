#ifndef KFFVSTRING_H
#define KFFVSTRING_H

#include "../../KTools/kawaiconverter.h"
#include "../../KTools/nativefs.h"

class KffVString
{
public:
    KffVString();

    QString& operator=(const QString &right);
    QString& getData();
    QByteArray toKffRawData();
    void fromKffRawData(NativeFs &file, const qint64 startPos);

private:
    QString data;
};

#endif // KFFVSTRING_H
