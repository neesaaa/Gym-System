/********************************************************************************
** Form generated from reading UI file 'user.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USER_H
#define UI_USER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_user
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label;
    QLineEdit *name;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *pass;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *pass_2;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QRadioButton *admin;

    void setupUi(QWidget *user)
    {
        if (user->objectName().isEmpty())
            user->setObjectName("user");
        user->resize(726, 400);
        user->setMinimumSize(QSize(700, 400));
        user->setMaximumSize(QSize(726, 400));
        verticalLayout = new QVBoxLayout(user);
        verticalLayout->setObjectName("verticalLayout");
        widget_2 = new QWidget(user);
        widget_2->setObjectName("widget_2");
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(widget_3);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(160, 0));
        label->setMaximumSize(QSize(160, 16777215));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_3->addWidget(label, 0, Qt::AlignLeft);

        name = new QLineEdit(widget_3);
        name->setObjectName("name");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(name->sizePolicy().hasHeightForWidth());
        name->setSizePolicy(sizePolicy1);
        name->setMinimumSize(QSize(500, 0));
        name->setMaximumSize(QSize(500, 16777215));

        horizontalLayout_3->addWidget(name, 0, Qt::AlignRight);


        verticalLayout_2->addWidget(widget_3);

        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName("widget_4");
        horizontalLayout_2 = new QHBoxLayout(widget_4);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(2, 2, 2, 2);
        label_2 = new QLabel(widget_4);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(160, 0));
        label_2->setMaximumSize(QSize(160, 16777215));
        label_2->setFont(font);

        horizontalLayout_2->addWidget(label_2, 0, Qt::AlignLeft);

        pass = new QLineEdit(widget_4);
        pass->setObjectName("pass");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pass->sizePolicy().hasHeightForWidth());
        pass->setSizePolicy(sizePolicy2);
        pass->setMinimumSize(QSize(500, 0));
        pass->setMaximumSize(QSize(500, 16777215));
        pass->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(pass, 0, Qt::AlignRight);


        verticalLayout_2->addWidget(widget_4);

        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName("widget_5");
        horizontalLayout = new QHBoxLayout(widget_5);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(2, 2, 2, 2);
        label_3 = new QLabel(widget_5);
        label_3->setObjectName("label_3");
        label_3->setMinimumSize(QSize(160, 0));
        label_3->setMaximumSize(QSize(160, 16777215));
        label_3->setFont(font);

        horizontalLayout->addWidget(label_3);

        pass_2 = new QLineEdit(widget_5);
        pass_2->setObjectName("pass_2");
        sizePolicy2.setHeightForWidth(pass_2->sizePolicy().hasHeightForWidth());
        pass_2->setSizePolicy(sizePolicy2);
        pass_2->setMinimumSize(QSize(500, 0));
        pass_2->setMaximumSize(QSize(500, 16777215));
        pass_2->setEchoMode(QLineEdit::Password);

        horizontalLayout->addWidget(pass_2, 0, Qt::AlignRight);


        verticalLayout_2->addWidget(widget_5);


        verticalLayout->addWidget(widget_2);

        widget_6 = new QWidget(user);
        widget_6->setObjectName("widget_6");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Minimum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget_6->sizePolicy().hasHeightForWidth());
        widget_6->setSizePolicy(sizePolicy3);
        widget_6->setMinimumSize(QSize(0, 100));
        widget_6->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_4 = new QHBoxLayout(widget_6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton = new QPushButton(widget_6);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(200, 0));
        pushButton->setMaximumSize(QSize(200, 16777215));
        QFont font1;
        font1.setPointSize(16);
        font1.setBold(true);
        pushButton->setFont(font1);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/diskette(1).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(32, 32));

        horizontalLayout_4->addWidget(pushButton);

        admin = new QRadioButton(widget_6);
        admin->setObjectName("admin");
        sizePolicy2.setHeightForWidth(admin->sizePolicy().hasHeightForWidth());
        admin->setSizePolicy(sizePolicy2);
        admin->setFont(font1);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/admin.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        admin->setIcon(icon1);
        admin->setIconSize(QSize(32, 32));
        admin->setChecked(false);

        horizontalLayout_4->addWidget(admin);


        verticalLayout->addWidget(widget_6);


        retranslateUi(user);

        QMetaObject::connectSlotsByName(user);
    } // setupUi

    void retranslateUi(QWidget *user)
    {
        user->setWindowTitle(QCoreApplication::translate("user", "Form", nullptr));
        label->setText(QCoreApplication::translate("user", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("user", "New Password:", nullptr));
        pass->setPlaceholderText(QCoreApplication::translate("user", "     Four char is the minimum", nullptr));
        label_3->setText(QCoreApplication::translate("user", "Password  Check:", nullptr));
        pass_2->setPlaceholderText(QString());
        pushButton->setText(QCoreApplication::translate("user", "  Save", nullptr));
        admin->setText(QCoreApplication::translate("user", "  Admin", nullptr));
    } // retranslateUi

};

namespace Ui {
    class user: public Ui_user {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USER_H
