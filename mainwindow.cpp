#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QGraphicsDropShadowEffect>
#include <QColor>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QString>
#include<QShortcut>
#include <QKeyEvent>
#include <QRandomGenerator>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    QGraphicsDropShadowEffect *labelShadow = new QGraphicsDropShadowEffect(this);
    labelShadow->setBlurRadius(25);
    labelShadow->setOffset(0, 0);
    labelShadow->setColor(QColor(234, 221, 186, 100));
    ui->label->setGraphicsEffect(labelShadow);

    // Set drop shadow effect for label_3
    QGraphicsDropShadowEffect *label3Shadow = new QGraphicsDropShadowEffect(this);
    label3Shadow->setBlurRadius(25);
    label3Shadow->setOffset(0, 0);
    label3Shadow->setColor(QColor(105, 118, 132, 100));
    ui->label_3->setGraphicsEffect(label3Shadow);

    // Set drop shadow effect for pushButton
    QGraphicsDropShadowEffect *buttonShadow = new QGraphicsDropShadowEffect(this);
    buttonShadow->setBlurRadius(25);
    buttonShadow->setOffset(3, 3);
    buttonShadow->setColor(QColor(105, 118, 132, 100));
    ui->pushButton->setGraphicsEffect(buttonShadow);

    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    // activefitness
    // db.setDatabaseName("DRIVER={ODBC Driver 11 for SQL Server};"
    //                    "SERVER=DESKTOP-2N8D06C;"
    //                    "DATABASE=skymini;"
    //                    "UID=sa;"
    //                    "PWD=p@ssw0rd");
    //me
    // db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};"
    //                    "SERVER=LAPTOP-ONHG8FN6;"
    //                    "DATABASE=zktecho;"
    //                    "UID=nesa;"
    //                    "PWD=123698745");
    // xhale
    // db.setDatabaseName("DRIVER={SQL Server};"
    //                    "SERVER=DESKTOP-9L5QUCK;"
    //                    "DATABASE=Number1;"
    //                    "UID=sa;"
    //                    "PWD=p@ssw0rd");
    db.setDatabaseName("DRIVER={ODBC Driver 18 for SQL Server};"
                       "SERVER=DESKTOP-9L5QUCK;"
                       "DATABASE=Number1;"
                       "UID=sa;"
                       "PWD=p@ssw0rd;"
                       "TrustServerCertificate=yes;"
                       "Integrated Security=false;");


    // Open the connection
    if (!db.open()) {
        qDebug() << "Database connection failed:";
        qDebug() << db.lastError().text();
        return;
    } else {
        qDebug() << "Database connected!";
    }


    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::Login);

    // Install shortcut for Enter key


}
void MainWindow::Login(){
    QString name=ui->lineEdit->text();
    QString password=ui->lineEdit_2->text();

    QSqlQuery  query;
    query.prepare("select count(*) from admin where name=:name and password=:password ");
    query.bindValue(":name", name);  // Corrected binding format
    query.bindValue(":password", password);  // Corrected binding format

    if(!query.exec()){
        qDebug()<<"error query";
        qDebug()<<query.lastError().text();
        return;
    }

    if(query.next()){
        int count =query.value(0).toInt();
        if(count>0){
            qDebug()<<"sad";
            query.prepare("select is_admin from admin where name=:name and password=:password ");
            query.bindValue(":name", name);  // Corrected binding format
            query.bindValue(":password", password);  // Corrected binding format
            if(query.exec()){
                if(query.next()){
                    if(query.value(0).toBool()){
                        emit ended_admin();
                        close();

                    }
                    else {
                        emit ended_user();
                        close();

                    }

                }
            }


        }
        else {
            ui->label_5->setText("غلط ركز ونبى يسطا");
            QFont font = ui->label_5->font();  // Get the current font
            QRandomGenerator generator;
            generator.seed(QTime::currentTime().msec());
            font.setPointSize(generator.bounded(12,16));  // Set the desired point size (adjust as needed)
            ui->label_5->setFont(font);

        }

    }



}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->pushButton->click();
        event->accept(); // Indicate that the event has been handled
        return; // Stop further processing
    }

    // Handle Down arrow key
    if (event->key() == Qt::Key_Down) {
        ui->lineEdit_2->setFocus();
        event->accept(); // Indicate that the event has been handled
        return; // Stop further processing
    }
    if(event->key() ==Qt::Key_Up){
        ui->lineEdit->setFocus();
        event->accept();
        return;
    }

    // Call base class method to handle other key events
    QMainWindow::keyPressEvent(event);
}

MainWindow::~MainWindow()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
}
