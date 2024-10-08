#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QWidget>

namespace Ui {
class dashboard;
}

class dashboard : public QWidget
{
    Q_OBJECT

public:
    explicit dashboard(QWidget *parent = nullptr,bool is_admin=false);
    ~dashboard();
    void setAdminMode(bool is_admin);
    void user_enable();
    void pack_closed();
    void safe_enable();
    void open_sheet();
    void open_emp();
    void emp_open();
    void ezn_enaple();


signals:
    void membeer();
    void user();
    void package();
    void safe();
    void sheets();
    void emp();
    void ezn_khazna();

    void disableButtons_signal();
    void memberClosedSignal();
    void user_closed();
    // void pack_closeddd();

private slots:
    void member_slot();
    void user_slot();
    void pack_slot();
    void member_enable();
    void disableButtons();
    void safe_click();
    void sheet_click();
    void ezn_slot();
public:
    Ui::dashboard *ui;
};

#endif // DASHBOARD_H
