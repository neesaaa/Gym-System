#ifndef MEMBER_H
#define MEMBER_H

#include <QWidget>
#include <QCloseEvent>
#include <QEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTableWidget>
#include <QDate>


namespace Ui {
class Member;
}

class Member : public QWidget
{
    Q_OBJECT

public:
    explicit Member(QWidget *parent = nullptr);
    ~Member();
    void front_setter();
    void update_packages();
    void emplyee_capturred();

signals:
    void memberClosed();

private slots:
    void onSaveButtonClicked();
    void seearch(int i);
    void free_id();
    void deletee();
    void left();
    void right();
    void showwing();
    void pay_save();
    void delete_pay();
    void edit_pay();
    void onPaymentCellDoubleClicked(int row ,int column);
    void onalldoubleclicked(int row ,int column);

    void onPackComboBoxSelectionChanged(int index);
    void onPayDiscChanged(const QString &text);
    void pack_save();
    void pack_edit();
    void pack_delete();
    void clearRow(QTableWidget *tableWidget, int row);
    void updateEndDate(const QDate &startDate);
    void change_in_shift(int shift);
    void onCellClicked(int row, int column);
    void clear_data();

    void FreezeChangeDate(int);
    void freezezboxchange(QDate);
    void save_freeze_slot();
    void onFreezeTableDoubleClicked(int row ,int column);
    void edit_freeze();
    void delete_freeze();

    //pt
    void updatePtValue(const QString &itemName);
    void updatePtNet(const QString &discountText);
    void save_pt();
    void pt_table_select(QTableWidgetItem *item);
    void pt_edit();
    void onPtTableDoubleClicked(const QModelIndex &index);
    void pt_delete();
    void clear_tables();

    void save_inv();
    void on_invtable_doubleClicked(int row, int column);
    void inv_delete();
    void add_on_end_date();
protected:
    void closeEvent(QCloseEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

private:
    bool front=0;
    int package_id;
    int inv_id;
    int pack_idd_for_inv;
    int all_row;
    int duration_package;
    Ui::Member *ui;
    QSqlDatabase db;
    bool blockSignalsFlag;
    int freezing_id;
    int freeze_counts;
    int freeze_row;
    int pt_id;
    int pt_row;

};

#endif // MEMBER_H
