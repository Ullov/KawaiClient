#include "kffvarray.h"

template<typename T>
KffVArray<T>::KffVArray() {}

template<typename T>
KffVArray<T>& KffVArray<T>::operator+=(const T &right)
{
    data.append(right);
    return *this;
}

template<typename T>
QByteArray KffVArray<T>::toKffRawData()
{
    QByteArray result;
    for (qint32 i = 0; i < data.size(); i++)
    {

    }
}
