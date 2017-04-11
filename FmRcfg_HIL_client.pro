#-------------------------------------------------
#
# Project created by QtCreator 2017-04-01T16:06:30
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
include(/usr/local/qwt-6.1.2/features/qwt.prf)

TARGET = test
TEMPLATE = app

INCLUDEPATH += ./inc

SOURCES += \
    src/adddevicedialog.cpp \
    src/addmodeldialog.cpp \
    src/common.cpp \
    src/deviceviewdialog.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/modelviewdialog.cpp \
    src/settingdialog.cpp \
    src/uav.cpp \
    src/uavdevice.cpp \
    src/uavmodel.cpp \
    src/udpthread.cpp

HEADERS += \
    inc/adddevicedialog.h \
    inc/addmodeldialog.h \
    inc/common.h \
    inc/controllercommunication.h \
    inc/deviceviewdialog.h \
    inc/mainwindow.h \
    inc/modelviewdialog.h \
    inc/settingdialog.h \
    inc/uav.h \
    inc/uavdevice.h \
    inc/uavmodel.h \
    inc/udpthread.h

FORMS += \
    form/adddevicedialog.ui \
    form/addmodeldialog.ui \
    form/deviceviewdialog.ui \
    form/mainwindow.ui \
    form/modelviewdialog.ui \
    form/settingdialog.ui
