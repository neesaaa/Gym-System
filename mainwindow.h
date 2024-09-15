#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void keyPressEvent(QKeyEvent *event) override; // Add this line
signals :
    void ended_admin();
    void ended_user();
private slots:
    void Login();

private:
    Ui::MainWindow *ui;
    QSqlDatabase db;
};
#endif // MAINWINDOW_H
