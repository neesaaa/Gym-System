#ifndef SAFE_H
#define SAFE_H

#include <QWidget>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QtSql>
#include <QFileDialog>


namespace Ui {
class safe;
}

class safe : public QWidget
{
    Q_OBJECT

public:
    explicit safe(QWidget *parent = nullptr);
    ~safe();
signals:
    void safe_closed();
private slots:
    void print();
    void saveQueryResults();
    void saveAsCsv(QSqlQuery& query, const QString& fileName);
    void saveAsPdf(QSqlQuery& query, const QString& fileName);
    void updateFileNameExtension(const QString &selectedFilter);
protected:
    void closeEvent(QCloseEvent *event) override;
private:
    Ui::safe *ui;
    QSqlDatabase db;
    QFileDialog *dialog; // Private attribute for QFileDialog

};

#endif // SAFE_H
