/********************************************************************************
** Form generated from reading UI file 'addmodeldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDMODELDIALOG_H
#define UI_ADDMODELDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddModelDialog
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QWidget *formLayoutWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *nState;
    QLabel *label_2;
    QSpinBox *nControl;
    QLabel *label_3;
    QDoubleSpinBox *deltat;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *modelName;
    QHBoxLayout *horizontalLayout;
    QLineEdit *modelPathDisp;
    QToolButton *modelPath;

    void setupUi(QDialog *AddModelDialog)
    {
        if (AddModelDialog->objectName().isEmpty())
            AddModelDialog->setObjectName(QStringLiteral("AddModelDialog"));
        AddModelDialog->resize(400, 237);
        buttonBox = new QDialogButtonBox(AddModelDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(30, 190, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(AddModelDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 381, 181));
        formLayoutWidget = new QWidget(groupBox);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(0, 20, 381, 159));
        gridLayout = new QGridLayout(formLayoutWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        nState = new QSpinBox(formLayoutWidget);
        nState->setObjectName(QStringLiteral("nState"));
        nState->setMinimum(3);
        nState->setMaximum(255);

        gridLayout->addWidget(nState, 0, 1, 1, 1);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        nControl = new QSpinBox(formLayoutWidget);
        nControl->setObjectName(QStringLiteral("nControl"));
        nControl->setMinimum(1);
        nControl->setMaximum(255);

        gridLayout->addWidget(nControl, 1, 1, 1, 1);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        deltat = new QDoubleSpinBox(formLayoutWidget);
        deltat->setObjectName(QStringLiteral("deltat"));
        deltat->setMinimum(0.01);
        deltat->setMaximum(1);
        deltat->setSingleStep(0.01);
        deltat->setValue(0.01);

        gridLayout->addWidget(deltat, 2, 1, 1, 1);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        modelName = new QLineEdit(formLayoutWidget);
        modelName->setObjectName(QStringLiteral("modelName"));

        gridLayout->addWidget(modelName, 4, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        modelPathDisp = new QLineEdit(formLayoutWidget);
        modelPathDisp->setObjectName(QStringLiteral("modelPathDisp"));
        modelPathDisp->setEnabled(false);

        horizontalLayout->addWidget(modelPathDisp);

        modelPath = new QToolButton(formLayoutWidget);
        modelPath->setObjectName(QStringLiteral("modelPath"));
        modelPath->setFocusPolicy(Qt::WheelFocus);
        modelPath->setAcceptDrops(false);

        horizontalLayout->addWidget(modelPath);


        gridLayout->addLayout(horizontalLayout, 3, 1, 1, 1);

        QWidget::setTabOrder(nState, nControl);
        QWidget::setTabOrder(nControl, deltat);
        QWidget::setTabOrder(deltat, modelPath);
        QWidget::setTabOrder(modelPath, modelName);
        QWidget::setTabOrder(modelName, modelPathDisp);

        retranslateUi(AddModelDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddModelDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddModelDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddModelDialog);
    } // setupUi

    void retranslateUi(QDialog *AddModelDialog)
    {
        AddModelDialog->setWindowTitle(QApplication::translate("AddModelDialog", "Add Model", 0));
        groupBox->setTitle(QApplication::translate("AddModelDialog", "model", 0));
        label->setText(QApplication::translate("AddModelDialog", "# state", 0));
        label_2->setText(QApplication::translate("AddModelDialog", "# control", 0));
        label_3->setText(QApplication::translate("AddModelDialog", "Delta t [s]", 0));
        label_4->setText(QApplication::translate("AddModelDialog", "model", 0));
        label_5->setText(QApplication::translate("AddModelDialog", "model name", 0));
        modelPath->setText(QApplication::translate("AddModelDialog", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class AddModelDialog: public Ui_AddModelDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDMODELDIALOG_H
