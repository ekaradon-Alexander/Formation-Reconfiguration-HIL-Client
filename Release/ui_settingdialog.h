/********************************************************************************
** Form generated from reading UI file 'settingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGDIALOG_H
#define UI_SETTINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *network_groupBox;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QComboBox *ip_comboBox;
    QPushButton *refresh_pushButton;
    QSpinBox *port_spinBox;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QDialog *SettingDialog)
    {
        if (SettingDialog->objectName().isEmpty())
            SettingDialog->setObjectName(QStringLiteral("SettingDialog"));
        SettingDialog->resize(400, 300);
        buttonBox = new QDialogButtonBox(SettingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 260, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        network_groupBox = new QGroupBox(SettingDialog);
        network_groupBox->setObjectName(QStringLiteral("network_groupBox"));
        network_groupBox->setGeometry(QRect(10, 10, 381, 91));
        gridLayout = new QGridLayout(network_groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ip_comboBox = new QComboBox(network_groupBox);
        ip_comboBox->setObjectName(QStringLiteral("ip_comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ip_comboBox->sizePolicy().hasHeightForWidth());
        ip_comboBox->setSizePolicy(sizePolicy);
        ip_comboBox->setDuplicatesEnabled(true);

        horizontalLayout->addWidget(ip_comboBox);

        refresh_pushButton = new QPushButton(network_groupBox);
        refresh_pushButton->setObjectName(QStringLiteral("refresh_pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(refresh_pushButton->sizePolicy().hasHeightForWidth());
        refresh_pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(refresh_pushButton);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 1);

        port_spinBox = new QSpinBox(network_groupBox);
        port_spinBox->setObjectName(QStringLiteral("port_spinBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(3);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(port_spinBox->sizePolicy().hasHeightForWidth());
        port_spinBox->setSizePolicy(sizePolicy2);
        port_spinBox->setMaximum(65535);
        port_spinBox->setValue(0);

        gridLayout_2->addWidget(port_spinBox, 0, 1, 1, 1);

        label = new QLabel(network_groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(network_groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy3.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy3);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);


        gridLayout->addLayout(gridLayout_2, 1, 0, 1, 1);

        buttonBox->raise();
        network_groupBox->raise();
        label_2->raise();

        retranslateUi(SettingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingDialog)
    {
        SettingDialog->setWindowTitle(QApplication::translate("SettingDialog", "Dialog", 0));
        network_groupBox->setTitle(QApplication::translate("SettingDialog", "Network", 0));
        refresh_pushButton->setText(QApplication::translate("SettingDialog", "Refresh", 0));
        label->setText(QApplication::translate("SettingDialog", "Client Port", 0));
        label_2->setText(QApplication::translate("SettingDialog", "Client IP", 0));
    } // retranslateUi

};

namespace Ui {
    class SettingDialog: public Ui_SettingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGDIALOG_H
