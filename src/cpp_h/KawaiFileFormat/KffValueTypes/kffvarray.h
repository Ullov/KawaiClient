#ifndef KFFVARRAY_H
#define KFFVARRAY_H

#include "../../KTools/converter.h"
#include "../../KTools/file.h"

template<typename T>
class KffVArray
{
public:
    KffVArray();

    KffVArray<T>& operator+=(const T &right);
    QByteArray toKffRawData();
    void fromKffRawData(KTools::File &file, const qint64 startPos);

private:
    QVector<T> data;
};

#endif // KFFVARRAY_H
