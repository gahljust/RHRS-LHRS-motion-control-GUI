/****************************************************************************
** Meta object code from reading C++ file 'inputbox.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "inputbox.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inputbox.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_InputBox_t {
    QByteArrayData data[12];
    char stringdata0[200];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputBox_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputBox_t qt_meta_stringdata_InputBox = {
    {
QT_MOC_LITERAL(0, 0, 8), // "InputBox"
QT_MOC_LITERAL(1, 9, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 23), // "on_buttonBox_2_accepted"
QT_MOC_LITERAL(4, 56, 23), // "on_buttonBox_2_rejected"
QT_MOC_LITERAL(5, 80, 15), // "on_rdbY_clicked"
QT_MOC_LITERAL(6, 96, 15), // "on_rdbX_clicked"
QT_MOC_LITERAL(7, 112, 19), // "on_rdbTheta_clicked"
QT_MOC_LITERAL(8, 132, 16), // "on_rdbx1_clicked"
QT_MOC_LITERAL(9, 149, 16), // "on_rdbx2_clicked"
QT_MOC_LITERAL(10, 166, 16), // "on_rdby1_clicked"
QT_MOC_LITERAL(11, 183, 16) // "on_rdby2_clicked"

    },
    "InputBox\0on_buttonBox_accepted\0\0"
    "on_buttonBox_2_accepted\0on_buttonBox_2_rejected\0"
    "on_rdbY_clicked\0on_rdbX_clicked\0"
    "on_rdbTheta_clicked\0on_rdbx1_clicked\0"
    "on_rdbx2_clicked\0on_rdby1_clicked\0"
    "on_rdby2_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputBox[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void InputBox::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InputBox *_t = static_cast<InputBox *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_buttonBox_accepted(); break;
        case 1: _t->on_buttonBox_2_accepted(); break;
        case 2: _t->on_buttonBox_2_rejected(); break;
        case 3: _t->on_rdbY_clicked(); break;
        case 4: _t->on_rdbX_clicked(); break;
        case 5: _t->on_rdbTheta_clicked(); break;
        case 6: _t->on_rdbx1_clicked(); break;
        case 7: _t->on_rdbx2_clicked(); break;
        case 8: _t->on_rdby1_clicked(); break;
        case 9: _t->on_rdby2_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject InputBox::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_InputBox.data,
      qt_meta_data_InputBox,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *InputBox::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputBox::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InputBox.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int InputBox::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE