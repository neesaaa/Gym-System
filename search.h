#ifndef SEARCH_H
#define SEARCH_H

#include <QWidget>
#include <QtSql>
#include <QKeyEvent>
namespace Ui {
class search;
}

class search : public QWidget
{
    Q_OBJECT

public:
    explicit search(QWidget *parent = nullptr);
    ~search();
signals:
    void closed(int id);  // Signal to emit when the window is closed

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override; // Add this line
private slots:
    void searching();
    void onCellClicked(int row, int column);
    void onCellDoubleClicked(int row, int column);

private:
    Ui::search *ui;
    QSqlDatabase db;
    int currentid=-1;

};

#endif // SEARCH_H
