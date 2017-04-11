/****************************************************************************
** Meta object code from reading C++ file 'addmodeldialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/addmodeldialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'addmodeldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AddModelDialog_t {
    QByteArrayData data[11];
    char stringdata0[127];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AddModelDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AddModelDialog_t qt_meta_stringdata_AddModelDialog = {
    {
QT_MOC_LITERAL(0, 0, 14), // "AddModelDialog"
QT_MOC_LITERAL(1, 15, 16), // "sendNewModelData"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "uint8_t"
QT_MOC_LITERAL(4, 41, 6), // "nState"
QT_MOC_LITERAL(5, 48, 8), // "nControl"
QT_MOC_LITERAL(6, 57, 6), // "deltat"
QT_MOC_LITERAL(7, 64, 9), // "modelPath"
QT_MOC_LITERAL(8, 74, 9), // "modelName"
QT_MOC_LITERAL(9, 84, 21), // "on_buttonBox_accepted"
QT_MOC_LITERAL(10, 106, 20) // "on_modelPath_clicked"

    },
    "AddModelDialog\0sendNewModelData\0\0"
    "uint8_t\0nState\0nControl\0deltat\0modelPath\0"
    "modelName\0on_buttonBox_accepted\0"
    "on_modelPath_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AddModelDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   40,    2, 0x08 /* Private */,
      10,    0,   41,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Float, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AddModelDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AddModelDialog *_t = static_cast<AddModelDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendNewModelData((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->on_buttonBox_accepted(); break;
        case 2: _t->on_modelPath_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AddModelDialog::*_t)(uint8_t , uint8_t , float , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AddModelDialog::sendNewModelData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AddModelDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_AddModelDialog.data,
      qt_meta_data_AddModelDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *AddModelDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AddModelDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_AddModelDialog.stringdata0))
        return static_cast<void*>(const_cast< AddModelDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int AddModelDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void AddModelDialog::sendNewModelData(uint8_t _t1, uint8_t _t2, float _t3, QString _t4, QString _t5)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
