#include "search.h"
#include "ui_search.h"
#include <QCloseEvent>

search::search(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::search)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("DRIVER={ODBC Driver 17 for SQL Server};"
                       "SERVER=LAPTOP-ONHG8FN6;"
                       "DATABASE=zktecho;"
                       "UID=nesa;"
                       "PWD=123698745");




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
    #widget, #widget_2, #widget_7 {
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
)";
    this->setStyleSheet(darkStyleSheet);

    QString darkStyle_table = "QTableWidget {"
                              "    background-color: #171010; "   // Dark background color
                              "    color: #FFFFFF; "              // Light text color
                              "}"
                              "QHeaderView::section {"
                              "    background-color: #31363F; "   // Header background color
                              "    color: #FFFFFF; "              // Header text color
                              "    padding: 4px; "                // Header padding
                              "}"
                              "QTableWidget::item {"
                              "    background-color: #212A3E; "   // Table item background color
                              "}"
                              "QTableWidget::item:selected {"
                              "    background-color: #FF8C00; "   // Selected item background color
                              "    color: #FFFFFF; "              // Selected item text color
                              "}";

    ui->nas->setStyleSheet(darkStyle_table);
    QStringList headers;
    headers << "ID" << "Name" << "Mob1";
    ui->nas->setColumnCount(3);
    ui->nas->setHorizontalHeaderLabels(headers);
    QHeaderView *header = ui->nas->horizontalHeader();

    header->setSectionResizeMode(0, QHeaderView::ResizeToContents); // Optional: Resize column 0 to its contents
    header->setSectionResizeMode(1, QHeaderView::Stretch);          // Stretch column 1
    header->setSectionResizeMode(2, QHeaderView::Stretch);

    connect(ui->search_2,&QPushButton::clicked,this,&search::searching);
    connect(ui->nas, &QTableWidget::cellClicked, this, &search::onCellClicked);
    connect(ui->nas, &QTableWidget::cellDoubleClicked, this, &search::onCellDoubleClicked);


    ui->nas->setEditTriggers(QAbstractItemView::NoEditTriggers);


}
void search::closeEvent(QCloseEvent *event)
{
    emit closed(currentid);  // Emit the signal with the current ID
    QWidget::closeEvent(event);
}
void search::searching(){
    ui->search_2->setDisabled(true);
    ui->prof->clear();
    ui->id_2->clear();
    QString name=ui->name->text().trimmed();
    QString mob=ui->mob->text().trimmed();

    // Initialize the SQL query string and parameters
    QString queryString = "SELECT id, name, mob_1 FROM customer WHERE 1=1"; // Select id, name, and mob_1

    // Use a list to hold the query parameters
    QList<QPair<QString, QVariant>> queryParams;

    // Add conditions based on non-empty fields
    if (!name.isEmpty()) {
        queryString += " AND name LIKE :name";
        queryParams.append(qMakePair("name", "%"+ name + "%"));
    }
    if (!mob.isEmpty()) {
        queryString += " AND (mob_1 LIKE :mob OR mob_2 LIKE :mob)";
        queryParams.append(qMakePair("mob",  mob + "%"));
    }

    // Prepare and execute the query
    QSqlQuery query;
    query.prepare(queryString);

    // Bind parameters
    for (const auto& param : queryParams) {
        query.bindValue(":" + param.first, param.second);
    }

    if (!query.exec()) {
        // Handle query execution error
        qDebug() << "Query execution error:" << query.lastError().text();
        return;
    }

    // Clear previous results
    ui->nas->setRowCount(0);



    // Populate the QTableWidget with the results
    while (query.next()) {
        int row = ui->nas->rowCount();
        ui->nas->insertRow(row);

        for (int col = 0; col < 3; ++col) {
            ui->nas->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
        }
    }
    ui->search_2->setEnabled(true);
}
void search::onCellClicked(int row, int column){
    ui->prof->clear();
    ui->id_2->clear();
    QString id = ui->nas->item(row, 0)->text();

    QSqlQuery query;
    query.prepare("SELECT name, mob_1, personal_image, card_image FROM customer WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec() && query.next()) {
        QString name = query.value("name").toString();
        QString mob = query.value("mob_1").toString();
        QString personalImage = query.value("personal_image").toString();
        QString cardImage = query.value("card_image").toString();

        ui->name->setText(name);
        ui->mob->setText(mob);

        // Load personal image from path
        QPixmap pixmapp(personalImage);
        if (!pixmapp.isNull()) {
            ui->prof->setPixmap(pixmapp);
        } else {
            qDebug() << "Failed to load personal image from path:" << personalImage;
        }

        // Load card image from path
        QPixmap pixmapid(cardImage);
        if (!pixmapid.isNull()) {
            ui->id_2->setPixmap(pixmapid);
        } else {
            qDebug() << "Failed to load card image from path:" << cardImage;
        }
    } else {
        qDebug() << "Query failed: " << query.lastError();
    }

}

void search::onCellDoubleClicked(int row ,int column){
    currentid= ui->nas->item(row, 0)->text().trimmed().toInt();

    // Emit the custom signal with the ID parameter
    close();

}
void search::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        ui->search_2->click();
        event->accept(); // Indicate that the event has been handled
        return; // Stop further processing
    }
    // Call base class method to handle other key events
    QWidget::keyPressEvent(event);
}


search::~search()
{
    delete ui;
}
