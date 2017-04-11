/********************************************************************************
** Form generated from reading UI file 'deviceviewdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEVIEWDIALOG_H
#define UI_DEVICEVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DeviceViewDialog
{
public:
    QTableWidget *viewTableWidget;

    void setupUi(QDialog *DeviceViewDialog)
    {
        if (DeviceViewDialog->objectName().isEmpty())
            DeviceViewDialog->setObjectName(QStringLiteral("DeviceViewDialog"));
        DeviceViewDialog->resize(450, 337);
        viewTableWidget = new QTableWidget(DeviceViewDialog);
        viewTableWidget->setObjectName(QStringLiteral("viewTableWidget"));
        viewTableWidget->setGeometry(QRect(10, 10, 431, 321));

        retranslateUi(DeviceViewDialog);

        QMetaObject::connectSlotsByName(DeviceViewDialog);
    } // setupUi

    void retranslateUi(QDialog *DeviceViewDialog)
    {
        DeviceViewDialog->setWindowTitle(QApplication::translate("DeviceViewDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class DeviceViewDialog: public Ui_DeviceViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEVIEWDIALOG_H
