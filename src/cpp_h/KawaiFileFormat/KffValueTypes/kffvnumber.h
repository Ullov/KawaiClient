#ifndef KFFVNUMBER_H
#define KFFVNUMBER_H

#include "../../KTools/converter.h"
#include "../../KTools/file.h"
#include <QByteArray>

template <typename T>
class KffVNumber
{
public:
    KffVNumber();

    T& operator=(const KffVNumber<T> &right);
    T& operator=(const T &right);
    T& getData();
    QByteArray toKffRawData();
    void fromKffRawData(KTools::File &file, const qint64 startPos);

private:
    T data;
};

#endif // KFFVNUMBER_H
