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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
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
    QHBoxLayout *horizontalLayout;
    QPushButton *btnOpenFile;
    QPushButton *btnSaveAs;
    QSpacerItem *horizontalSpacer;
    QTableWidget *tableWidget;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *lineEditNewDate;
    QPushButton *btnAddDate;
    QPushButton *btnModifyDate;
    QPushButton *btnShowCurrentDate;
    QLabel *label;
    QLineEdit *lineEditBirthday;
    QPushButton *btnShowPreviousDay;
    QPushButton *btnCalculateDuration;
    QPushButton *btnCalculateBirthday;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        btnOpenFile = new QPushButton(centralwidget);
        btnOpenFile->setObjectName("btnOpenFile");

        horizontalLayout->addWidget(btnOpenFile);

        btnSaveAs = new QPushButton(centralwidget);
        btnSaveAs->setObjectName("btnSaveAs");

        horizontalLayout->addWidget(btnSaveAs);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setColumnCount(4);

        verticalLayout->addWidget(tableWidget);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        lineEditNewDate = new QLineEdit(centralwidget);
        lineEditNewDate->setObjectName("lineEditNewDate");

        gridLayout->addWidget(lineEditNewDate, 0, 1, 1, 1);

        btnAddDate = new QPushButton(centralwidget);
        btnAddDate->setObjectName("btnAddDate");

        gridLayout->addWidget(btnAddDate, 0, 2, 1, 1);

        btnModifyDate = new QPushButton(centralwidget);
        btnModifyDate->setObjectName("btnModifyDate");

        gridLayout->addWidget(btnModifyDate, 0, 3, 1, 1);

        btnShowCurrentDate = new QPushButton(centralwidget);
        btnShowCurrentDate->setObjectName("btnShowCurrentDate");

        gridLayout->addWidget(btnShowCurrentDate, 0, 4, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 1, 0, 1, 1);

        lineEditBirthday = new QLineEdit(centralwidget);
        lineEditBirthday->setObjectName("lineEditBirthday");

        gridLayout->addWidget(lineEditBirthday, 1, 1, 1, 1);

        btnShowPreviousDay = new QPushButton(centralwidget);
        btnShowPreviousDay->setObjectName("btnShowPreviousDay");

        gridLayout->addWidget(btnShowPreviousDay, 1, 2, 1, 1);

        btnCalculateDuration = new QPushButton(centralwidget);
        btnCalculateDuration->setObjectName("btnCalculateDuration");

        gridLayout->addWidget(btnCalculateDuration, 1, 3, 1, 1);

        btnCalculateBirthday = new QPushButton(centralwidget);
        btnCalculateBirthday->setObjectName("btnCalculateBirthday");

        gridLayout->addWidget(btnCalculateBirthday, 1, 4, 1, 1);


        verticalLayout->addLayout(gridLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Date Manager", nullptr));
        btnOpenFile->setText(QCoreApplication::translate("MainWindow", "Open File", nullptr));
        btnSaveAs->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Date:", nullptr));
        btnAddDate->setText(QCoreApplication::translate("MainWindow", "Add Date", nullptr));
        btnModifyDate->setText(QCoreApplication::translate("MainWindow", "Modify Date", nullptr));
        btnShowCurrentDate->setText(QCoreApplication::translate("MainWindow", "Current Date", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Birth Date:", nullptr));
        btnShowPreviousDay->setText(QCoreApplication::translate("MainWindow", "Previous", nullptr));
        btnCalculateDuration->setText(QCoreApplication::translate("MainWindow", "Duration", nullptr));
        btnCalculateBirthday->setText(QCoreApplication::translate("MainWindow", "Calculate Birthday", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
