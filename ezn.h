#ifndef EZN_H
#define EZN_H

#include <QWidget>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class ezn;
}

class ezn : public QWidget
{
    Q_OBJECT

public:
    explicit ezn(QWidget *parent = nullptr);
    ~ezn();
signals:
    void ezn_closed();
private slots:
    void save();
    void on_leftButton_clicked();
    void right();
    void deletee();
protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::ezn *ui;
};

#endif // EZN_H
