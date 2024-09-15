#ifndef EMP_H
#define EMP_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class emp;
}

class emp : public QWidget
{
    Q_OBJECT

public:
    explicit emp(QWidget *parent = nullptr);
    ~emp();
signals:
    void emp_closed();
    void employee();
protected:
    void closeEvent(QCloseEvent *event) override;
private slots:
    void searchAndUpdateTable();
    void onTableCellDoubleClicked(int row, int column);
    void del();
    void save();

private:
    Ui::emp *ui;
    QSqlDatabase db;
    int index=-1;

};

#endif // EMP_H
