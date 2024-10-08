/********************************************************************************
** Form generated from reading UI file 'dashboard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_H
#define UI_DASHBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dashboard
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *photo;
    QWidget *btns;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_2;
    QPushButton *safe;
    QPushButton *Emp;
    QPushButton *pack;
    QPushButton *User;
    QPushButton *ezn;
    QPushButton *sheet;

    void setupUi(QWidget *dashboard)
    {
        if (dashboard->objectName().isEmpty())
            dashboard->setObjectName("dashboard");
        dashboard->resize(1200, 800);
        dashboard->setMinimumSize(QSize(1200, 800));
        dashboard->setMaximumSize(QSize(1200, 800));
        QPalette palette;
        dashboard->setPalette(palette);
        dashboard->setStyleSheet(QString::fromUtf8("QLabel#photo{\n"
"background-color:#000;\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(dashboard);
        horizontalLayout->setObjectName("horizontalLayout");
        frame = new QFrame(dashboard);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        photo = new QLabel(frame);
        photo->setObjectName("photo");

        horizontalLayout_2->addWidget(photo);


        horizontalLayout->addWidget(frame);

        btns = new QWidget(dashboard);
        btns->setObjectName("btns");
        btns->setMinimumSize(QSize(200, 0));
        verticalLayout = new QVBoxLayout(btns);
        verticalLayout->setObjectName("verticalLayout");
        pushButton_2 = new QPushButton(btns);
        pushButton_2->setObjectName("pushButton_2");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMinimumSize(QSize(0, 40));
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        pushButton_2->setFont(font);
        pushButton_2->setLayoutDirection(Qt::RightToLeft);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/team.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pushButton_2->setIcon(icon);
        pushButton_2->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(pushButton_2);

        safe = new QPushButton(btns);
        safe->setObjectName("safe");
        sizePolicy1.setHeightForWidth(safe->sizePolicy().hasHeightForWidth());
        safe->setSizePolicy(sizePolicy1);
        safe->setMinimumSize(QSize(0, 40));
        safe->setFont(font);
        safe->setLayoutDirection(Qt::RightToLeft);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/safe.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        safe->setIcon(icon1);
        safe->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(safe);

        Emp = new QPushButton(btns);
        Emp->setObjectName("Emp");
        Emp->setMinimumSize(QSize(0, 40));
        Emp->setFont(font);
        Emp->setLayoutDirection(Qt::RightToLeft);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/login/employee.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Emp->setIcon(icon2);
        Emp->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(Emp);

        pack = new QPushButton(btns);
        pack->setObjectName("pack");
        sizePolicy1.setHeightForWidth(pack->sizePolicy().hasHeightForWidth());
        pack->setSizePolicy(sizePolicy1);
        pack->setMinimumSize(QSize(0, 40));
        pack->setFont(font);
        pack->setLayoutDirection(Qt::RightToLeft);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/login/new.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pack->setIcon(icon3);
        pack->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(pack);

        User = new QPushButton(btns);
        User->setObjectName("User");
        sizePolicy1.setHeightForWidth(User->sizePolicy().hasHeightForWidth());
        User->setSizePolicy(sizePolicy1);
        User->setMinimumSize(QSize(0, 40));
        User->setFont(font);
        User->setLayoutDirection(Qt::RightToLeft);
        User->setText(QString::fromUtf8("User  "));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/login/manager.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        User->setIcon(icon4);
        User->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(User);

        ezn = new QPushButton(btns);
        ezn->setObjectName("ezn");
        ezn->setMinimumSize(QSize(0, 40));
        ezn->setFont(font);
        ezn->setLayoutDirection(Qt::RightToLeft);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/login/cash-payment.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ezn->setIcon(icon5);
        ezn->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(ezn);

        sheet = new QPushButton(btns);
        sheet->setObjectName("sheet");
        sizePolicy1.setHeightForWidth(sheet->sizePolicy().hasHeightForWidth());
        sheet->setSizePolicy(sizePolicy1);
        sheet->setMinimumSize(QSize(0, 40));
        sheet->setFont(font);
        sheet->setLayoutDirection(Qt::RightToLeft);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/login/document.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        sheet->setIcon(icon6);
        sheet->setIconSize(QSize(36, 36));

        verticalLayout->addWidget(sheet);


        horizontalLayout->addWidget(btns);


        retranslateUi(dashboard);

        QMetaObject::connectSlotsByName(dashboard);
    } // setupUi

    void retranslateUi(QWidget *dashboard)
    {
        dashboard->setWindowTitle(QCoreApplication::translate("dashboard", "Dashboard", nullptr));
        photo->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("dashboard", "Member  ", nullptr));
        safe->setText(QCoreApplication::translate("dashboard", "    \330\247\331\204\330\256\330\262\331\206\330\251  ", nullptr));
        Emp->setText(QCoreApplication::translate("dashboard", "   Emp", nullptr));
        pack->setText(QCoreApplication::translate("dashboard", "New Package", nullptr));
        ezn->setText(QCoreApplication::translate("dashboard", "\330\247\330\260\331\206 \330\256\330\262\331\206\330\251", nullptr));
        sheet->setText(QCoreApplication::translate("dashboard", "Sheets  ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dashboard: public Ui_dashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_H
