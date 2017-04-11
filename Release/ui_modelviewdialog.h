/********************************************************************************
** Form generated from reading UI file 'modelviewdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODELVIEWDIALOG_H
#define UI_MODELVIEWDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_ModelViewDialog
{
public:
    QHBoxLayout *horizontalLayout;
    QTableWidget *viewTableWidget;

    void setupUi(QDialog *ModelViewDialog)
    {
        if (ModelViewDialog->objectName().isEmpty())
            ModelViewDialog->setObjectName(QStringLiteral("ModelViewDialog"));
        ModelViewDialog->resize(400, 280);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ModelViewDialog->sizePolicy().hasHeightForWidth());
        ModelViewDialog->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(ModelViewDialog);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        viewTableWidget = new QTableWidget(ModelViewDialog);
        viewTableWidget->setObjectName(QStringLiteral("viewTableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(viewTableWidget->sizePolicy().hasHeightForWidth());
        viewTableWidget->setSizePolicy(sizePolicy1);
        viewTableWidget->setAlternatingRowColors(true);
        viewTableWidget->setSortingEnabled(true);
        viewTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        viewTableWidget->horizontalHeader()->setStretchLastSection(true);
        viewTableWidget->verticalHeader()->setCascadingSectionResizes(false);

        horizontalLayout->addWidget(viewTableWidget);


        retranslateUi(ModelViewDialog);

        QMetaObject::connectSlotsByName(ModelViewDialog);
    } // setupUi

    void retranslateUi(QDialog *ModelViewDialog)
    {
        ModelViewDialog->setWindowTitle(QApplication::translate("ModelViewDialog", "All Models", 0));
    } // retranslateUi

};

namespace Ui {
    class ModelViewDialog: public Ui_ModelViewDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODELVIEWDIALOG_H
