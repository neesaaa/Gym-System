#ifndef PACKAGES_H
#define PACKAGES_H

#include <QWidget>
#include <QtSql>

namespace Ui {
class packages;
}

class packages : public QWidget
{
    Q_OBJECT

public:
    explicit packages(QWidget *parent = nullptr);
    ~packages();
signals:
    void pack_closed();
    void added();
private slots:
    void pack_save();
    void pack_edit();
    void pack_search();
    void pack_delete();
    void clearData();
    void pt_save();
    void pt_search();
    void pt_edit();
    void pt_delete();
    void clearData_pt();
    void updateIcon();

protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::packages *ui;
    QSqlDatabase db;
    int pack_id;
    int pt_id;
};

#endif // PACKAGES_H
