/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../inc/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[26];
    char stringdata0[364];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "on_newModelAdded"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 7), // "uint8_t"
QT_MOC_LITERAL(4, 37, 6), // "nState"
QT_MOC_LITERAL(5, 44, 8), // "nControl"
QT_MOC_LITERAL(6, 53, 6), // "deltat"
QT_MOC_LITERAL(7, 60, 9), // "modelPath"
QT_MOC_LITERAL(8, 70, 9), // "modelName"
QT_MOC_LITERAL(9, 80, 14), // "on_newDevAdded"
QT_MOC_LITERAL(10, 95, 2), // "ID"
QT_MOC_LITERAL(11, 98, 5), // "model"
QT_MOC_LITERAL(12, 104, 2), // "IP"
QT_MOC_LITERAL(13, 107, 8), // "uint16_t"
QT_MOC_LITERAL(14, 116, 4), // "port"
QT_MOC_LITERAL(15, 121, 21), // "on_newSettingReceived"
QT_MOC_LITERAL(16, 143, 10), // "clientPort"
QT_MOC_LITERAL(17, 154, 8), // "clientIP"
QT_MOC_LITERAL(18, 163, 20), // "on_newModelOutputGet"
QT_MOC_LITERAL(19, 184, 26), // "on_addDeviceButton_clicked"
QT_MOC_LITERAL(20, 211, 25), // "on_addModelButton_clicked"
QT_MOC_LITERAL(21, 237, 34), // "on_actionShow_All_Models_trig..."
QT_MOC_LITERAL(22, 272, 28), // "on_controllerMessageReceived"
QT_MOC_LITERAL(23, 301, 3), // "msg"
QT_MOC_LITERAL(24, 305, 22), // "on_actionSet_triggered"
QT_MOC_LITERAL(25, 328, 35) // "on_actionShow_All_Devices_tri..."

    },
    "MainWindow\0on_newModelAdded\0\0uint8_t\0"
    "nState\0nControl\0deltat\0modelPath\0"
    "modelName\0on_newDevAdded\0ID\0model\0IP\0"
    "uint16_t\0port\0on_newSettingReceived\0"
    "clientPort\0clientIP\0on_newModelOutputGet\0"
    "on_addDeviceButton_clicked\0"
    "on_addModelButton_clicked\0"
    "on_actionShow_All_Models_triggered\0"
    "on_controllerMessageReceived\0msg\0"
    "on_actionSet_triggered\0"
    "on_actionShow_All_Devices_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

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
       1,    5,   64,    2, 0x08 /* Private */,
       9,    4,   75,    2, 0x08 /* Private */,
      15,    2,   84,    2, 0x08 /* Private */,
      18,    0,   89,    2, 0x08 /* Private */,
      19,    0,   90,    2, 0x08 /* Private */,
      20,    0,   91,    2, 0x08 /* Private */,
      21,    0,   92,    2, 0x08 /* Private */,
      22,    1,   93,    2, 0x08 /* Private */,
      24,    0,   96,    2, 0x08 /* Private */,
      25,    0,   97,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Float, QMetaType::QString, QMetaType::QString,    4,    5,    6,    7,    8,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::QString, 0x80000000 | 13,   10,   11,   12,   14,
    QMetaType::Void, 0x80000000 | 13, QMetaType::QString,   16,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   23,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_newModelAdded((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->on_newDevAdded((*reinterpret_cast< uint8_t(*)>(_a[1])),(*reinterpret_cast< uint8_t(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< uint16_t(*)>(_a[4]))); break;
        case 2: _t->on_newSettingReceived((*reinterpret_cast< uint16_t(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->on_newModelOutputGet(); break;
        case 4: _t->on_addDeviceButton_clicked(); break;
        case 5: _t->on_addModelButton_clicked(); break;
        case 6: _t->on_actionShow_All_Models_triggered(); break;
        case 7: _t->on_controllerMessageReceived((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->on_actionSet_triggered(); break;
        case 9: _t->on_actionShow_All_Devices_triggered(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
