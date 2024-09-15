#include "packages.h"
#include "ui_packages.h"
#include <QMessageBox>
#include <QTabWidget>

packages::packages(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::packages)
{
    ui->setupUi(this);
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

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
QString globalStyle = R"(
    QWidget {
        background-color: #31363F;
        color: #FFFFFF;
    }
    QLabel {
        background-color: transparent;
        color: #FFFFFF;
    }
    QLabel#label_5 {
        background-color: #003C43;
        color: #FFFFFF;
        border: 2px dashed #C8FFE0;
    }
    QLabel#label_10 {
        background-color: #005C78 ;
        color: #FFFFFF;
        border: 2px dashed #5DEBD7;
        padding: 2px;
    }
    QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox {
        background-color: #040D12;
        color: #FFFFFF;
        border: 2px solid #222831;
    }
    QLineEdit:focus, QDateEdit:focus, QTextEdit:focus, QSpinBox:focus, QComboBox:focus {
        border: 2px solid #FFA62F;
        background-color: #1F1B24;
    }
    QWidget#widget_4, QWidget#widget_3 {
        background-color: #31363F;
        color: #FFFFFF;
        border: 2px solid #C8FFE0; /* Optional: add border */
    }
    QWidget#widget_5, QWidget#widget_6, QWidget#widget_7, QWidget#widget_8, QWidget#widget_13, QWidget#widget_11, QWidget#widget_12 {
        background-color: #31363F;
        color: #FFFFFF;
        border: none; /* Optional: add border */
    }
    QWidget#widget_16, QWidget#widget_17, QWidget#widget_18, QWidget#widget_19 ,QWidget#widget_20 ,QWidget#widget_21 ,QWidget#widget_22 , QWidget#widget_23{
        background-color: #31363F;
        color: #FFFFFF;
        border: none; /* Optional: add border */
    }
    QWidget#widget_10 {
        background-color: #31363F;
        color: #FFFFFF;
        border: none; /* Light blue border */
    }
    QWidget#widget_9 {
        background-color: #31363F;
        color: #FFFFFF;
        border: none; /* Light blue border */
    }
    QWidget#widget_24 {
        background-color: #3887BE; /* Orange background */
        border: 1px solid #222831;
        border-radius: 5px;
        box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
    }
    QWidget#widget_26 {
        background-color: #164863; /* Orange background */
        color: #FFFFFF; /* White text */
        border: 2px solid #5356FF; /* Orange border */
        border-radius: 5px;
        box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
    }
    QWidget#widget_15, QWidget#widget_14 {
        background-color: #31363F;
        color: #FFFFFF;
        border: 2px solid #87CEEB; /* Light blue border */
    }
    QPushButton {
        border: 2px solid #FFA62F;
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #005C78, stop:1 #003C43);
        color: #FFFFFF;
    }
    QPushButton#pt_search,QPushButton#pt_edit,QPushButton#pt_delete,QPushButton#pt_save {
        border: 2px solid #FFA62F;
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #005C78, stop:1 #A7E6FF);
        color: #FFFFFF;
    }
    QPushButton:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF8C00, stop:1 #F05941);
    }
    QPushButton:pressed {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5D001E, stop:1 #8A3324);
        border: 2px solid #87431D;
    }
    QPushButton#pt_search:hover,
    QPushButton#pt_edit:hover,
    QPushButton#pt_delete:hover,
    QPushButton#pt_save:hover {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF8C00, stop:1 #F05941);
    }

    QPushButton#pt_search:pressed,
    QPushButton#pt_edit:pressed,
    QPushButton#pt_delete:pressed,
    QPushButton#pt_save:pressed {
        background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5D001E, stop:1 #8A3324);
        border: 2px solid #87431D;
    }
    QTableWidget {
        background-color: #5C8374;
        color: #FFFFFF;
        border: 2px solid #222831;
    }
    QHeaderView::section {
        background-color: #31363F;
        color: #FFFFFF;
        padding: 4px;
    }
    QTableWidget::item {
        background-color: #212A3E;
    }
    QTableWidget::item:selected {
        background-color: #FF8C00;
        color: #FFFFFF;
    }
    QTableWidget::item:hover {
        background-color: #1F1B24;
        color: #FFA62F;
    }
)";
    // Apply the global stylesheet
    ui->pack_table->horizontalHeader()->setStretchLastSection(true);
    int numRows = ui->pack_table->rowCount();

    // Set the height of the last row to expand vertically
    int lastRow = numRows - 1;
    ui->pack_table->setRowHeight(lastRow, ui->pack_table->rowHeight(lastRow) + 10); // Adjust the height as neede

    this->setStyleSheet(globalStyle);
    pack_id=-1;
    pt_id=-1;
    connect(ui->pack_save,&QPushButton::clicked,this,&packages::pack_save);
    connect(ui->pack_search, &QPushButton::clicked, this, &packages::pack_search);
    connect(ui->pack_edit, &QPushButton::clicked, this, &packages::pack_edit);// Connect search button
    connect(ui->pack_delete, &QPushButton::clicked, this, &packages::pack_delete);

    connect(ui->pt_save, &QPushButton::clicked, this, &packages::pt_save);
    connect(ui->pt_search , &QPushButton::clicked, this, &packages::pt_search );
    connect(ui->pt_edit , &QPushButton::clicked, this, &packages::pt_edit );
    connect(ui->pt_delete , &QPushButton::clicked, this, &packages::pt_delete );

    connect(ui->active, &QRadioButton::toggled, this, &packages::updateIcon);

    updateIcon();



}
void packages::clearData() {
    // Clear QLineEdit, QComboBox, etc.
    ui->name->clear();
    ui->price->clear();
    ui->count->clear();
    ui->duration->clear();
    // Clear other UI elements as needed

    // Clear the QTableWidget (pack_table)
    ui->pack_table->clearContents();
}
void packages::clearData_pt() {
    // Clear QLineEdit, QComboBox, etc.
    ui->name_pt->clear();
    ui->price_pt->clear();
    ui->count_pt->clear();
    ui->pt->clear();
    // Clear other UI elements as needed

    // Clear the QTableWidget (pack_table)
}
void packages::pack_save(){
    ui->pack_save->setDisabled(true);
    QString name = ui->name->text().trimmed();
    QString priceStr = ui->price->text().trimmed();
    int count = ui->count->value();
    int duration = ui->duration->value();
    bool active=ui->active->isChecked();

    // Validate name is not empty
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if name is empty
    }

    // Validate price is not empty and convert to integer
    if (priceStr.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Price cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if price is empty
    }

    bool ok;
    int price = priceStr.toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Price must be a valid integer.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if price is not a valid integer
    }

    // Validate and convert other values
    int inbody = 0, spa = 0, inv = 0, freeze = 0, pt = 0;
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM package_on_desk WHERE name = :name");
    checkQuery.bindValue(":name", name);
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::critical(this, "Input Error", "Name already exists. Please choose a different name.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if name already exists
    }

    if (!ui->pack_table->item(0, 0) || ui->pack_table->item(0, 0)->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Inbody cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if inbody cell is empty
    } else {
        inbody = ui->pack_table->item(0, 0)->text().trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Input Error", "Inbody must be a valid integer.");
            ui->pack_save->setEnabled(true);
            return; // Exit function if inbody is not a valid integer
        }
    }

    if (!ui->pack_table->item(0, 1) || ui->pack_table->item(0, 1)->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Spa cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if spa cell is empty
    } else {
        spa = ui->pack_table->item(0, 1)->text().trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Input Error", "Spa must be a valid integer.");
            ui->pack_save->setEnabled(true);
            return; // Exit function if spa is not a valid integer
        }
    }

    if (!ui->pack_table->item(0, 2) || ui->pack_table->item(0, 2)->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Inv cannot be empty.");
        ui->pack_save->setEnabled(true);

        return; // Exit function if inv cell is empty
    } else {
        inv = ui->pack_table->item(0, 2)->text().trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Input Error", "Inv must be a valid integer.");
            ui->pack_save->setEnabled(true);
            return; // Exit function if inv is not a valid integer
        }
    }

    if (!ui->pack_table->item(0, 3) || ui->pack_table->item(0, 3)->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Freeze cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if freeze cell is empty
    } else {
        freeze = ui->pack_table->item(0, 3)->text().trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Input Error", "Freeze must be a valid integer.");
            ui->pack_save->setEnabled(true);
            return; // Exit function if freeze is not a valid integer
        }
    }

    if (!ui->pack_table->item(0, 4) || ui->pack_table->item(0, 4)->text().trimmed().isEmpty()) {
        QMessageBox::critical(this, "Input Error", "PT cannot be empty.");
        ui->pack_save->setEnabled(true);
        return; // Exit function if pt cell is empty
    } else {
        pt = ui->pack_table->item(0, 4)->text().trimmed().toInt(&ok);
        if (!ok) {
            QMessageBox::critical(this, "Input Error", "PT must be a valid integer.");
            ui->pack_save->setEnabled(true);
            return; // Exit function if pt is not a valid integer
        }
    }
    int maxId = 0;
    QSqlQuery queryMaxId("SELECT COALESCE(MAX(id), 0) FROM package_on_desk");
    if (queryMaxId.next()) {
        maxId = queryMaxId.value(0).toInt() + 1; // Increment max ID by 1
    }


    // Insert data into package_on_desk table
    QSqlQuery query;
    query.prepare("INSERT INTO package_on_desk (id, inbody, spa, start_date, inv, freezze, pt, name, count, price, duration, installment,active) "
                  "VALUES (:id, :inbody, :spa,  GETDATE(), :inv, :freezze, :pt, :name, :count, :price, :duration, 0, :active)");
    query.bindValue(":id", maxId);
    query.bindValue(":inbody", inbody); // Assuming default values for these columns
    query.bindValue(":spa", spa);
    query.bindValue(":inv", inv);
    query.bindValue(":freezze", freeze);
    query.bindValue(":pt", pt);
    query.bindValue(":name", name);
    query.bindValue(":count", count);
    query.bindValue(":price", price);
    query.bindValue(":duration", duration);
    query.bindValue(":active", active?1:0);


    if (query.exec()) {
        qDebug() << "Data inserted successfully.";
        QMessageBox::information(this, "Success", "Data inserted successfully.");
        emit added();
        clearData();
    } else {
        qDebug() << "Error inserting data:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to insert data:\n" + query.lastError().text());
    }
    ui->pack_save->setEnabled(true);

}

void packages::pack_search() {
    ui->pack_search->setEnabled(false);

    QString searchName = ui->name->text().trimmed();

    // Validate if searchName is not empty
    if (searchName.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Please enter a name to search.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM package_on_desk WHERE name = :name");
    query.bindValue(":name", searchName);

    if (query.exec()) {
        if (query.next()) {
            pack_id=query.value("id").toInt();
            int inbody = query.value("inbody").toInt();
            int spa = query.value("spa").toInt();
            int inv = query.value("inv").toInt();
            int freezze = query.value("freezze").toInt();
            int pt = query.value("pt").toInt();
            QString name = query.value("name").toString();
            int count = query.value("count").toInt();
            int price = query.value("price").toInt();
            int duration = query.value("duration").toInt();
            bool active=query.value("active").toBool();
            if(active)
                ui->active->setChecked(true);
            else
                ui->active->setChecked(false);
            // Populate UI elements with retrieved data
            ui->pack_table->setItem(0, 0, new QTableWidgetItem(QString::number(inbody)));
            ui->pack_table->setItem(0, 1, new QTableWidgetItem(QString::number(spa)));
            ui->pack_table->setItem(0, 2, new QTableWidgetItem(QString::number(inv)));
            ui->pack_table->setItem(0, 3, new QTableWidgetItem(QString::number(freezze)));
            ui->pack_table->setItem(0, 4, new QTableWidgetItem(QString::number(pt)));
            ui->name->setText(name);
            ui->count->setValue(count);
            ui->price->setText(QString::number(price));
            ui->duration->setValue(duration);

            QMessageBox::information(this, "Success", "Package found and loaded.");
        } else {
            QMessageBox::information(this, "Not Found", "No package found with that name.");
        }
    } else {
        qDebug() << "Error searching data:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to search data:\n" + query.lastError().text());
    }
    ui->pack_search->setEnabled(true);

}
void packages::pack_edit() {
    ui->pack_edit->setEnabled(false);

    if (pack_id == -1) {
        QMessageBox::critical(this, "No Search", "Please search first to edit.");
        ui->pack_edit->setEnabled(true);
        return;
    }

    // Retrieve data for editing
    QString name = ui->name->text().trimmed();
    QString priceStr = ui->price->text().trimmed();
    int count = ui->count->value();
    int duration = ui->duration->value();

    // Validate name is not empty
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name cannot be empty.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if name is empty
    }

    // Validate price is not empty and convert to integer
    if (priceStr.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Price cannot be empty.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if price is empty
    }

    bool ok;
    int price = priceStr.toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Price must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if price is not a valid integer
    }

    int inbody = ui->pack_table->item(0, 0)->text().trimmed().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Inbody must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if inbody is not a valid integer
    }

    int spa = ui->pack_table->item(0, 1)->text().trimmed().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Spa must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if spa is not a valid integer
    }

    int inv = ui->pack_table->item(0, 2)->text().trimmed().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Inv must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if inv is not a valid integer
    }

    int freeze = ui->pack_table->item(0, 3)->text().trimmed().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Freeze must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if freeze is not a valid integer
    }

    int pt = ui->pack_table->item(0, 4)->text().trimmed().toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "PT must be a valid integer.");
        ui->pack_edit->setEnabled(true);
        return; // Exit function if pt is not a valid integer
    }
    bool activee=ui->active->isChecked();

    // Update data in package_on_desk table
    QSqlQuery query;
    query.prepare("UPDATE package_on_desk SET inbody = :inbody, spa = :spa, inv = :inv, freezze = :freeze, pt = :pt, "
                  "name = :name, count = :count, price = :price, duration = :duration, active = :active WHERE id = :id");
    query.bindValue(":inbody", inbody);
    query.bindValue(":spa", spa);
    query.bindValue(":inv", inv);
    query.bindValue(":freeze", freeze);
    query.bindValue(":pt", pt);
    query.bindValue(":name", name);
    query.bindValue(":count", count);
    query.bindValue(":price", price);
    query.bindValue(":duration", duration);
    query.bindValue(":active", activee?1:0);
    query.bindValue(":id", pack_id); // Assuming pack_id is your private attribute storing the ID

    if (query.exec()) {
        qDebug() << "Data updated successfully.";
        QMessageBox::information(this, "Success", "Data updated successfully.");
        pack_id = -1;
        emit added();
    } else {
        qDebug() << "Error updating data:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update data:\n" + query.lastError().text());
    }
    ui->pack_edit->setEnabled(true);

}
void packages::pack_delete(){
    if (pack_id == -1) {
        QMessageBox::critical(this, "No Search", "Please search first to delete.");
        return;
    }

    QString packageName = ui->name->text().trimmed();
    if (packageName.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Package name cannot be empty.");
        return;
    }

    // Ask for confirmation before deleting
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Are you sure you want to delete the package: " + packageName + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM package_on_desk WHERE id = :id");
        query.bindValue(":id", pack_id);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Package deleted successfully.");
            clearData();
            emit added();
            qDebug() << "Package deleted successfully.";
            pack_id = -1; // Reset pack_id
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete package:\n" + query.lastError().text());
            qDebug() << "Error deleting package:" << query.lastError().text();
        }
    } else {
        QMessageBox::information(this, "Deletion Canceled", "Deletion canceled.");
        qDebug() << "Deletion canceled.";
    }
}
void packages::pt_save(){
    QString name = ui->name_pt->text().trimmed();
    QString priceStr = ui->price_pt->text().trimmed();
    int count = ui->count_pt->value();
    int ptValue = ui->pt->value(); // Assuming pt is a QSpinBox or similar
    // Validate name is not empty
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name cannot be empty.");
        return; // Exit function if name is empty
    }

    // Validate price is not empty and convert to integer
    if (priceStr.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Price cannot be empty.");
        return; // Exit function if price is empty
    }


    bool ok;
    int price = priceStr.toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Price must be a valid integer.");
        return; // Exit function if price is not a valid integer
    }
    // Check if name already exists in pt_ondesk table
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM pt_ondesk WHERE name = :name");
    checkQuery.bindValue(":name", name);
    if (checkQuery.exec() && checkQuery.next()) {
        QMessageBox::critical(this, "Input Error", "Name already exists. Please choose a different name.");
        return; // Exit function if name already exists
    }

    // Validate pt and count are not equal to zero
    if (ptValue == 0 || count == 0) {
        QMessageBox::critical(this, "Input Error", "PT and Count must be greater than zero. or -1 in unlimited");
        return; // Exit function if pt or count are zero
    }

    // Validate and convert other values as needed

    // Get the next available ID for pt_ondesk table
    int maxId = 0;
    QSqlQuery queryMaxId("SELECT COALESCE(MAX(id), 0) FROM pt_ondesk");
    if (queryMaxId.next()) {
        maxId = queryMaxId.value(0).toInt() + 1; // Increment max ID by 1
    }

    // Insert data into pt_ondesk table
    QSqlQuery query;
    query.prepare("INSERT INTO pt_ondesk (id, name, date_added, value, count, num_sessions) "
                  "VALUES (:id, :name,  GETDATE(), :value, :count, :num_sessions )"); // Assuming default values for these columns
    query.bindValue(":id", maxId);
    query.bindValue(":name", name);
    query.bindValue(":value", price);
    query.bindValue(":count", count);
    query.bindValue(":num_sessions", ptValue);



    if (query.exec()) {
        qDebug() << "Data inserted successfully into pt_ondesk.";
        QMessageBox::information(this, "Success", "Data inserted successfully into pt_ondesk.");
        clearData_pt(); // Clear UI fields or perform any other necessary actions
    } else {
        qDebug() << "Error inserting data into pt_ondesk:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to insert data into pt_ondesk:\n" + query.lastError().text());
    }

}
void packages::pt_search(){
    QString searchName = ui->name_pt->text().trimmed();

    // Validate if searchName is not empty
    if (searchName.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Please enter a name to search.");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM pt_ondesk WHERE name = :name");
    query.bindValue(":name", searchName);

    if (query.exec()) {
        if (query.next()) {
            pt_id=query.value("id").toInt();
            QString name = query.value("name").toString();
            int count = query.value("count").toInt();
            int price = query.value("value").toInt();
            int pt = query.value("num_sessions").toInt();
            // Populate UI elements with retrieved data
            ui->name_pt->setText(name);
            ui->count_pt->setValue(count);
            ui->price_pt->setText(QString::number(price));
            ui->pt->setValue(pt);

            QMessageBox::information(this, "Success", "Package found and loaded.");
        } else {
            QMessageBox::information(this, "Not Found", "No package found with that name.");
        }
    } else {
        qDebug() << "Error searching data:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to search data:\n" + query.lastError().text());
    }

}
void packages::pt_edit(){
    if (pt_id == -1) {
        QMessageBox::critical(this, "No Search", "Please search first to edit.");
        return;
    }
    QString name = ui->name_pt->text().trimmed();
    QString priceStr = ui->price_pt->text().trimmed();
    int count = ui->count_pt->value();
    int ptValue = ui->pt->value(); // Assuming pt is a QSpinBox or similar

    // Validate name is not empty
    if (name.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Name cannot be empty.");
        return; // Exit function if name is empty
    }

    // Validate price is not empty and convert to integer
    if (priceStr.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Price cannot be empty.");
        return; // Exit function if price is empty
    }


    bool ok;
    int price = priceStr.toInt(&ok);
    if (!ok) {
        QMessageBox::critical(this, "Input Error", "Price must be a valid integer.");
        return; // Exit function if price is not a valid integer
    }

    // Validate pt and count are not equal to zero
    if (price == 0 || count == 0 || ptValue==0 ) {
        QMessageBox::critical(this, "Input Error", "PT and Count must be greater than zero. or -1 in unlimited");
        return; // Exit function if pt or count are zero
    }

    // Get the next available ID for pt_ondesk table
    QSqlQuery queryUpdate;
    queryUpdate.prepare("UPDATE pt_ondesk SET name = :name, value = :value, count = :count, num_sessions = :num_sessions "
                        "WHERE id = :id");
    queryUpdate.bindValue(":name", name);
    queryUpdate.bindValue(":value", price);
    queryUpdate.bindValue(":count", count);
    queryUpdate.bindValue(":num_sessions", ptValue);
    queryUpdate.bindValue(":id", pt_id);


    if (queryUpdate.exec()) {
        qDebug() << "Data inserted successfully into pt_ondesk.";
        QMessageBox::information(this, "Success", "Data inserted successfully into pt_ondesk.");
        clearData_pt(); // Clear UI fields or perform any other necessary actions
        pt_id=-1;
    } else {
        qDebug() << "Error inserting data into pt_ondesk:" << queryUpdate.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to insert data into pt_ondesk:\n" + queryUpdate.lastError().text());
    }



}

void packages::pt_delete(){
    if (pt_id == -1) {
        QMessageBox::critical(this, "No Search", "Please search first to delete.");
        return;
    }

    QString packageName = ui->name_pt->text().trimmed();
    if (packageName.isEmpty()) {
        QMessageBox::critical(this, "Input Error", "Package name cannot be empty.");
        return;
    }

    // Ask for confirmation before deleting
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Delete",
                                  "Are you sure you want to delete the package: " + packageName + "?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM pt_ondesk WHERE id = :id");
        query.bindValue(":id", pt_id);

        if (query.exec()) {
            QMessageBox::information(this, "Success", "Package deleted successfully.");
            clearData_pt();
            qDebug() << "Package deleted successfully.";
            pt_id = -1; // Reset pt_id
        } else {
            QMessageBox::critical(this, "Error", "Failed to delete package:\n" + query.lastError().text());
            qDebug() << "Error deleting package:" << query.lastError().text();
        }
    } else {
        QMessageBox::information(this, "Deletion Canceled", "Deletion canceled.");
        qDebug() << "Deletion canceled.";
    }

}

void packages::closeEvent(QCloseEvent *event) {
    emit pack_closed();  // Emit the signal when the widget is closed
    qDebug() << "pack widget closed";
    QWidget::closeEvent(event);  // Call the base class implementation
}
void packages::updateIcon(){
    if(ui->active->isChecked()){
        ui->active->setIcon(QIcon(":/login/correct.png"));
    }
    else {
        ui->active->setIcon(QIcon(":/login/cross.png"));
    }
}
packages::~packages()
{
    delete ui;
}
