/****************************************************************************
** Meta object code from reading C++ file 'minesfieldwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../minesfieldwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'minesfieldwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MinesFieldWidget_t {
    QByteArrayData data[8];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MinesFieldWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MinesFieldWidget_t qt_meta_stringdata_MinesFieldWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "MinesFieldWidget"
QT_MOC_LITERAL(1, 17, 24), // "verticalScrollPosChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 3), // "pos"
QT_MOC_LITERAL(4, 47, 26), // "horizontalScrollPosChanged"
QT_MOC_LITERAL(5, 74, 16), // "scrollPosChanged"
QT_MOC_LITERAL(6, 91, 14), // "horizontal_pos"
QT_MOC_LITERAL(7, 106, 12) // "vertical_pos"

    },
    "MinesFieldWidget\0verticalScrollPosChanged\0"
    "\0pos\0horizontalScrollPosChanged\0"
    "scrollPosChanged\0horizontal_pos\0"
    "vertical_pos"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MinesFieldWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       5,    2,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    7,

       0        // eod
};

void MinesFieldWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MinesFieldWidget *_t = static_cast<MinesFieldWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->verticalScrollPosChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->horizontalScrollPosChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->scrollPosChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject MinesFieldWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_MinesFieldWidget.data,
      qt_meta_data_MinesFieldWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MinesFieldWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MinesFieldWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MinesFieldWidget.stringdata0))
        return static_cast<void*>(const_cast< MinesFieldWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int MinesFieldWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE