/********************************************************************************
** Form generated from reading UI file 'adddevicedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDEVICEDIALOG_H
#define UI_ADDDEVICEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddDeviceDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *ID;
    QLabel *label_2;
    QComboBox *model;
    QGroupBox *groupBox_2;
    QWidget *formLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QLineEdit *IP;
    QLabel *label_4;
    QSpinBox *port;

    void setupUi(QDialog *AddDeviceDialog)
    {
        if (AddDeviceDialog->objectName().isEmpty())
            AddDeviceDialog->setObjectName(QStringLiteral("AddDeviceDialog"));
        AddDeviceDialog->resize(400, 220);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AddDeviceDialog->sizePolicy().hasHeightForWidth());
        AddDeviceDialog->setSizePolicy(sizePolicy);
        buttonBox = new QDialogButtonBox(AddDeviceDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 180, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(AddDeviceDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 381, 81));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 20, 381, 59));
        gridLayout = new QGridLayout(formLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        ID = new QSpinBox(formLayoutWidget);
        ID->setObjectName(QStringLiteral("ID"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(ID->sizePolicy().hasHeightForWidth());
        ID->setSizePolicy(sizePolicy1);
        ID->setMinimum(1);
        ID->setMaximum(255);

        gridLayout->addWidget(ID, 0, 1, 1, 1);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        model = new QComboBox(formLayoutWidget);
        model->setObjectName(QStringLiteral("model"));

        gridLayout->addWidget(model, 1, 1, 1, 1);

        groupBox_2 = new QGroupBox(AddDeviceDialog);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 100, 381, 81));
        formLayoutWidget_2 = new QWidget(groupBox_2);
        formLayoutWidget_2->setObjectName(QStringLiteral("formLayoutWidget_2"));
        formLayoutWidget_2->setGeometry(QRect(0, 19, 381, 57));
        gridLayout_2 = new QGridLayout(formLayoutWidget_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(formLayoutWidget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        IP = new QLineEdit(formLayoutWidget_2);
        IP->setObjectName(QStringLiteral("IP"));

        gridLayout_2->addWidget(IP, 0, 1, 1, 1);

        label_4 = new QLabel(formLayoutWidget_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 1);

        port = new QSpinBox(formLayoutWidget_2);
        port->setObjectName(QStringLiteral("port"));
        port->setMaximum(65535);

        gridLayout_2->addWidget(port, 1, 1, 1, 1);


        retranslateUi(AddDeviceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddDeviceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddDeviceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddDeviceDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDeviceDialog)
    {
        AddDeviceDialog->setWindowTitle(QApplication::translate("AddDeviceDialog", "New Device", 0));
        groupBox->setTitle(QApplication::translate("AddDeviceDialog", "Simulation", 0));
        label->setText(QApplication::translate("AddDeviceDialog", "ID", 0));
        label_2->setText(QApplication::translate("AddDeviceDialog", "Model", 0));
        groupBox_2->setTitle(QApplication::translate("AddDeviceDialog", "Controller", 0));
        label_3->setText(QApplication::translate("AddDeviceDialog", "IP Address", 0));
        label_4->setText(QApplication::translate("AddDeviceDialog", "Port", 0));
    } // retranslateUi

};

namespace Ui {
    class AddDeviceDialog: public Ui_AddDeviceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDEVICEDIALOG_H
