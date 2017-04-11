/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionShow_All_Models;
    QAction *actionShow_All_Devices;
    QAction *actionSet;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_4;
    QPushButton *taskButton;
    QPushButton *addDeviceButton;
    QPushButton *stopButton;
    QPushButton *startButton;
    QPushButton *addModelButton;
    QGridLayout *gridLayout_1;
    QwtPlot *map;
    QTextBrowser *console;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menuModels;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1000, 800);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(850, 700));
        MainWindow->setFocusPolicy(Qt::NoFocus);
        MainWindow->setAutoFillBackground(false);
        actionShow_All_Models = new QAction(MainWindow);
        actionShow_All_Models->setObjectName(QStringLiteral("actionShow_All_Models"));
        actionShow_All_Models->setCheckable(false);
        actionShow_All_Devices = new QAction(MainWindow);
        actionShow_All_Devices->setObjectName(QStringLiteral("actionShow_All_Devices"));
        actionShow_All_Devices->setCheckable(false);
        actionSet = new QAction(MainWindow);
        actionSet->setObjectName(QStringLiteral("actionSet"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        taskButton = new QPushButton(centralWidget);
        taskButton->setObjectName(QStringLiteral("taskButton"));

        gridLayout_4->addWidget(taskButton, 0, 2, 1, 1);

        addDeviceButton = new QPushButton(centralWidget);
        addDeviceButton->setObjectName(QStringLiteral("addDeviceButton"));

        gridLayout_4->addWidget(addDeviceButton, 0, 1, 1, 1);

        stopButton = new QPushButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        gridLayout_4->addWidget(stopButton, 0, 4, 1, 1);

        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));

        gridLayout_4->addWidget(startButton, 0, 3, 1, 1);

        addModelButton = new QPushButton(centralWidget);
        addModelButton->setObjectName(QStringLiteral("addModelButton"));

        gridLayout_4->addWidget(addModelButton, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_4, 1, 0, 1, 1);

        gridLayout_1 = new QGridLayout();
        gridLayout_1->setSpacing(6);
        gridLayout_1->setObjectName(QStringLiteral("gridLayout_1"));
        map = new QwtPlot(centralWidget);
        map->setObjectName(QStringLiteral("map"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(3);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(map->sizePolicy().hasHeightForWidth());
        map->setSizePolicy(sizePolicy1);

        gridLayout_1->addWidget(map, 1, 0, 1, 1);

        console = new QTextBrowser(centralWidget);
        console->setObjectName(QStringLiteral("console"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(console->sizePolicy().hasHeightForWidth());
        console->setSizePolicy(sizePolicy2);
        QFont font;
        font.setFamily(QStringLiteral("Monaco"));
        font.setPointSize(10);
        console->setFont(font);

        gridLayout_1->addWidget(console, 1, 1, 1, 1);


        gridLayout->addLayout(gridLayout_1, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 22));
        menuModels = new QMenu(menuBar);
        menuModels->setObjectName(QStringLiteral("menuModels"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuModels->menuAction());
        menuModels->addAction(actionShow_All_Models);
        menuModels->addAction(actionShow_All_Devices);
        menuModels->addSeparator();
        menuModels->addAction(actionSet);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionShow_All_Models->setText(QApplication::translate("MainWindow", "Show All Models", 0));
        actionShow_All_Devices->setText(QApplication::translate("MainWindow", "Show All Devices", 0));
        actionSet->setText(QApplication::translate("MainWindow", "Set client port", 0));
        taskButton->setText(QApplication::translate("MainWindow", "Task", 0));
        addDeviceButton->setText(QApplication::translate("MainWindow", "Add Device", 0));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0));
        addModelButton->setText(QApplication::translate("MainWindow", "Add Model", 0));
        menuModels->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
