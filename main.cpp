#include "mainwindow.h"
#include "dashboard.h"
#include "member.h"
#include "user.h"
#include "packages.h"
#include "safe.h"
#include "sheets.h"
#include <QDebug>  // Include QDebug header
#include <QApplication>
#include <QRect>
#include<QScreen>
#include<QTimer>
#include <windows.h>
#include "emp.h"

int main(int argc, char *argv[])
{
    //FreeConsole();
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/login/dumble.png"));
    MainWindow w;
    w.show();//

    std::unique_ptr<dashboard> dash(new dashboard());
    qDebug() << "Dashboard initialized";
    bool admin=1;

    // Updated code to use setAdminMode method
    QObject::connect(&w, &MainWindow::ended_admin, [&]() {
        qDebug() << "Admin mode activated.";
        dash->setAdminMode(true);
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - dash->width()) / 2;
        int y = (screenGeometry.height() - dash->height()) / 2;
        dash->move(x, y);
        dash->show();//
    });

    // Updated code to use setAdminMode method
    QObject::connect(&w, &MainWindow::ended_user, [&]() {
        qDebug() << "User mode activated.";
        dash->setAdminMode(false);
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - dash->width()) / 2;
        int y = (screenGeometry.height() - dash->height()) / 2;
        dash->move(x, y);
        admin=0;

        emit dash->disableButtons_signal();

        dash->show();
    });

    std::unique_ptr<Member> mem(new Member());

    QObject::connect(dash.get(), &dashboard::membeer, [&]() {
        qDebug() << "membeer signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - mem->width()) / 2;
        int y = (screenGeometry.height() - mem->height()) / 2;
        qDebug() << "Moving member widget to (" << x << ", " << y << ")";
        if(admin==0){
            mem->front_setter();
        }
        mem->move(x, y);
        mem->show();
    });
    //emit dash->membeer();

    std::unique_ptr<user> userInstance(new user());

    QObject::connect(dash.get(), &dashboard::user, [&]() {
        qDebug() << "membeer signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - userInstance->width()) / 2;
        int y = (screenGeometry.height() - userInstance->height()) / 2;
        qDebug() << "Moving member widget to (" << x << ", " << y << ")";
        userInstance->move(x, y);
        userInstance->show();
    });
    //emit dash->user();

    std::unique_ptr<packages> pack(new packages());

    QObject::connect(dash.get(), &dashboard::package, [&]() {
        qDebug() << "membeer signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - pack->width()) / 2;
        int y = (screenGeometry.height() - pack->height()) / 2;
        qDebug() << "Moving member widget to (" << x << ", " << y << ")";
        pack->move(x, y);
        pack->show();
    });
    //emit dash->package();

    std::unique_ptr<safe> safe_win(new safe());
    QObject::connect(dash.get(), &dashboard::safe, [&]() {
        qDebug() << "safe_win signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - safe_win->width()) / 2;
        int y = (screenGeometry.height() - safe_win->height()) / 2;
        qDebug() << "Moving member widget to (" << x << ", " << y << ")";
        safe_win->move(x, y);
        safe_win->show();
    });
    //emit dash->safe();
    std::unique_ptr<sheets> sheet(new sheets());
    QObject::connect(dash.get(), &dashboard::sheets, [&]() {
        qDebug() << "safe_win signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - sheet->width()) / 2;
        int y = (screenGeometry.height() - sheet->height()) / 2;
        qDebug() << "Moving sheet widget to (" << x << ", " << y << ")";
        sheet->move(x, y);
        sheet->show();
    });
    //emit dash->sheets();

    std::unique_ptr<emp> empo(new emp());
    QObject::connect(dash.get(), &dashboard::emp, [&]() {
        qDebug() << "employee signal received in main.";
        QRect screenGeometry = QApplication::primaryScreen()->availableGeometry();
        int x = (screenGeometry.width() - empo->width()) / 2;
        int y = (screenGeometry.height() - empo->height()) / 2;
        qDebug() << "Moving sheet widget to (" << x << ", " << y << ")";
        empo->move(x, y);
        empo->show();
    });
    //emit dash->emp();






    QObject::connect(mem.get(), &Member::memberClosed, dash.get(), &dashboard::memberClosedSignal);
    QObject::connect(empo.get(), &emp::emp_closed, dash.get(), &dashboard::emp_open);
    QObject::connect(userInstance.get(), &user::closed_user, dash.get(), &dashboard::user_enable);
    QObject::connect(pack.get(), &packages::pack_closed, dash.get(), &dashboard::pack_closed);
    QObject::connect(safe_win.get(), &safe::safe_closed, dash.get(), &dashboard::safe_enable);
    QObject::connect(sheet.get(), &sheets::closed, dash.get(), &dashboard::open_sheet);
    QObject::connect(pack.get(), &packages::added, mem.get(), &Member::update_packages);
    QObject::connect(empo.get(), &emp::employee, mem.get(), &Member::emplyee_capturred);








    qDebug() << "Connected membeer signal to slot";


    return a.exec();
}
