/********************************************************************************
** Form generated from reading UI file 'safe.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAFE_H
#define UI_SAFE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_safe
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *save;
    QPushButton *print;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QDateEdit *start;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QDateEdit *end;

    void setupUi(QWidget *safe)
    {
        if (safe->objectName().isEmpty())
            safe->setObjectName("safe");
        safe->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(4);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(safe->sizePolicy().hasHeightForWidth());
        safe->setSizePolicy(sizePolicy);
        safe->setMinimumSize(QSize(800, 600));
        safe->setMaximumSize(QSize(800, 600));
        verticalLayout = new QVBoxLayout(safe);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(safe);
        widget_2->setObjectName("widget_2");
        horizontalLayout_3 = new QHBoxLayout(widget_2);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(widget_2);
        label_3->setObjectName("label_3");
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/login/vecteezy_dark-image-of-a-steel-bank-vault_25272729(1).jpg")));
        label_3->setScaledContents(true);

        horizontalLayout_3->addWidget(label_3);


        verticalLayout->addWidget(widget_2);

        widget_5 = new QWidget(safe);
        widget_5->setObjectName("widget_5");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_5->sizePolicy().hasHeightForWidth());
        widget_5->setSizePolicy(sizePolicy1);
        widget_5->setMinimumSize(QSize(0, 68));
        widget_5->setMaximumSize(QSize(16777215, 68));
        horizontalLayout_2 = new QHBoxLayout(widget_5);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        save = new QPushButton(widget_5);
        save->setObjectName("save");
        save->setMinimumSize(QSize(130, 50));
        save->setMaximumSize(QSize(130, 50));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        save->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/safe-box.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        save->setIcon(icon);
        save->setIconSize(QSize(36, 36));

        horizontalLayout_2->addWidget(save);

        print = new QPushButton(widget_5);
        print->setObjectName("print");
        print->setMinimumSize(QSize(130, 50));
        print->setMaximumSize(QSize(130, 50));
        print->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/printer.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        print->setIcon(icon1);
        print->setIconSize(QSize(36, 36));

        horizontalLayout_2->addWidget(print);


        verticalLayout->addWidget(widget_5);

        widget = new QWidget(safe);
        widget->setObjectName("widget");
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget_3);
        label->setObjectName("label");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(0, 100));
        label->setMaximumSize(QSize(16777215, 100));
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        start = new QDateEdit(widget_3);
        start->setObjectName("start");

        verticalLayout_2->addWidget(start);


        horizontalLayout->addWidget(widget_3);

        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        verticalLayout_3 = new QVBoxLayout(widget_4);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(0, 100));
        label_2->setMaximumSize(QSize(16777215, 100));
        label_2->setFont(font);

        verticalLayout_3->addWidget(label_2);

        end = new QDateEdit(widget_4);
        end->setObjectName("end");

        verticalLayout_3->addWidget(end);


        horizontalLayout->addWidget(widget_4);


        verticalLayout->addWidget(widget);


        retranslateUi(safe);

        QMetaObject::connectSlotsByName(safe);
    } // setupUi

    void retranslateUi(QWidget *safe)
    {
        safe->setWindowTitle(QCoreApplication::translate("safe", "Form", nullptr));
        label_3->setText(QString());
        save->setText(QCoreApplication::translate("safe", "Save", nullptr));
        print->setText(QCoreApplication::translate("safe", "Print", nullptr));
        label->setText(QCoreApplication::translate("safe", "Start Date:", nullptr));
        label_2->setText(QCoreApplication::translate("safe", "End Date:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class safe: public Ui_safe {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAFE_H
