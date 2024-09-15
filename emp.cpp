#include "emp.h"
#include "ui_emp.h"

emp::emp(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::emp)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER={ODBC Driver 18 for SQL Server};"
                       "SERVER=DESKTOP-9L5QUCK;"
                       "DATABASE=Number1;"
                       "UID=sa;"
                       "PWD=p@ssw0rd;"
                       "TrustServerCertificate=yes;"
                       "Integrated Security=false;");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
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

    /* Specific widget styling */
    #widget, #widget_2, #widget_17, #widget_18 {
        border: 2px solid #94FFD8;
        border-radius: 5px;
        padding: 5px;
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

    /* QDateEdit styling */
    QDateEdit {
        background-color: #395B64;
        border: 1px solid #555555;
        border-radius: 5px;
        padding: 5px;
        color: #E0E0E0;
    }

    QDateEdit::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: top right;
        width: 15px;
        border-left-width: 1px;
        border-left-color: darkgray;
        border-left-style: solid;
        border-top-right-radius: 3px;
        border-bottom-right-radius: 3px;
    }

    QDateEdit::down-arrow {
        width: 10px;
        height: 10px;
    }

    QDateEdit:disabled {
        background-color: #6C6C6C; /* Gray background */
        color: #A0A0A0; /* Lighter text color */
        border: 1px solid #A0A0A0; /* Lighter border color */
    }

    /* QTableWidget styling */
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

    /* QComboBox styling */
    QComboBox {
        background-color: #395B64;
        border: 1px solid #555555;
        border-radius: 5px;
        padding: 5px;
        color: #E0E0E0;
    }

    QComboBox::drop-down {
        subcontrol-origin: padding;
        subcontrol-position: top right;
        width: 15px;
        border-left-width: 1px;
        border-left-color: darkgray;
        border-left-style: solid;
        border-top-right-radius: 3px;
        border-bottom-right-radius: 3px;
    }

    QComboBox::down-arrow {
        width: 10px;
        height: 10px;
        image: url(:/login/arrow-down.png); /* Ensure this path is correct */
    }

    QComboBox QAbstractItemView {
        background-color: #2C3333;
        border: 1px solid #555555;
        color: #FFFFFF;
        selection-background-color: #FF8C00;
        selection-color: #FFFFFF;
    }

    QComboBox:hover {
        border: 1px solid #AAAAAA;
    }

    QComboBox:disabled {
        background-color: #6C6C6C;
        color: #A0A0A0;
        border: 1px solid #A0A0A0;
    }
)";
    index=-1;

    this->setStyleSheet(darkStyleSheet);

    // Set the number of columns
    ui->embtable->setColumnCount(1); // Example with 3 columns

    // Set the header labels
    QStringList headers;
    headers << "Name" ;  // Example header names
    ui->embtable->setHorizontalHeaderLabels(headers);

    // Add 9 empty rows
    ui->embtable->setRowCount(12);
    ui->embtable->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Optional: Make the columns stretch to fit the table width
    ui->embtable->horizontalHeader()->setStretchLastSection(true);
    ui->embtable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(ui->search, &QPushButton::clicked, this, &emp::searchAndUpdateTable);
    connect(ui->embtable, &QTableWidget::cellDoubleClicked, this, &emp::onTableCellDoubleClicked);
    connect(ui->save, &QPushButton::clicked, this, &emp::save);
    connect(ui->delete_2,&QPushButton::clicked,this ,&emp::del);

    connect(ui->type, &QComboBox::currentIndexChanged, [this](int) {
        this->index = -1;
        ui->name->clear();
        ui->embtable->clearContents();
        ui->embtable->setRowCount(12);
    });


}

void emp::searchAndUpdateTable() {
    ui->search->setDisabled(true);
    index=-1;
    QString selectedType = ui->type->currentText();
    QString searchName = ui->name->text().trimmed();
    QString tableName;

    // Determine which table to use based on the selected type
    if (selectedType == "Sales") {
        tableName = "saales"; // Replace with your actual sales table name
    } else if (selectedType == "Captain") {
        tableName = "cap"; // Replace with your actual captain table name
    } else {
        ui->search->setEnabled(true);
        return;
    }

    // Clear previous results from the table
    ui->embtable->setRowCount(0);

    QSqlQuery query;
    QString queryString;

    // Prepare the query based on whether searchName is empty or not
    if (searchName.isEmpty()) {
        queryString = QString("SELECT name FROM %1").arg(tableName);
    } else {
        queryString = QString("SELECT name FROM %1 WHERE name LIKE :name").arg(tableName);
    }

    query.prepare(queryString);

    if (!searchName.isEmpty()) {
        query.bindValue(":name", "%" + searchName + "%");
    }

    if (!query.exec()) {
        QMessageBox::critical(nullptr, "Query Error", query.lastError().text());
        ui->search->setEnabled(true);
        return;
    }

    // Populate the QTableWidget with search results
    while (query.next()) {
        QString name = query.value(0).toString();

        int row = ui->embtable->rowCount();
        ui->embtable->insertRow(row);

        QTableWidgetItem* item = new QTableWidgetItem(name);
        ui->embtable->setItem(row, 0, item);
    }

    // Ensure the table has at least 12 rows
    int rowCount = ui->embtable->rowCount();
    if (rowCount < 12) {
        ui->embtable->setRowCount(12);
    }
    QTimer::singleShot(20, this, [this]() { ui->search->setEnabled(true); });

}
void emp::onTableCellDoubleClicked(int row, int column){
    index=row;
}
void emp::save() {
    ui->save->setDisabled(true);
    QString selectedType = ui->type->currentText();
    QString tableName;
    QString idColumnName;

    // Determine the table and ID column based on the selected type
    if (selectedType == "Sales") {
        tableName = "saales"; // Replace with your actual sales table name
    } else if (selectedType == "Captain") {
        tableName = "cap"; // Replace with your actual captain table name
        idColumnName = "id"; // ID column name
    } else {
        QMessageBox::warning(this, "Invalid Type", "Please select a valid type.");
        ui->save->setEnabled(true);
        return;
    }

    // Get the name from the QLineEdit
    QString newName = ui->name->text().trimmed();

    // Check if the name is empty
    if (newName.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Name cannot be empty.");
        ui->save->setEnabled(true);
        return;
    }

    // Prepare and execute the insertion query
    QSqlQuery insertQuery;
    QString insertQueryString;

    if (selectedType == "Captain") {
        // Get the next ID for Captain
        int nextId = -1;
        QSqlQuery query;
        query.prepare(QString("SELECT MAX(%1) FROM %2").arg(idColumnName).arg(tableName));

        if (!query.exec()) {
            QMessageBox::critical(this, "Query Error", query.lastError().text());
            ui->save->setEnabled(true);
            return;
        }

        if (query.next()) {
            QVariant maxIdVariant = query.value(0);
            int maxId = maxIdVariant.isNull() ? 0 : maxIdVariant.toInt();
            nextId = maxId + 1;
        }

        // Prepare the insertion query for Captain
        insertQueryString = QString("INSERT INTO %1 (%2, name) VALUES (:id, :name)").arg(tableName).arg(idColumnName);
        insertQuery.prepare(insertQueryString);
        insertQuery.bindValue(":id", nextId);
    } else {
        // Prepare the insertion query for Sales
        insertQueryString = QString("INSERT INTO %1 (name) VALUES (:name)").arg(tableName);
        insertQuery.prepare(insertQueryString);
    }
    // Bind the value for 'name'
    insertQuery.bindValue(":name", newName);

    // Execute the insertion query
    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Query Error", insertQuery.lastError().text());
        ui->save->setEnabled(true);
        return;
    }

    emit employee();
    // Clear previous results from the table
    ui->embtable->setRowCount(0);

    // Optional: Refresh the table if needed
    ui->embtable->clearContents();

    // Add empty rows up to a total of 12 rows
    ui->embtable->setRowCount(12);

    // Reset index after insertion
    index = -1;

    // Clear the name field
    ui->name->clear();

    // Optionally trigger any additional actions (like a search)
    ui->search->click();

    QTimer::singleShot(30, this, [this]() { ui->save->setEnabled(true); });
}

void emp::del(){
    ui->delete_2->setDisabled(true);
    if (index == -1) {
        QMessageBox::warning(this, "No Selection", "Please double-click a row first to select it.");
        ui->delete_2->setEnabled(true);
        return;
    }

    QString selectedType = ui->type->currentText();
    QString tableName;

    // Determine the table based on the selected type
    if (selectedType == "Sales") {
        tableName = "saales"; // Replace with your actual sales table name
    } else if (selectedType == "Captain") {
        tableName = "cap"; // Replace with your actual captain table name
    } else {
        QMessageBox::warning(this, "Invalid Type", "Please select a valid type.");
        ui->delete_2->setEnabled(true);
        return;
    }

    // Get the name from the selected row in the QTableWidget
    QString searchName = ui->embtable->item(index, 0)->text().trimmed();

    // Confirm deletion with user
    if (QMessageBox::question(this, "Confirm Deletion",
                              QString("Are you sure you want to delete '%1' from the %2 ?").arg(searchName, tableName),
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        ui->delete_2->setEnabled(true);
        return;
    }

    // Prepare and execute the deletion query
    QSqlQuery query;
    query.prepare(QString("DELETE FROM %1 WHERE name = :name").arg(tableName));
    query.bindValue(":name", searchName);

    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
        ui->delete_2->setEnabled(true);
        return;
    }
    emit employee();


    // Optional: Refresh the table if needed
    ui->embtable->clearContents();

    // Add empty rows up to a total of 12 rows
    ui->embtable->setRowCount(12);

    // Reset index after deletion
    index = -1;

    ui->name->clear();
    ui->search->click();
    QTimer::singleShot(10, this, [this]() { ui->delete_2->setEnabled(true); });




}
void emp::closeEvent(QCloseEvent *event) {
    emit emp_closed();  // Emit the signal when the widget is closed
    qDebug() << "emp widget closed";
    QWidget::closeEvent(event);  // Call the base class implementation
}

emp::~emp()
{
    delete ui;
}
