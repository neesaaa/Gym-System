#include "dashboard.h"
#include "ui_dashboard.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>  // Include QDebug header

dashboard::dashboard(QWidget *parent,bool is_admin)
    : QWidget(parent)
    , ui(new Ui::dashboard)
{
    ui->setupUi(this);
    QString btnsStyle =
        "QWidget {"
        "border: 2px solid #E3651D;"
        "border-radius: 5px;"
        "background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ffde59, stop:1 #ff914d);"
        "}"
        "QPushButton {"
        "border: 2px solid black;"
        "border-radius: 5px;"
        "color: white;"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #151515, stop:1 #151515);"
        "}"
        "QPushButton:hover {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFD700, stop:1 #8B0000);"
        "}"
        "QPushButton:pressed {"
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FAF5E4, stop:1 #F4EEC7);"
        "}";

    // Apply the combined stylesheet to ui->btns
    ui->btns->setStyleSheet(btnsStyle);
            // Combine styles into one stylesheet

    QList<QPushButton *> buttons = ui->btns->findChildren<QPushButton *>();
        for (QPushButton *button : buttons) {
        // Create a QGraphicsDropShadowEffect for the button
        QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(button);
        shadowEffect->setBlurRadius(10);  // Set the blur radius of the shadow
        shadowEffect->setOffset(3, 3);    // Set the offset (x, y) of the shadow
        shadowEffect->setColor(Qt::black); // Set the color of the shadow

        // Apply the shadow effect to the button
        button->setGraphicsEffect(shadowEffect);
    }
    ui->frame->setStyleSheet("border: 2px solid #E3651D; border-radius: 5px; background-color:FFD700;");




    //signals
    connect(ui->pushButton_2,&QPushButton::clicked,this,&dashboard::member_slot);
    connect(this, &dashboard::memberClosedSignal, this, &dashboard::member_enable);

    connect(ui->User,&QPushButton::clicked,this,&dashboard::user_slot);

    connect(ui->safe,&QPushButton::clicked,this,&dashboard::safe_click);

    connect(this, &dashboard::disableButtons_signal, this, &dashboard::disableButtons);
    connect(this, &dashboard::user_closed, this, &dashboard::user_enable);
    // connect(this, &dashboard::pack_closeddd, this, &dashboard::pack_closed);
    connect(ui->pack, &QPushButton::clicked, this, &dashboard::pack_slot);
    connect(ui->sheet, &QPushButton::clicked, this, &dashboard::sheet_click);

    connect(ui->Emp, &QPushButton::clicked, this, &dashboard::open_emp);

    connect(ui->ezn, &QPushButton::clicked, this, &dashboard::ezn_slot);



    qDebug() << "Connected pushButton_2 to member_slot";

}
void dashboard::setAdminMode(bool is_admin) {
    bool isAdmin = is_admin;
    QString imagePath = isAdmin ? ":/login/xhale-admin.jpeg" : ":/login/frontdesk.jpeg";
    QPixmap pixmap(imagePath);
    ui->photo->setPixmap(pixmap);
    ui->photo->setScaledContents(true);
    qDebug() << "Dashboard mode set to" << (isAdmin ? "admin" : "user");
}

void
dashboard::member_slot(){
    qDebug() << "member_slot called";
    emit membeer();
    ui->pushButton_2->setEnabled(false);
    QString buttonName = "pushButton_2"; // Assuming this is the name of your QPushButton

    // Default style
    QString defaultStyle = QString("#%1 {"
                                   "border: 2px solid black;"
                                   "border-radius: 5px;"
                                   "color: gray;"
                                   "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #151515, stop:1 #151515);"
                                   "}").arg(buttonName);


    ui->pushButton_2->setStyleSheet(defaultStyle);

    qDebug() << "lol++++";
}
void dashboard::member_enable(){
    ui->pushButton_2->setEnabled(true);
    QString buttonName = "pushButton_2"; // Assuming this is the name of your QPushButton

    // Default style
    QString defaultStyle = QString("#%1 {"
                                   "border: 2px solid black;"
                                   "border-radius: 5px;"
                                   "color: white;"
                                   "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #151515, stop:1 #151515);"
                                   "}").arg(buttonName);

    // Hover style
    QString hoverStyle = QString("#%1:hover {"
                                 "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FFD700, stop:1 #8B0000);"
                                 "}").arg(buttonName);

    // Pressed style
    QString pushedStyle = QString("#%1:pressed {"
                                  "background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FAF5E4, stop:1 #F4EEC7);"
                                  "}").arg(buttonName);

    // Combine styles into one stylesheet
    QString styleSheet = defaultStyle + hoverStyle + pushedStyle;

    // Apply the stylesheet to ui->pushButton_2
    ui->pushButton_2->setStyleSheet(styleSheet);


}
void dashboard::user_slot(){
    emit user();
    ui->User->setDisabled(true);
}
void dashboard::disableButtons(){
    ui->User->setDisabled(true);
    ui->pack->setDisabled(true);
    ui->Emp->setDisabled(true);
    ui->ezn->setDisabled(true);
}
void dashboard::user_enable(){
    ui->User->setEnabled(true);
}
void dashboard::pack_slot(){
    emit package();
    ui->pack->setDisabled(true);
}
void dashboard::pack_closed(){
    ui->pack->setEnabled(true);
}
void dashboard::safe_click(){
    emit safe();
    ui->safe->setDisabled(true);
}
void dashboard::safe_enable(){
    ui->safe->setEnabled(true);
}
void dashboard::sheet_click(){
    emit sheets();
    ui->sheet->setDisabled(true);
}
void dashboard::open_sheet(){
    ui->sheet->setEnabled(true);
}
void dashboard::open_emp(){
    emit emp();
    ui->Emp->setDisabled(true);
}
void dashboard::emp_open(){
    ui->Emp->setEnabled(true);
}
void dashboard::ezn_slot(){
    emit ezn_khazna();
    ui->ezn->setDisabled(true);
}
void dashboard::ezn_enaple(){
    ui->ezn->setEnabled(true);
}

dashboard::~dashboard()
{
    delete ui;
}
