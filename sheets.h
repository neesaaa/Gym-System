#ifndef SHEETS_H
#define SHEETS_H
#include <QButtonGroup>
#include <QRadioButton>
#include <QMessageBox>
#include <QWidget>
#include <QDebug>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
#include <QtSql>
#include <QFileDialog>



namespace Ui {
class sheets;
}

class sheets : public QWidget
{
    Q_OBJECT

public:
    explicit sheets(QWidget *parent = nullptr);
    ~sheets();
signals:
    void closed();
private slots:
    void onButtonToggled(QAbstractButton *button, bool checked);
    void print();
    void save();


    void r1_slot();
    void r2_slot();
    void r3_slot();
    void r4_slot();
    void r5_slot();
    void r6_slot();
    void r7_slot();
    void r8_slot();
    void r9_slot();
    void r10_slot();
    void r11_slot();

    void r1_save_slot();
    void r2_save_slot();
    void r3_save_slot();
    void r4_save_slot();
    void r5_save_slot();
    void r6_save_slot();
    void r7_save_slot();
    void r8_save_slot();
    void r9_save_slot();
    void r10_save_slot();
    void r11_save_slot();

    void updateFileNameExtension(const QString &selectedFilter);

protected:
    void closeEvent(QCloseEvent *event) override;


private:
    Ui::sheets *ui;
    QString result;
    QButtonGroup *buttonGroup;
    QRadioButton *lastSelectedRadioButton = nullptr;
    QSqlDatabase db;
    QFileDialog *dialog;
    bool isPDF=false;
};

#endif // SHEETS_H
