/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(395, 550);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 30, 500, 600));
        widget->setMinimumSize(QSize(500, 0));
        widget->setStyleSheet(QString::fromUtf8("QPushButton#pushButton {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.506582, x2:1, y2:0.477, stop:0 rgba(40, 47, 78, 219), stop:1 rgba(85, 98, 112, 226));\n"
"    color: rgb(255, 255, 255);\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QPushButton#pushButton:hover {\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0.506582, x2:1, y2:0.477, stop:0 rgba(40, 67, 98, 219), stop:1 rgba(105, 118, 132, 225));\n"
"}\n"
"\n"
"QPushButton#pushButton:pressed {\n"
"    padding-left: 5px;\n"
"    padding-top: 5px;\n"
"    background-color: rgba(105, 118, 132, 200);\n"
"}\n"
""));
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 30, 300, 420));
        label->setStyleSheet(QString::fromUtf8("border-image :url(:/login/samuel-girven-VJ2s0c20qCo-unsplash.jpg);\n"
"border-radius:20px;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 30, 300, 420));
        label_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0.715099, stop:0 rgba(0, 0, 0, 50), stop:0.375 rgba(0, 0, 0, 50), stop:0.835227 rgba(0, 0, 0, 0), stop:1 rgba(0, 0, 0, 75));\n"
"border-radius: 20px;\n"
"\n"
""));
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 60, 280, 390));
        label_3->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,100);\n"
"border-radius:15px;"));
        label_4 = new QLabel(widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(135, 95, 90, 40));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color:rgba(255,255,255,210);"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(80, 165, 200, 40));
        QFont font1;
        font1.setPointSize(10);
        lineEdit->setFont(font1);
        lineEdit->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0);\n"
"border:none;\n"
"border-bottom:2px solid rgba(105,118,132,255);\n"
"color :rgba(255,255,255,230);\n"
"padding-bottom:7px;"));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(80, 230, 200, 40));
        lineEdit_2->setFont(font1);
        lineEdit_2->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0);\n"
"border:none;\n"
"border-bottom:2px solid rgba(105,118,132,255);\n"
"color :rgba(255,255,255,230);\n"
"padding-bottom:7px;"));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(80, 310, 200, 40));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        pushButton->setFont(font2);
        label_5 = new QLabel(widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 360, 180, 25));
        QFont font3;
        font3.setPointSize(8);
        label_5->setFont(font3);
        label_5->setStyleSheet(QString::fromUtf8("color:rgba(255,255,255,140);"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 395, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "Log In:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "  User Name", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MainWindow", "  Password", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "L o g In", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Forget your UserName or password ?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
