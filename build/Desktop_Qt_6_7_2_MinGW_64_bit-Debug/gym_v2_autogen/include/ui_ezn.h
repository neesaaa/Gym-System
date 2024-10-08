/********************************************************************************
** Form generated from reading UI file 'ezn.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EZN_H
#define UI_EZN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ezn
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QDateEdit *date;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *type;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QLineEdit *price;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QTextEdit *note;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *save;
    QPushButton *del;
    QPushButton *left;
    QPushButton *right;

    void setupUi(QWidget *ezn)
    {
        if (ezn->objectName().isEmpty())
            ezn->setObjectName("ezn");
        ezn->resize(700, 400);
        ezn->setMinimumSize(QSize(700, 400));
        ezn->setMaximumSize(QSize(700, 400));
        verticalLayout = new QVBoxLayout(ezn);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(ezn);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(widget_4);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_2->addWidget(label);

        date = new QDateEdit(widget_4);
        date->setObjectName("date");
        date->setMinimumSize(QSize(260, 0));
        date->setMaximumSize(QSize(250, 16777215));
        QFont font1;
        font1.setPointSize(10);
        date->setFont(font1);

        horizontalLayout_2->addWidget(date, 0, Qt::AlignLeft);


        horizontalLayout->addWidget(widget_4);

        widget_5 = new QWidget(widget);
        widget_5->setObjectName("widget_5");
        horizontalLayout_3 = new QHBoxLayout(widget_5);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(widget_5);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout_3->addWidget(label_2, 0, Qt::AlignLeft);

        type = new QComboBox(widget_5);
        type->addItem(QString());
        type->addItem(QString());
        type->addItem(QString());
        type->addItem(QString());
        type->addItem(QString());
        type->setObjectName("type");
        type->setMinimumSize(QSize(260, 0));
        type->setMaximumSize(QSize(250, 16777215));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setItalic(false);
        type->setFont(font2);

        horizontalLayout_3->addWidget(type, 0, Qt::AlignLeft);


        horizontalLayout->addWidget(widget_5);


        verticalLayout->addWidget(widget);

        widget_2 = new QWidget(ezn);
        widget_2->setObjectName("widget_2");
        horizontalLayout_4 = new QHBoxLayout(widget_2);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        horizontalLayout_4->addWidget(label_3);

        price = new QLineEdit(widget_2);
        price->setObjectName("price");

        horizontalLayout_4->addWidget(price);


        verticalLayout->addWidget(widget_2);

        widget_3 = new QWidget(ezn);
        widget_3->setObjectName("widget_3");
        horizontalLayout_5 = new QHBoxLayout(widget_3);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(widget_3);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        horizontalLayout_5->addWidget(label_4, 0, Qt::AlignTop);

        note = new QTextEdit(widget_3);
        note->setObjectName("note");

        horizontalLayout_5->addWidget(note);


        verticalLayout->addWidget(widget_3);

        widget_6 = new QWidget(ezn);
        widget_6->setObjectName("widget_6");
        horizontalLayout_6 = new QHBoxLayout(widget_6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        save = new QPushButton(widget_6);
        save->setObjectName("save");
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(true);
        save->setFont(font3);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/diskette.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        save->setIcon(icon);

        horizontalLayout_6->addWidget(save);

        del = new QPushButton(widget_6);
        del->setObjectName("del");
        del->setFont(font3);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/delete(2).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        del->setIcon(icon1);

        horizontalLayout_6->addWidget(del);

        left = new QPushButton(widget_6);
        left->setObjectName("left");
        left->setMinimumSize(QSize(60, 40));
        left->setMaximumSize(QSize(60, 40));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/login/left_arrow.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        left->setIcon(icon2);
        left->setIconSize(QSize(20, 20));

        horizontalLayout_6->addWidget(left);

        right = new QPushButton(widget_6);
        right->setObjectName("right");
        right->setMinimumSize(QSize(60, 40));
        right->setMaximumSize(QSize(60, 40));
        right->setFont(font3);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/login/right_arrow.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        right->setIcon(icon3);
        right->setIconSize(QSize(40, 20));

        horizontalLayout_6->addWidget(right);


        verticalLayout->addWidget(widget_6);


        retranslateUi(ezn);

        QMetaObject::connectSlotsByName(ezn);
    } // setupUi

    void retranslateUi(QWidget *ezn)
    {
        ezn->setWindowTitle(QCoreApplication::translate("ezn", "Form", nullptr));
        label->setText(QCoreApplication::translate("ezn", "Date:", nullptr));
        label_2->setText(QCoreApplication::translate("ezn", "Type:", nullptr));
        type->setItemText(0, QCoreApplication::translate("ezn", "Cash", nullptr));
        type->setItemText(1, QCoreApplication::translate("ezn", "Credit", nullptr));
        type->setItemText(2, QCoreApplication::translate("ezn", "Valu", nullptr));
        type->setItemText(3, QCoreApplication::translate("ezn", "Vodafone", nullptr));
        type->setItemText(4, QCoreApplication::translate("ezn", "Fawary", nullptr));

        label_3->setText(QCoreApplication::translate("ezn", "Price:", nullptr));
        label_4->setText(QCoreApplication::translate("ezn", "Note:", nullptr));
        save->setText(QCoreApplication::translate("ezn", "Save", nullptr));
        del->setText(QCoreApplication::translate("ezn", "Delete", nullptr));
        left->setText(QString());
        right->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ezn: public Ui_ezn {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EZN_H
