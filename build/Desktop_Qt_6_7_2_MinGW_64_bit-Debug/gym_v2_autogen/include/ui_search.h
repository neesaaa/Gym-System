/********************************************************************************
** Form generated from reading UI file 'search.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCH_H
#define UI_SEARCH_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_search
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *name;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *mob;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *search_2;
    QLabel *id_2;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QTableWidget *nas;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *prof;

    void setupUi(QWidget *search)
    {
        if (search->objectName().isEmpty())
            search->setObjectName("search");
        search->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(search->sizePolicy().hasHeightForWidth());
        search->setSizePolicy(sizePolicy);
        search->setMinimumSize(QSize(800, 600));
        search->setMaximumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(search);
        verticalLayout->setObjectName("verticalLayout");
        widget_6 = new QWidget(search);
        widget_6->setObjectName("widget_6");
        widget_6->setMaximumSize(QSize(16777215, 170));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        widget = new QWidget(widget_6);
        widget->setObjectName("widget");
        widget->setMaximumSize(QSize(16777215, 150));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget_3);
        label->setObjectName("label");
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(60, 16777215));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        name = new QLineEdit(widget_3);
        name->setObjectName("name");

        horizontalLayout->addWidget(name);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(60, 0));
        label_2->setMaximumSize(QSize(60, 16777215));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2);

        mob = new QLineEdit(widget_4);
        mob->setObjectName("mob");

        horizontalLayout_2->addWidget(mob);


        verticalLayout_2->addWidget(widget_4);


        horizontalLayout_4->addWidget(widget);

        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName("widget_7");
        horizontalLayout_5 = new QHBoxLayout(widget_7);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        search_2 = new QPushButton(widget_7);
        search_2->setObjectName("search_2");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/magnifier.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        search_2->setIcon(icon);
        search_2->setIconSize(QSize(32, 32));

        horizontalLayout_5->addWidget(search_2);

        id_2 = new QLabel(widget_7);
        id_2->setObjectName("id_2");
        id_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(id_2);


        horizontalLayout_4->addWidget(widget_7);


        verticalLayout->addWidget(widget_6);

        widget_2 = new QWidget(search);
        widget_2->setObjectName("widget_2");
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        nas = new QTableWidget(widget_2);
        nas->setObjectName("nas");
        nas->setMinimumSize(QSize(500, 0));
        nas->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_6->addWidget(nas);

        widget_8 = new QWidget(widget_2);
        widget_8->setObjectName("widget_8");
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        prof = new QLabel(widget_8);
        prof->setObjectName("prof");
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        prof->setFont(font1);
        prof->setAlignment(Qt::AlignCenter);

        horizontalLayout_7->addWidget(prof);


        horizontalLayout_6->addWidget(widget_8);


        verticalLayout->addWidget(widget_2);


        retranslateUi(search);

        QMetaObject::connectSlotsByName(search);
    } // setupUi

    void retranslateUi(QWidget *search)
    {
        search->setWindowTitle(QCoreApplication::translate("search", "Form", nullptr));
        label->setText(QCoreApplication::translate("search", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("search", "mob:", nullptr));
        search_2->setText(QCoreApplication::translate("search", "Search", nullptr));
        id_2->setText(QCoreApplication::translate("search", "one click to load", nullptr));
        prof->setText(QCoreApplication::translate("search", "one click load profile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class search: public Ui_search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_H
