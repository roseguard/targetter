/****************************************************************************
** Meta object code from reading C++ file 'mainmenuscene.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainmenuscene.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainmenuscene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mainMenuScene_t {
    QByteArrayData data[5];
    char stringdata0[55];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainMenuScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainMenuScene_t qt_meta_stringdata_mainMenuScene = {
    {
QT_MOC_LITERAL(0, 0, 13), // "mainMenuScene"
QT_MOC_LITERAL(1, 14, 12), // "startClicked"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 14), // "optionsClicked"
QT_MOC_LITERAL(4, 43, 11) // "exitClicked"

    },
    "mainMenuScene\0startClicked\0\0optionsClicked\0"
    "exitClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainMenuScene[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mainMenuScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainMenuScene *_t = static_cast<mainMenuScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startClicked(); break;
        case 1: _t->optionsClicked(); break;
        case 2: _t->exitClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mainMenuScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainMenuScene::startClicked)) {
                *result = 0;
            }
        }
        {
            typedef void (mainMenuScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainMenuScene::optionsClicked)) {
                *result = 1;
            }
        }
        {
            typedef void (mainMenuScene::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainMenuScene::exitClicked)) {
                *result = 2;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject mainMenuScene::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_mainMenuScene.data,
      qt_meta_data_mainMenuScene,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mainMenuScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainMenuScene::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mainMenuScene.stringdata0))
        return static_cast<void*>(const_cast< mainMenuScene*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int mainMenuScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void mainMenuScene::startClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void mainMenuScene::optionsClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void mainMenuScene::exitClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
