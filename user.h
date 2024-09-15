#ifndef USER_H
#define USER_H

#include <QWidget>
#include <QtSql/QSqlDatabase>

namespace Ui {
class user;
}

class user : public QWidget
{
    Q_OBJECT

public:
    explicit user(QWidget *parent = nullptr);
    ~user();
signals :
    void closed_user();
private slots:
    void save_clicked();
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::user *ui;
    QSqlDatabase db;
};

#endif // USER_H
