#include "kffvnumber.h"

template<typename T>
KffVNumber<T>::KffVNumber() {}

template<typename T>
T& KffVNumber<T>::operator=(const KffVNumber<T> &right)
{
    if (this == &right)
        return this;
    data = right.data;
    return *this;
}
template<typename T>
T& KffVNumber<T>::operator=(const T &right)
{
    data = right;
    return *data;
}

template<typename T>
T& KffVNumber<T>::getData()
{
    return data;
}

template<typename T>
QByteArray KffVNumber<T>::toKffRawData()
{
    return KawaiConverter::convert<T, QByteArray>(data);
}

template<typename T>
void KffVNumber<T>::fromKffRawData(NativeFs &file, const qint64 startPos)
{
    file.seek(startPos);
    data = file.read<T>();
}
