#include "user.h"
#include "ui_user.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <QInputDialog>

user::user(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};"
                       "SERVER=LAPTOP-ONHG8FN6;"
                       "DATABASE=zktecho;"
                       "UID=nesa;"
                       "PWD=123698745");



    // Open the connection
    if (!db.open()) {
        qDebug() << "Database connection failed:";
        qDebug() << db.lastError().text();
        return;
    } else {
        qDebug() << "Database connected!";
    }




    setWindowTitle("New User");

    if (!db.open()) {
        qDebug() << "Database connection failed:";
        return;
    }


    QString darkStyleSheet = R"(
        /* QWidget styling */
        QWidget {
            background-color: #2C3333;
            color: #FFFFFF;
            font-family: Arial, sans-serif;
            font-size: 14px;
        }

        /* QLabel styling */
        QLabel {
            color: #FFFFFF;
            border: none;
        }

        /* QLineEdit styling */
        QLineEdit {
            background-color: #395B64;
            border: 1px solid #555555;
            border-radius: 5px;
            padding: 5px;
            color: #E0E0E0;
        }

        QLineEdit:focus {
            border: 1px solid #AAAAAA;
        }
        /* QPushButton styling */
        QPushButton {
            background-color: #A5C9CA;
            border: 1px solid #5C5C5C;
            border-radius: 5px;
            padding: 5px 10px;
            color: #000000;
        }

        QPushButton:hover {
            background-color: #E7F6F2;
        }

        QPushButton:pressed {
            background-color: #064663;
            color: #FFFFFF;
        }

        /* QRadioButton styling */
        QRadioButton {
            color: #E7F6F2;
            background-color: transparent;
        }

        QRadioButton::indicator {
            width: 13px;
            height: 13px;
        }

        QRadioButton::indicator::unchecked {
            border: 1px solid #5C5C5C;
            background-color: #3A3F44;
            border-radius: 6px;
        }

        QRadioButton::indicator::unchecked:hover {
            border: 1px solid #9A0680;
            background-color: #3E065F;
        }

        QRadioButton::indicator::checked {
            border: 1px solid #5C5C5C;
            background-color: #F73D93;
            border-radius: 6px;
        }

        QRadioButton::indicator::checked:hover {
            border: 1px solid #ECB365;
            background-color: #041C32;
        }

        QRadioButton::indicator::checked:disabled {
            border: 1px solid #3E3E3E;
            background-color: #2E2E2E;
        }
    )";

    // Apply the stylesheet to the entire dashboard widget
    this->setStyleSheet(darkStyleSheet);
    connect(ui->pushButton,&QPushButton::clicked,this,&user::save_clicked);
}
void user::save_clicked() {
    QString name = ui->name->text().trimmed();
    QString pass = ui->pass->text();
    QString pass2 = ui->pass_2->text();

    // Perform input validation
    if (name.isEmpty() || pass.isEmpty()) {
        qDebug() << "Name or password fields are empty!";

        // Show a QMessageBox to notify the user
        QMessageBox::critical(this, "Input Error", "Please fill in all fields (name and passwords).");

        // Return from the slot
        return;
    }

    if (pass.length() < 4) {
        qDebug() << "Password is too short!";

        // Show a QMessageBox to notify the user
        QMessageBox::critical(this, "Input Error", "Password should be at least 4 characters long.");

        // Return from the slot
        return;
    }

    if (pass != pass2) {
        qDebug() << "Passwords do not match!";

        // Show a QMessageBox to notify the user
        QMessageBox::critical(this, "Input Error", "Passwords do not match. Please check and try again.");

        // Return from the slot
        return;
    }

    bool isAdmin = ui->admin->isChecked();

    // Assuming you have a valid database connection
    QSqlQuery query;
    QString queryString = "SELECT id, password FROM admin WHERE name = :name";
    query.prepare(queryString);
    query.bindValue(":name", name);

    if (!query.exec()) {
        qDebug() << "Error checking existing user:" << query.lastError().text();
        return;
    }

    if (query.next()) {
        // User exists, prompt for old password
        QString existingPassword = query.value("password").toString();

        bool ok;
        QString oldPass = QInputDialog::getText(this, "Old Password Required",
                                                "Enter old password:",
                                                QLineEdit::Password,
                                                "", &ok);

        if (ok && oldPass == existingPassword) {
            // Old password matches, update to new password
            int existingId = query.value("id").toInt();

            queryString = "UPDATE admin SET password = :password, is_admin = :is_admin WHERE id = :id";
            query.prepare(queryString);
            query.bindValue(":id", existingId);
            query.bindValue(":password", pass);
            query.bindValue(":is_admin", ui->admin->isChecked());

            if (!query.exec()) {
                qDebug() << "Error updating password:" << query.lastError().text();
                return;
            }

            QMessageBox::information(this, "Success", "Password updated successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Old password is incorrect. Password update failed.");
            return;
        }
    } else {
        // User does not exist, insert new record
        queryString = "SELECT COALESCE(MAX(id), 0) + 1 AS next_id FROM admin";
        query.prepare(queryString);

        if (!query.exec()) {
            qDebug() << "Error executing max id query:" << query.lastError().text();
            return;
        }

        int nextId = 1;
        if (query.next()) {
            nextId = query.value("next_id").toInt();
        }

        queryString = "INSERT INTO admin (id, name, password, is_admin) VALUES (:id, :name, :password, :is_admin)";
        query.prepare(queryString);
        query.bindValue(":id", nextId);
        query.bindValue(":name", name);
        query.bindValue(":password", pass);
        query.bindValue(":is_admin", ui->admin->isChecked());

        if (!query.exec()) {
            qDebug() << "Error inserting new record:" << query.lastError().text();
            return;
        }

        QMessageBox::information(this, "Success", "New admin record inserted successfully.");
    }

    // Clear input fields or perform any other necessary actions
    ui->name->clear();
    ui->pass->clear();
    ui->pass_2->clear();
}

void user::closeEvent(QCloseEvent *event) {
    emit closed_user();  // Emit the signal when the widget is closed
    qDebug() << "user widget closed";
    QWidget::closeEvent(event);  // Call the base class implementation
}

user::~user()
{
    delete ui;
}
