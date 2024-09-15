/********************************************************************************
** Form generated from reading UI file 'emp.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMP_H
#define UI_EMP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_emp
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *name;
    QWidget *widget_6;
    QGridLayout *gridLayout;
    QComboBox *type;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *save;
    QPushButton *search;
    QPushButton *delete_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QTableWidget *embtable;

    void setupUi(QWidget *emp)
    {
        if (emp->objectName().isEmpty())
            emp->setObjectName("emp");
        emp->resize(800, 600);
        emp->setMinimumSize(QSize(800, 600));
        emp->setMaximumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(emp);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(emp);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 200));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(widget_5);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        name = new QLineEdit(widget_5);
        name->setObjectName("name");

        horizontalLayout_2->addWidget(name);


        verticalLayout_2->addWidget(widget_5);

        widget_6 = new QWidget(widget_3);
        widget_6->setObjectName("widget_6");
        gridLayout = new QGridLayout(widget_6);
        gridLayout->setObjectName("gridLayout");
        type = new QComboBox(widget_6);
        type->addItem(QString());
        type->addItem(QString());
        type->setObjectName("type");

        gridLayout->addWidget(type, 0, 0, 1, 1);


        verticalLayout_2->addWidget(widget_6);


        horizontalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        save = new QPushButton(widget_4);
        save->setObjectName("save");
        save->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/diskette(1).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        save->setIcon(icon);

        verticalLayout_3->addWidget(save);

        search = new QPushButton(widget_4);
        search->setObjectName("search");
        search->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/interface.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        search->setIcon(icon1);

        verticalLayout_3->addWidget(search);

        delete_2 = new QPushButton(widget_4);
        delete_2->setObjectName("delete_2");
        delete_2->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/login/delete.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        delete_2->setIcon(icon2);

        verticalLayout_3->addWidget(delete_2);


        horizontalLayout->addWidget(widget_4);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(emp);
        widget_2->setObjectName("widget_2");
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        embtable = new QTableWidget(widget_2);
        embtable->setObjectName("embtable");

        horizontalLayout_3->addWidget(embtable);


        verticalLayout->addWidget(widget_2);


        retranslateUi(emp);

        QMetaObject::connectSlotsByName(emp);
    } // setupUi

    void retranslateUi(QWidget *emp)
    {
        emp->setWindowTitle(QCoreApplication::translate("emp", "Form", nullptr));
        label->setText(QCoreApplication::translate("emp", "Name:", nullptr));
        type->setItemText(0, QCoreApplication::translate("emp", "Sales", nullptr));
        type->setItemText(1, QCoreApplication::translate("emp", "Captain", nullptr));

        type->setCurrentText(QString());
        type->setPlaceholderText(QCoreApplication::translate("emp", "Select Employee type", nullptr));
        save->setText(QCoreApplication::translate("emp", "  Save ", nullptr));
        search->setText(QCoreApplication::translate("emp", "Search", nullptr));
        delete_2->setText(QCoreApplication::translate("emp", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class emp: public Ui_emp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMP_H
