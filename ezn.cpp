#include "ezn.h"
#include "ui_ezn.h"

ezn::ezn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ezn)
{
    ui->setupUi(this);
    ui->date->setDate(QDate::currentDate());

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
    QLineEdit, QTextEdit {
        background-color: #395B64;
        border: 1px solid #555555;
        border-radius: 5px;
        padding: 5px;
        color: #E0E0E0;
    }

    QLineEdit:focus, QTextEdit:focus {
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

    /* QComboBox styling */
    QComboBox {
        background-color: #395B64;
        border: 1px solid #555555;
        border-radius: 5px;
        padding: 5px;
        color: #E0E0E0;
    }

    QComboBox:focus {
        border: 1px solid #AAAAAA;
    }

    QComboBox::drop-down {
        background-color: #395B64;
        border-left: 1px solid #555555;
        width: 25px; /* Controls width of the drop-down area */
    }

    QComboBox::down-arrow {
        width: 13px;
        height: 13px;
        background-color: #A5C9CA; /* Background behind the arrow */
    }

    QComboBox::item {
        background-color: #2C3333;
        color: #FFFFFF;
    }

    QComboBox::item:hover {
        background-color: #E7F6F2;
        color: #000000;
    }

    /* QDateEdit styling */
    QDateEdit {
        background-color: #395B64;
        border: 1px solid #555555;
        border-radius: 5px;
        padding: 5px;
        color: #E0E0E0;
    }

    QDateEdit:focus {
        border: 1px solid #AAAAAA;
    }

    QDateEdit::drop-down {
        background-color: #395B64;
        border-left: 1px solid #555555;
    }

    /* QCalendarWidget popup styling (for QDateEdit calendar) */
    QCalendarWidget QAbstractItemView {
        background-color: #2C3333;
        color: #E0E0E0;
        selection-background-color: #A5C9CA;
        selection-color: #000000;
    }
)";



    // Apply the stylesheet to the entire dashboard widget
    this->setStyleSheet(darkStyleSheet);
    connect(ui->save,&QPushButton::clicked,this,&ezn::save);
    connect(ui->left,&QPushButton::clicked,this,&ezn::on_leftButton_clicked);
    connect(ui->right,&QPushButton::clicked,this,&ezn::right);
    connect(ui->del,&QPushButton::clicked,this,&ezn::deletee);



}
void ezn::closeEvent(QCloseEvent *event) {
    emit ezn_closed();  // Emit the signal when the widget is closed
    qDebug() << "emp widget closed";
    QWidget::closeEvent(event);  // Call the base class implementation
}
void ezn::save(){
    QDate date = ui->date->date();
    QString type=ui->type->currentText();

    int price = ui->price->text().trimmed().toInt();

    // 3. Get the note from the QTextEdit
    QString noteString = ui->note->toPlainText().trimmed()+" اذن خزنة";

    // 4. Prepare the SQL query to insert the data (assuming payment_date is of date type in the database)
    QSqlQuery query;
    // 5. Find the maximum existing id in the payment table
    query.prepare("SELECT MAX(id) FROM payment");
    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve max id: " + query.lastError().text());
        return;
    }

    // 6. Calculate the new id
    qint64 newId = 1; // Default to 1 if there are no records
    if (query.next()) {
        newId = query.value(0).isNull() ? 1 : query.value(0).toInt() + 1;
    }
    QString insertQuery = QString(R"(
        INSERT INTO payment (id, date_pay, amount, note, type)
        VALUES (%1, :date_pay, :amount, :note, :type)
    )").arg(newId);
    query.prepare(insertQuery);

    // 5. Bind the values to the query
    query.bindValue(":date_pay", date);  // Bind the QDate value
    query.bindValue(":amount", price);         // Bind the amount as a double
    query.bindValue(":note", noteString);
    query.bindValue(":type", type);         // Bind the note text

    // 6. Execute the query and handle the result
    if (!query.exec()) {
        // Show an error message if the insertion fails
        QMessageBox::critical(this, "Error", "Failed to insert payment: " + query.lastError().text());
        return;
    }

    // 7. Success message or update the UI
    QMessageBox::information(this, "Success", "Payment saved successfully.");
    ui->price->clear();       // Clear the price QLineEdit
    ui->note->clear();        // Clear the note QTextEdit
    ui->date->setDate(QDate::currentDate());

}
void ezn::on_leftButton_clicked() {
    int currentPaymentId = -1; // Initialize to an invalid ID


    if (ui->price->text().isEmpty() && ui->note->toPlainText().isEmpty()) {
        // If both fields are empty, get the maximum ID for payments with NULL values
        QSqlQuery maxIdQuery;
        maxIdQuery.prepare("SELECT MAX(id) AS max_id FROM payment WHERE customer_id IS NULL AND pack_id IS NULL AND pt_id IS NULL");

        if (!maxIdQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve maximum payment ID: " + maxIdQuery.lastError().text());
            return;
        }

        if (maxIdQuery.next()) {
            currentPaymentId = maxIdQuery.value("max_id").toInt()+1; // Store the maximum payment ID
        }

        if (currentPaymentId == -1) {
            QMessageBox::information(this, "Information", "مفيش اصلا");
            return; // Exit the slot if no payment found
        }

    } else {
        // If the price and note fields are filled, get the date and type
        QDate displayedDate = ui->date->date();
        QString selectedType = ui->type->currentText().trimmed();
        int price=ui->price->text().trimmed().toInt();

        // Query to get the ID of the currently displayed payment based on the date and type
        QSqlQuery idQuery;
        idQuery.prepare("SELECT id FROM payment WHERE date_pay = :displayedDate AND type = :selectedType AND amount = :price AND customer_id IS NULL AND pack_id IS NULL AND pt_id IS NULL");
        idQuery.bindValue(":displayedDate", displayedDate);
        idQuery.bindValue(":selectedType", selectedType);
        idQuery.bindValue(":price", price);

        if (!idQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve payment ID: " + idQuery.lastError().text());
            return;
        }

        if (idQuery.next()) {
            currentPaymentId = idQuery.value("id").toInt(); // Store the current payment ID
        } else {
            QMessageBox::information(this, "Information", "امسح الحجات المكتوبه");
            return;
        }
    }




    QSqlQuery query;
    query.prepare("SELECT TOP 1 * FROM payment "
                  "WHERE customer_id IS NULL "
                  "AND pack_id IS NULL "
                  "AND pt_id IS NULL "
                  "AND id < :currentPaymentId "
                  "ORDER BY id DESC");

    query.bindValue(":currentPaymentId", currentPaymentId);


    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve payments: " + query.lastError().text());
        return;
    }

    // Clear previous input fields
    ui->price->clear(); // Clear previous price
    ui->note->clear(); // Clear previous note



    if (query.next()) { // Check if there is a result
        // Set the date, type, amount, and note into respective UI components
        ui->date->setDate(query.value("date_pay").toDate()); // Assuming date_pay is of type DATE
        ui->type->setCurrentText(query.value("type").toString()); // Assuming you have a combobox for type
        ui->price->setText(query.value("amount").toString()); // Assuming amount is stored as a string
        ui->note->setPlainText(query.value("note").toString()); // Assuming note is of type TEXT
    } else {
        QMessageBox::information(this, "Information", "ده أول إذن يصحبى مفيش قبله");
    }
}
void ezn::right(){

    int currentPaymentId=-1;
    if (ui->price->text().isEmpty() && ui->note->toPlainText().isEmpty()) {
        // If both fields are empty, get the maximum ID for payments with NULL values
        QSqlQuery maxIdQuery;
        maxIdQuery.prepare("SELECT MIN(id) AS min_id FROM payment WHERE customer_id IS NULL AND pack_id IS NULL AND pt_id IS NULL");

        if (!maxIdQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve maximum payment ID: " + maxIdQuery.lastError().text());
            return;
        }

        if (maxIdQuery.next()) {
            currentPaymentId = maxIdQuery.value("min_id").toInt()-1; // Store the maximum payment ID
        }

        if (currentPaymentId == -1) {
            QMessageBox::information(this, "Information", "مفيش اصلا");
            return; // Exit the slot if no payment found
        }

    } else {
        // If the price and note fields are filled, get the date and type
        QDate displayedDate = ui->date->date();
        QString selectedType = ui->type->currentText().trimmed();
        int price=ui->price->text().trimmed().toInt();

        // Query to get the ID of the currently displayed payment based on the date and type
        QSqlQuery idQuery;
        idQuery.prepare("SELECT id FROM payment WHERE date_pay = :displayedDate AND type = :selectedType AND amount = :price AND customer_id IS NULL AND pack_id IS NULL AND pt_id IS NULL");
        idQuery.bindValue(":displayedDate", displayedDate);
        idQuery.bindValue(":selectedType", selectedType);
        idQuery.bindValue(":price", price);

        if (!idQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve payment ID: " + idQuery.lastError().text());
            return;
        }

        if (idQuery.next()) {
            currentPaymentId = idQuery.value("id").toInt(); // Store the current payment ID
        } else {
            QMessageBox::information(this, "Information", "امسح الحجات المكتوبه");
            return;
        }
    }




    QSqlQuery query;
    query.prepare("SELECT TOP 1 * FROM payment "
                  "WHERE customer_id IS NULL "
                  "AND pack_id IS NULL "
                  "AND pt_id IS NULL "
                  "AND id > :currentPaymentId "
                  "ORDER BY id ASC");

    query.bindValue(":currentPaymentId", currentPaymentId);


    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve payments: " + query.lastError().text());
        return;
    }

    // Clear previous input fields
    ui->price->clear(); // Clear previous price
    ui->note->clear(); // Clear previous note



    if (query.next()) { // Check if there is a result
        // Set the date, type, amount, and note into respective UI components
        ui->date->setDate(query.value("date_pay").toDate()); // Assuming date_pay is of type DATE
        ui->type->setCurrentText(query.value("type").toString()); // Assuming you have a combobox for type
        ui->price->setText(query.value("amount").toString()); // Assuming amount is stored as a string
        ui->note->setPlainText(query.value("note").toString()); // Assuming note is of type TEXT
    } else {
        QMessageBox::information(this, "Information", "ده اخر إذن يصحبى مفيش بعده");
    }

}
void ezn::deletee(){
    int currentPaymentId=-1;
    QDate displayedDate = ui->date->date();
    QString selectedType = ui->type->currentText().trimmed();
    int price=ui->price->text().trimmed().toInt();

    // Query to get the ID of the currently displayed payment based on the date and type
    QSqlQuery idQuery;
    idQuery.prepare("SELECT id FROM payment WHERE date_pay = :displayedDate AND type = :selectedType AND amount = :price AND customer_id IS NULL AND pack_id IS NULL AND pt_id IS NULL");
    idQuery.bindValue(":displayedDate", displayedDate);
    idQuery.bindValue(":selectedType", selectedType);
    idQuery.bindValue(":price", price);
    if (!idQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve payment ID: " + idQuery.lastError().text());
        return;
    }
    if (idQuery.next()) {
        currentPaymentId = idQuery.value("id").toInt(); // Store the current payment ID
    } else {
        QMessageBox::information(this, "Information", "امسح الحجات المكتوبه");
        return;
    }

    idQuery.prepare("DELETE FROM payment WHERE id = :currentPaymentId");
    idQuery.bindValue(":currentPaymentId", currentPaymentId);  // Bind the currentPaymentId value

    if (!idQuery.exec()) {
        QMessageBox::critical(nullptr, "Delete Payment",
                              "Failed to delete payment: " + idQuery.lastError().text());
    } else {
        QMessageBox::information(nullptr, "Delete Payment",
                                 "Payment with ID " + QString::number(currentPaymentId) + " deleted successfully.");
    }

}

ezn::~ezn()
{
    delete ui;
}
