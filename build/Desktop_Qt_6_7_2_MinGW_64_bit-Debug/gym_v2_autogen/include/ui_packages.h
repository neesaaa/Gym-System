/********************************************************************************
** Form generated from reading UI file 'packages.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKAGES_H
#define UI_PACKAGES_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_packages
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QLineEdit *name;
    QWidget *widget_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSpinBox *count;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_3;
    QLineEdit *price;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QSpinBox *duration;
    QWidget *widget_25;
    QHBoxLayout *horizontalLayout_18;
    QRadioButton *active;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QWidget *widget_9;
    QVBoxLayout *verticalLayout_7;
    QWidget *widget_13;
    QHBoxLayout *horizontalLayout_8;
    QTableWidget *pack_table;
    QLabel *label_5;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget_11;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pack_save;
    QPushButton *pack_search;
    QWidget *widget_12;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pack_edit;
    QPushButton *pack_delete;
    QWidget *widget_26;
    QHBoxLayout *horizontalLayout_17;
    QWidget *widget_24;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_5;
    QWidget *widget_14;
    QHBoxLayout *horizontalLayout_9;
    QWidget *widget_16;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_6;
    QLineEdit *name_pt;
    QWidget *widget_17;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_7;
    QSpinBox *count_pt;
    QWidget *widget_18;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QLineEdit *price_pt;
    QWidget *widget_19;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_9;
    QSpinBox *pt;
    QWidget *widget_15;
    QHBoxLayout *horizontalLayout_15;
    QWidget *widget_23;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_10;
    QWidget *widget_20;
    QHBoxLayout *horizontalLayout_14;
    QWidget *widget_21;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pt_save;
    QPushButton *pt_search;
    QWidget *widget_22;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pt_edit;
    QPushButton *pt_delete;

    void setupUi(QWidget *packages)
    {
        if (packages->objectName().isEmpty())
            packages->setObjectName("packages");
        packages->resize(1200, 800);
        packages->setMinimumSize(QSize(1200, 800));
        packages->setMaximumSize(QSize(1200, 801));
        verticalLayout = new QVBoxLayout(packages);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(packages);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        widget_4 = new QWidget(widget);
        widget_4->setObjectName("widget_4");
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_5 = new QWidget(widget_4);
        widget_5->setObjectName("widget_5");
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label = new QLabel(widget_5);
        label->setObjectName("label");
        label->setMinimumSize(QSize(60, 0));
        label->setMaximumSize(QSize(50, 16777215));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);

        horizontalLayout_4->addWidget(label);

        name = new QLineEdit(widget_5);
        name->setObjectName("name");
        name->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_4->addWidget(name);


        horizontalLayout->addWidget(widget_5);

        widget_6 = new QWidget(widget_4);
        widget_6->setObjectName("widget_6");
        horizontalLayout_5 = new QHBoxLayout(widget_6);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_2 = new QLabel(widget_6);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        horizontalLayout_5->addWidget(label_2);

        count = new QSpinBox(widget_6);
        count->setObjectName("count");
        count->setMinimumSize(QSize(100, 0));
        count->setMinimum(-1);
        count->setMaximum(9999999);

        horizontalLayout_5->addWidget(count);


        horizontalLayout->addWidget(widget_6);

        widget_7 = new QWidget(widget_4);
        widget_7->setObjectName("widget_7");
        horizontalLayout_6 = new QHBoxLayout(widget_7);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        label_3 = new QLabel(widget_7);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        horizontalLayout_6->addWidget(label_3);

        price = new QLineEdit(widget_7);
        price->setObjectName("price");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(price->sizePolicy().hasHeightForWidth());
        price->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(price);


        horizontalLayout->addWidget(widget_7);

        widget_8 = new QWidget(widget_4);
        widget_8->setObjectName("widget_8");
        horizontalLayout_7 = new QHBoxLayout(widget_8);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_4 = new QLabel(widget_8);
        label_4->setObjectName("label_4");
        label_4->setFont(font);

        horizontalLayout_7->addWidget(label_4);

        duration = new QSpinBox(widget_8);
        duration->setObjectName("duration");
        duration->setMinimumSize(QSize(100, 0));
        duration->setMinimum(1);
        duration->setMaximum(99999999);

        horizontalLayout_7->addWidget(duration);

        widget_25 = new QWidget(widget_8);
        widget_25->setObjectName("widget_25");
        horizontalLayout_18 = new QHBoxLayout(widget_25);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        active = new QRadioButton(widget_25);
        active->setObjectName("active");
        active->setFont(font);

        horizontalLayout_18->addWidget(active);


        horizontalLayout_7->addWidget(widget_25);


        horizontalLayout->addWidget(widget_8);


        verticalLayout_2->addWidget(widget_4);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName("widget_3");
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName("widget_9");
        verticalLayout_7 = new QVBoxLayout(widget_9);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(2, -1, 2, -1);
        widget_13 = new QWidget(widget_9);
        widget_13->setObjectName("widget_13");
        horizontalLayout_8 = new QHBoxLayout(widget_13);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        pack_table = new QTableWidget(widget_13);
        if (pack_table->columnCount() < 5)
            pack_table->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        pack_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        pack_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        pack_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        pack_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        pack_table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        if (pack_table->rowCount() < 1)
            pack_table->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        pack_table->setVerticalHeaderItem(0, __qtablewidgetitem5);
        pack_table->setObjectName("pack_table");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pack_table->sizePolicy().hasHeightForWidth());
        pack_table->setSizePolicy(sizePolicy1);
        pack_table->setMaximumSize(QSize(800, 70));

        horizontalLayout_8->addWidget(pack_table);


        verticalLayout_7->addWidget(widget_13);

        label_5 = new QLabel(widget_9);
        label_5->setObjectName("label_5");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Latin Modern Roman Demi")});
        font1.setPointSize(20);
        font1.setBold(true);
        label_5->setFont(font1);
        label_5->setLayoutDirection(Qt::LeftToRight);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_5);


        horizontalLayout_2->addWidget(widget_9);

        widget_10 = new QWidget(widget_3);
        widget_10->setObjectName("widget_10");
        sizePolicy2.setHeightForWidth(widget_10->sizePolicy().hasHeightForWidth());
        widget_10->setSizePolicy(sizePolicy2);
        widget_10->setMinimumSize(QSize(500, 0));
        widget_10->setMaximumSize(QSize(500, 16777215));
        horizontalLayout_3 = new QHBoxLayout(widget_10);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        widget_11 = new QWidget(widget_10);
        widget_11->setObjectName("widget_11");
        verticalLayout_3 = new QVBoxLayout(widget_11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        pack_save = new QPushButton(widget_11);
        pack_save->setObjectName("pack_save");
        sizePolicy1.setHeightForWidth(pack_save->sizePolicy().hasHeightForWidth());
        pack_save->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setBold(true);
        pack_save->setFont(font2);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/login/floppy-disk.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pack_save->setIcon(icon);
        pack_save->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(pack_save);

        pack_search = new QPushButton(widget_11);
        pack_search->setObjectName("pack_search");
        sizePolicy1.setHeightForWidth(pack_search->sizePolicy().hasHeightForWidth());
        pack_search->setSizePolicy(sizePolicy1);
        pack_search->setFont(font2);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/login/interface.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pack_search->setIcon(icon1);
        pack_search->setIconSize(QSize(32, 32));

        verticalLayout_3->addWidget(pack_search);


        horizontalLayout_3->addWidget(widget_11);

        widget_12 = new QWidget(widget_10);
        widget_12->setObjectName("widget_12");
        verticalLayout_4 = new QVBoxLayout(widget_12);
        verticalLayout_4->setObjectName("verticalLayout_4");
        pack_edit = new QPushButton(widget_12);
        pack_edit->setObjectName("pack_edit");
        sizePolicy1.setHeightForWidth(pack_edit->sizePolicy().hasHeightForWidth());
        pack_edit->setSizePolicy(sizePolicy1);
        pack_edit->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/login/written-paper.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pack_edit->setIcon(icon2);
        pack_edit->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pack_edit);

        pack_delete = new QPushButton(widget_12);
        pack_delete->setObjectName("pack_delete");
        sizePolicy1.setHeightForWidth(pack_delete->sizePolicy().hasHeightForWidth());
        pack_delete->setSizePolicy(sizePolicy1);
        pack_delete->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/login/trash.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pack_delete->setIcon(icon3);
        pack_delete->setIconSize(QSize(32, 32));

        verticalLayout_4->addWidget(pack_delete);


        horizontalLayout_3->addWidget(widget_12);


        horizontalLayout_2->addWidget(widget_10);


        verticalLayout_2->addWidget(widget_3);


        verticalLayout->addWidget(widget);

        widget_26 = new QWidget(packages);
        widget_26->setObjectName("widget_26");
        widget_26->setMaximumSize(QSize(16777215, 60));
        horizontalLayout_17 = new QHBoxLayout(widget_26);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        widget_24 = new QWidget(widget_26);
        widget_24->setObjectName("widget_24");

        horizontalLayout_17->addWidget(widget_24);


        verticalLayout->addWidget(widget_26);

        widget_2 = new QWidget(packages);
        widget_2->setObjectName("widget_2");
        verticalLayout_5 = new QVBoxLayout(widget_2);
        verticalLayout_5->setObjectName("verticalLayout_5");
        widget_14 = new QWidget(widget_2);
        widget_14->setObjectName("widget_14");
        sizePolicy2.setHeightForWidth(widget_14->sizePolicy().hasHeightForWidth());
        widget_14->setSizePolicy(sizePolicy2);
        horizontalLayout_9 = new QHBoxLayout(widget_14);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        widget_16 = new QWidget(widget_14);
        widget_16->setObjectName("widget_16");
        horizontalLayout_10 = new QHBoxLayout(widget_16);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        label_6 = new QLabel(widget_16);
        label_6->setObjectName("label_6");
        label_6->setMinimumSize(QSize(60, 0));
        label_6->setMaximumSize(QSize(50, 16777215));
        label_6->setFont(font);

        horizontalLayout_10->addWidget(label_6);

        name_pt = new QLineEdit(widget_16);
        name_pt->setObjectName("name_pt");
        name_pt->setMaximumSize(QSize(300, 16777215));

        horizontalLayout_10->addWidget(name_pt);


        horizontalLayout_9->addWidget(widget_16);

        widget_17 = new QWidget(widget_14);
        widget_17->setObjectName("widget_17");
        horizontalLayout_11 = new QHBoxLayout(widget_17);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_7 = new QLabel(widget_17);
        label_7->setObjectName("label_7");
        label_7->setFont(font);

        horizontalLayout_11->addWidget(label_7);

        count_pt = new QSpinBox(widget_17);
        count_pt->setObjectName("count_pt");
        count_pt->setMinimumSize(QSize(100, 0));
        count_pt->setMinimum(-1);
        count_pt->setMaximum(9999999);

        horizontalLayout_11->addWidget(count_pt);


        horizontalLayout_9->addWidget(widget_17);

        widget_18 = new QWidget(widget_14);
        widget_18->setObjectName("widget_18");
        horizontalLayout_12 = new QHBoxLayout(widget_18);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_8 = new QLabel(widget_18);
        label_8->setObjectName("label_8");
        label_8->setFont(font);

        horizontalLayout_12->addWidget(label_8);

        price_pt = new QLineEdit(widget_18);
        price_pt->setObjectName("price_pt");

        horizontalLayout_12->addWidget(price_pt);


        horizontalLayout_9->addWidget(widget_18);

        widget_19 = new QWidget(widget_14);
        widget_19->setObjectName("widget_19");
        horizontalLayout_13 = new QHBoxLayout(widget_19);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        label_9 = new QLabel(widget_19);
        label_9->setObjectName("label_9");
        label_9->setFont(font);

        horizontalLayout_13->addWidget(label_9);

        pt = new QSpinBox(widget_19);
        pt->setObjectName("pt");
        pt->setMinimumSize(QSize(100, 0));
        pt->setMinimum(1);
        pt->setMaximum(99999999);

        horizontalLayout_13->addWidget(pt);


        horizontalLayout_9->addWidget(widget_19);


        verticalLayout_5->addWidget(widget_14);

        widget_15 = new QWidget(widget_2);
        widget_15->setObjectName("widget_15");
        horizontalLayout_15 = new QHBoxLayout(widget_15);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        widget_23 = new QWidget(widget_15);
        widget_23->setObjectName("widget_23");
        horizontalLayout_16 = new QHBoxLayout(widget_23);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        label_10 = new QLabel(widget_23);
        label_10->setObjectName("label_10");
        sizePolicy2.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy2);
        label_10->setMinimumSize(QSize(0, 50));
        label_10->setMaximumSize(QSize(16777215, 50));
        label_10->setFont(font1);
        label_10->setLayoutDirection(Qt::LeftToRight);
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_16->addWidget(label_10);


        horizontalLayout_15->addWidget(widget_23);

        widget_20 = new QWidget(widget_15);
        widget_20->setObjectName("widget_20");
        sizePolicy2.setHeightForWidth(widget_20->sizePolicy().hasHeightForWidth());
        widget_20->setSizePolicy(sizePolicy2);
        widget_20->setMinimumSize(QSize(500, 0));
        widget_20->setMaximumSize(QSize(500, 16777215));
        horizontalLayout_14 = new QHBoxLayout(widget_20);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        widget_21 = new QWidget(widget_20);
        widget_21->setObjectName("widget_21");
        verticalLayout_6 = new QVBoxLayout(widget_21);
        verticalLayout_6->setObjectName("verticalLayout_6");
        pt_save = new QPushButton(widget_21);
        pt_save->setObjectName("pt_save");
        sizePolicy1.setHeightForWidth(pt_save->sizePolicy().hasHeightForWidth());
        pt_save->setSizePolicy(sizePolicy1);
        pt_save->setFont(font2);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/login/floppy-disk(2).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pt_save->setIcon(icon4);
        pt_save->setIconSize(QSize(32, 32));

        verticalLayout_6->addWidget(pt_save);

        pt_search = new QPushButton(widget_21);
        pt_search->setObjectName("pt_search");
        sizePolicy1.setHeightForWidth(pt_search->sizePolicy().hasHeightForWidth());
        pt_search->setSizePolicy(sizePolicy1);
        pt_search->setFont(font2);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/login/magnifier.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pt_search->setIcon(icon5);
        pt_search->setIconSize(QSize(32, 32));

        verticalLayout_6->addWidget(pt_search);


        horizontalLayout_14->addWidget(widget_21);

        widget_22 = new QWidget(widget_20);
        widget_22->setObjectName("widget_22");
        verticalLayout_8 = new QVBoxLayout(widget_22);
        verticalLayout_8->setObjectName("verticalLayout_8");
        pt_edit = new QPushButton(widget_22);
        pt_edit->setObjectName("pt_edit");
        sizePolicy1.setHeightForWidth(pt_edit->sizePolicy().hasHeightForWidth());
        pt_edit->setSizePolicy(sizePolicy1);
        pt_edit->setFont(font2);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/login/pencil.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pt_edit->setIcon(icon6);
        pt_edit->setIconSize(QSize(32, 32));

        verticalLayout_8->addWidget(pt_edit);

        pt_delete = new QPushButton(widget_22);
        pt_delete->setObjectName("pt_delete");
        sizePolicy1.setHeightForWidth(pt_delete->sizePolicy().hasHeightForWidth());
        pt_delete->setSizePolicy(sizePolicy1);
        pt_delete->setFont(font2);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/login/delete(2).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        pt_delete->setIcon(icon7);
        pt_delete->setIconSize(QSize(32, 32));

        verticalLayout_8->addWidget(pt_delete);


        horizontalLayout_14->addWidget(widget_22);


        horizontalLayout_15->addWidget(widget_20);


        verticalLayout_5->addWidget(widget_15);


        verticalLayout->addWidget(widget_2);


        retranslateUi(packages);

        QMetaObject::connectSlotsByName(packages);
    } // setupUi

    void retranslateUi(QWidget *packages)
    {
        packages->setWindowTitle(QCoreApplication::translate("packages", "Form", nullptr));
        label->setText(QCoreApplication::translate("packages", "Name:", nullptr));
        label_2->setText(QCoreApplication::translate("packages", "Count:", nullptr));
        label_3->setText(QCoreApplication::translate("packages", "Price:", nullptr));
        label_4->setText(QCoreApplication::translate("packages", "Duration:", nullptr));
        active->setText(QCoreApplication::translate("packages", "Active", nullptr));
        QTableWidgetItem *___qtablewidgetitem = pack_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("packages", "Inbody", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = pack_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("packages", "Spa", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = pack_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("packages", "Inv", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = pack_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("packages", "Freeze", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = pack_table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("packages", "pt", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = pack_table->verticalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("packages", "Fill values", nullptr));
        label_5->setText(QCoreApplication::translate("packages", "New Package", nullptr));
        pack_save->setText(QCoreApplication::translate("packages", "  Save", nullptr));
        pack_search->setText(QCoreApplication::translate("packages", "Search", nullptr));
        pack_edit->setText(QCoreApplication::translate("packages", " Edit", nullptr));
        pack_delete->setText(QCoreApplication::translate("packages", "Delete", nullptr));
        label_6->setText(QCoreApplication::translate("packages", "Name:", nullptr));
        label_7->setText(QCoreApplication::translate("packages", "Count:", nullptr));
        label_8->setText(QCoreApplication::translate("packages", "Price:", nullptr));
        label_9->setText(QCoreApplication::translate("packages", "pt:", nullptr));
        label_10->setText(QCoreApplication::translate("packages", "New PT", nullptr));
        pt_save->setText(QCoreApplication::translate("packages", "  Save", nullptr));
        pt_search->setText(QCoreApplication::translate("packages", "Search", nullptr));
        pt_edit->setText(QCoreApplication::translate("packages", " Edit", nullptr));
        pt_delete->setText(QCoreApplication::translate("packages", "Delete", nullptr));
    } // retranslateUi

};

namespace Ui {
    class packages: public Ui_packages {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKAGES_H
