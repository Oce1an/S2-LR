/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QHBoxLayout *buttonLayout1;
    QPushButton *btnLoadFile;
    QPushButton *btnSaveFile;
    QPushButton *btnSortByPrice;
    QPushButton *btnClearTable;
    QSpacerItem *horizontalSpacer1;
    QHBoxLayout *buttonLayout2;
    QPushButton *btnAddComponent;
    QPushButton *btnDeleteComponent;
    QSpacerItem *horizontalSpacer2;
    QHBoxLayout *searchLayout;
    QLineEdit *lineEditSearch;
    QPushButton *btnSearch;
    QPushButton *btnBuildConfig;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setColumnCount(6);
        tableWidget->horizontalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(tableWidget);

        buttonLayout1 = new QHBoxLayout();
        buttonLayout1->setObjectName("buttonLayout1");
        btnLoadFile = new QPushButton(centralwidget);
        btnLoadFile->setObjectName("btnLoadFile");

        buttonLayout1->addWidget(btnLoadFile);

        btnSaveFile = new QPushButton(centralwidget);
        btnSaveFile->setObjectName("btnSaveFile");

        buttonLayout1->addWidget(btnSaveFile);

        btnSortByPrice = new QPushButton(centralwidget);
        btnSortByPrice->setObjectName("btnSortByPrice");

        buttonLayout1->addWidget(btnSortByPrice);

        btnClearTable = new QPushButton(centralwidget);
        btnClearTable->setObjectName("btnClearTable");

        buttonLayout1->addWidget(btnClearTable);

        horizontalSpacer1 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout1->addItem(horizontalSpacer1);


        verticalLayout->addLayout(buttonLayout1);

        buttonLayout2 = new QHBoxLayout();
        buttonLayout2->setObjectName("buttonLayout2");
        btnAddComponent = new QPushButton(centralwidget);
        btnAddComponent->setObjectName("btnAddComponent");

        buttonLayout2->addWidget(btnAddComponent);

        btnDeleteComponent = new QPushButton(centralwidget);
        btnDeleteComponent->setObjectName("btnDeleteComponent");

        buttonLayout2->addWidget(btnDeleteComponent);

        horizontalSpacer2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        buttonLayout2->addItem(horizontalSpacer2);


        verticalLayout->addLayout(buttonLayout2);

        searchLayout = new QHBoxLayout();
        searchLayout->setObjectName("searchLayout");
        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName("lineEditSearch");

        searchLayout->addWidget(lineEditSearch);

        btnSearch = new QPushButton(centralwidget);
        btnSearch->setObjectName("btnSearch");

        searchLayout->addWidget(btnSearch);

        btnBuildConfig = new QPushButton(centralwidget);
        btnBuildConfig->setObjectName("btnBuildConfig");

        searchLayout->addWidget(btnBuildConfig);


        verticalLayout->addLayout(searchLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "PC Component Manager", nullptr));
        btnLoadFile->setText(QCoreApplication::translate("MainWindow", "Load File", nullptr));
        btnSaveFile->setText(QCoreApplication::translate("MainWindow", "Save File", nullptr));
        btnSortByPrice->setText(QCoreApplication::translate("MainWindow", "Sort by Price", nullptr));
        btnClearTable->setText(QCoreApplication::translate("MainWindow", "Clear Table", nullptr));
        btnAddComponent->setText(QCoreApplication::translate("MainWindow", "Add Component", nullptr));
        btnDeleteComponent->setText(QCoreApplication::translate("MainWindow", "Delete Component", nullptr));
        lineEditSearch->setPlaceholderText(QCoreApplication::translate("MainWindow", "Search by type, manufacturer or model...", nullptr));
        btnSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        btnBuildConfig->setText(QCoreApplication::translate("MainWindow", "Build PC Configuration", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
