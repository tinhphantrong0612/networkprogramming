/****************************************************************************
** Meta object code from reading C++ file 'stageprepare.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.11)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Client_UI/stageprepare.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stageprepare.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.11. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StagePrepare_t {
    QByteArrayData data[10];
    char stringdata0[166];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StagePrepare_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StagePrepare_t qt_meta_stringdata_StagePrepare = {
    {
QT_MOC_LITERAL(0, 0, 12), // "StagePrepare"
QT_MOC_LITERAL(1, 13, 19), // "on_btnStart_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 19), // "on_btnReady_clicked"
QT_MOC_LITERAL(4, 54, 21), // "on_btnUnready_clicked"
QT_MOC_LITERAL(5, 76, 24), // "on_btnChangeTeam_clicked"
QT_MOC_LITERAL(6, 101, 29), // "on_actionQuit_Lobby_triggered"
QT_MOC_LITERAL(7, 131, 18), // "on_btnKick_clicked"
QT_MOC_LITERAL(8, 150, 9), // "onReceive"
QT_MOC_LITERAL(9, 160, 5) // "char*"

    },
    "StagePrepare\0on_btnStart_clicked\0\0"
    "on_btnReady_clicked\0on_btnUnready_clicked\0"
    "on_btnChangeTeam_clicked\0"
    "on_actionQuit_Lobby_triggered\0"
    "on_btnKick_clicked\0onReceive\0char*"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StagePrepare[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x08 /* Private */,
       3,    0,   50,    2, 0x08 /* Private */,
       4,    0,   51,    2, 0x08 /* Private */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    1,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,

       0        // eod
};

void StagePrepare::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StagePrepare *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_btnStart_clicked(); break;
        case 1: _t->on_btnReady_clicked(); break;
        case 2: _t->on_btnUnready_clicked(); break;
        case 3: _t->on_btnChangeTeam_clicked(); break;
        case 4: _t->on_actionQuit_Lobby_triggered(); break;
        case 5: _t->on_btnKick_clicked(); break;
        case 6: _t->onReceive((*reinterpret_cast< char*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StagePrepare::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_StagePrepare.data,
    qt_meta_data_StagePrepare,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StagePrepare::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StagePrepare::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StagePrepare.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int StagePrepare::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
