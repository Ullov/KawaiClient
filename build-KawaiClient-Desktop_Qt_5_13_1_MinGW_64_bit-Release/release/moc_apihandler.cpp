/****************************************************************************
** Meta object code from reading C++ file 'apihandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../src/cpp_h/apihandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'apihandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ApiHandler_t {
    QByteArrayData data[9];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ApiHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ApiHandler_t qt_meta_stringdata_ApiHandler = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ApiHandler"
QT_MOC_LITERAL(1, 11, 27), // "universalDownloadingStarted"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 4), // "mode"
QT_MOC_LITERAL(4, 45, 28), // "universalDownloadingFinished"
QT_MOC_LITERAL(5, 74, 4), // "data"
QT_MOC_LITERAL(6, 79, 25), // "universalStartDownloading"
QT_MOC_LITERAL(7, 105, 5), // "param"
QT_MOC_LITERAL(8, 111, 38) // "universalEmitSignalDownloadin..."

    },
    "ApiHandler\0universalDownloadingStarted\0"
    "\0mode\0universalDownloadingFinished\0"
    "data\0universalStartDownloading\0param\0"
    "universalEmitSignalDownloadingFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ApiHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    2,   42,    2, 0x0a /* Public */,
       8,    2,   47,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QJsonObject,    3,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QStringList, QMetaType::QStringList,    7,    3,
    QMetaType::Void, QMetaType::QStringList, QMetaType::QJsonObject,    3,    5,

       0        // eod
};

void ApiHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ApiHandler *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->universalDownloadingStarted((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 1: _t->universalDownloadingFinished((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        case 2: _t->universalStartDownloading((*reinterpret_cast< const QStringList(*)>(_a[1])),(*reinterpret_cast< const QStringList(*)>(_a[2]))); break;
        case 3: _t->universalEmitSignalDownloadingFinished((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QJsonObject(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ApiHandler::*)(QStringList );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiHandler::universalDownloadingStarted)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ApiHandler::*)(QStringList , QJsonObject );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ApiHandler::universalDownloadingFinished)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ApiHandler::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ApiHandler.data,
    qt_meta_data_ApiHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ApiHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ApiHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ApiHandler.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ApiHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ApiHandler::universalDownloadingStarted(QStringList _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ApiHandler::universalDownloadingFinished(QStringList _t1, QJsonObject _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
