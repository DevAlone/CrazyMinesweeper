/****************************************************************************
** Meta object code from reading C++ file 'newgamedialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../newgamedialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newgamedialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NewGameDialog_t {
    QByteArrayData data[7];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewGameDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewGameDialog_t qt_meta_stringdata_NewGameDialog = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NewGameDialog"
QT_MOC_LITERAL(1, 14, 10), // "updateData"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 25), // "on_pushButtonEasy_clicked"
QT_MOC_LITERAL(4, 52, 33), // "on_pushButtonLIttleHarder_cli..."
QT_MOC_LITERAL(5, 86, 30), // "on_pushButtonAsianMode_clicked"
QT_MOC_LITERAL(6, 117, 29) // "on_pushButtonManually_clicked"

    },
    "NewGameDialog\0updateData\0\0"
    "on_pushButtonEasy_clicked\0"
    "on_pushButtonLIttleHarder_clicked\0"
    "on_pushButtonAsianMode_clicked\0"
    "on_pushButtonManually_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewGameDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NewGameDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NewGameDialog *_t = static_cast<NewGameDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateData(); break;
        case 1: _t->on_pushButtonEasy_clicked(); break;
        case 2: _t->on_pushButtonLIttleHarder_clicked(); break;
        case 3: _t->on_pushButtonAsianMode_clicked(); break;
        case 4: _t->on_pushButtonManually_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject NewGameDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_NewGameDialog.data,
      qt_meta_data_NewGameDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NewGameDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewGameDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NewGameDialog.stringdata0))
        return static_cast<void*>(const_cast< NewGameDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int NewGameDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
