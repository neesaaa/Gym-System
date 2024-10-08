#include "member.h"
#include "ui_member.h"
#include <QDebug>  // Include QDebug header
#include<QDate>
#include<QFileDialog>
#include <QBuffer>
#include <QSqlError>
#include <QMessageBox>
#include<QTimer>
#include<QMetaType>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QRegularExpression>
#include <QSqlQueryModel>
#include <QTableView>// Include the QRegularExpression header
#include "search.h"


Member::Member(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Member)
{
    ui->setupUi(this);

    setWindowTitle("Member");
    // Set dark stylesheet for the entire Member widget
    QString darkStyle = "QWidget {"
                        "background-color: #171010; "
                        "color: #FFFFFF; "
                        "}"
                        "QLabel, QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox {"
                        "background-color: #171010; "
                        "color: #FFFFFF; "
                        "}"
                        "QPushButton {"
                        "border: 2px solid #FFA62F; "
                        "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #290001, stop:1 #87431D); "
                        "color: #FFFFFF; "
                        "}"
                        "QPushButton:hover {"
                        "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF8C00, stop:1 #F05941); "
                        "}";

    this->setStyleSheet(darkStyle);
    ui->payment->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Apply individual styles if needed
    QString commonStyle = "border: 2px solid #222831; background-color: #171010; color: #FFFFFF;";
    QString combinedStyles = " QWidget#widget_5, QWidget#widget_6, QWidget#widget_7, QWidget#widget_8 {"
                             "border: 2px solid #31363F; background-color: #171010; color: #FFFFFF; } "
                             "QWidget#widget_3 ,QWidget#widget_4,QWidget#widget_2{"
                             "border: 2px solid #DFF5FF; background-color: #000000; color: #FFFFFF; }";
    ui->imageid->setStyleSheet("border: 2px solid #31363F; background-color: #212A3E; color:#FFFFFF;");
    ui->imagep->setStyleSheet("border: 2px solid #31363F; background-color: #212A3E; color:#FFFFFF");
    ui->dateEdit->setStyleSheet(commonStyle);
    ui->name->setStyleSheet(commonStyle);
    ui->tabWidget->setStyleSheet(commonStyle);
    ui->note->setStyleSheet(commonStyle);
    ui->mob1->setStyleSheet(commonStyle);
    ui->mob2->setStyleSheet(commonStyle);
    ui->id->setStyleSheet(commonStyle);
    ui->gender->setStyleSheet(commonStyle);
    ui->widget->setStyleSheet(combinedStyles);
    ui->widget_9->setStyleSheet("border: 2px solid #C7C8CC; background-color: #171010; color: #FFFFFF;");
    ui->sales->setStyleSheet(commonStyle);

    // Additional styles for buttons
    QString buttonStyle = "QPushButton {"
                          "border: 2px solid #F6F4EB; "
                          "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #205375, stop:1 #112B3C); "
                          "color: #FFFFFF; "
                          "}"
                          "QPushButton:hover {"
                          "background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #205375, stop:1 #F4CE14); "
                          "}";
    ui->save->setStyleSheet(buttonStyle);
    ui->Search->setStyleSheet(buttonStyle);
    ui->free_id->setStyleSheet(buttonStyle);
    ui->Delete->setStyleSheet(buttonStyle);
    ui->left->setStyleSheet(buttonStyle);
    ui->right->setStyleSheet(buttonStyle);
    ui->show->setStyleSheet(buttonStyle);
    ui->save_pay->setStyleSheet(buttonStyle);
    ui->edit_pa->setStyleSheet(buttonStyle);
    ui->delete_pay->setStyleSheet(buttonStyle);

    QString payment_style = "QWidget#widget_13, QWidget#widget_15 , QWidget#widget_17,QWidget#widget_20{"
                            "border:2px solid #F0EBE3;"
                            "}"
                            "QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox {"
                            "background-color: #171010; "
                            "color: #FFFFFF; "
                            "border:1px solid #31363F;"
                            "}";
    QString pt_style = "QWidget#widget_47, QWidget#widget_48, QWidget#widget_58 {"
                       "border: 2px solid #F0EBE3;"
                       "}"
                       "QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox {"
                       "background-color: #171010; "
                       "color: #FFFFFF; "
                       "border: 1px solid #31363F;"
                       "}";

    QString tabWidgetStyle = R"(
        QTabWidget::pane {
            border: 2px solid #DFF5FF;
        }
        QTabBar::tab {
            background: #31363F;
            color: #FFFFFF;
            border: 1px solid #DFF5FF;
            padding: 5px;
        }
        QTabBar::tab:selected {
            background: #FFFBDA;
            color: #000000;
            border: 2px solid #DFF5FF;
        }
        QTabBar::tab:hover {
            background: #344C64;
            color: #FFFFFF;
        }
    )";
    ui->tabWidget->setTabIcon(1,QIcon(":/login/money.png"));

    ui->tab->setStyleSheet(payment_style);
    ui->tab_2->setStyleSheet(payment_style);
    ui->tab_3->setStyleSheet(pt_style);

    ui->tabWidget->setStyleSheet(tabWidgetStyle);


    ui->dateEdit->setDate(QDate::currentDate());
    ui->pay_date->setDate(QDate::currentDate());

    ui->imageid->setText("Double click load ID");
    //image double click
    ui->imagep->setMouseTracking(true);
    ui->imagep->installEventFilter(this);
    ui->imageid->setMouseTracking(true);
    ui->imageid->installEventFilter(this);

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
    free_id();


    // Connect the save button to the onSaveButtonClicked slot
    connect(ui->save, &QPushButton::clicked, this, &Member::onSaveButtonClicked);
    connect(ui->Search, &QPushButton::clicked, this, &Member::seearch);
    connect(ui->free_id, &QPushButton::clicked, this, &Member::free_id);
    connect(ui->Delete, &QPushButton::clicked, this, &Member::deletee);
    connect(ui->left, &QPushButton::clicked, this, &Member::left);
    connect(ui->right, &QPushButton::clicked, this, &Member::right);
    connect(ui->show, &QPushButton::clicked, this, &Member::showwing);
    connect(ui->save_pay, &QPushButton::clicked, this, &Member::pay_save);
    connect(ui->delete_pay, &QPushButton::clicked, this, &Member::delete_pay);
    connect(ui->payment, &QTableWidget::cellDoubleClicked, this, &Member::onPaymentCellDoubleClicked);
    connect(ui->all, &QTableWidget::cellDoubleClicked, this, &Member::onalldoubleclicked);

    connect(ui->edit_pa, &QPushButton::clicked, this, &Member::edit_pay);
    connect(ui->pack_save, &QPushButton::clicked, this, &Member::pack_save);
    connect(ui->pack_edit, &QPushButton::clicked, this, &Member::pack_edit);
    connect(ui->pack_delete,&QPushButton::clicked,this,&Member::pack_delete);

    connect(ui->pack_start, &QDateEdit::dateChanged, this, [=](const QDate &date) {
        updateEndDate(date); // Call with default value of dur (0 or any default you set)
    });
    connect(ui->specs_pack, &QTableWidget::cellClicked, this, &Member::onCellClicked);


    //tabeles styles

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

    ui->payment->setStyleSheet(darkStyle_table);
    ui->specs_pack->setStyleSheet(darkStyle_table);
    ui->all->setStyleSheet(darkStyle_table);
    ui->log->setStyleSheet(darkStyle_table);
    ui->freeze_table->setStyleSheet(darkStyle_table);
    ui->pt_table->setStyleSheet(darkStyle_table);
    ui->invtable->setStyleSheet(darkStyle_table);


    QSqlQuery query;
    query.prepare(R"(
    SELECT name
    FROM package_on_desk
    WHERE active = 1
    ORDER BY start_date
)");
    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error in package names", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString packageName = query.value(0).toString();
        ui->pack_combo->addItem(packageName);
    }

    QString styleSheet = "QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox {"
                         "background-color: #171010; "
                         "color: #FFFFFF; "
                         "border: 1px solid #31363F;}"
                         "QWidget#widget_24,QWidget#widget_32,QWidget#widget_31,QWidget#widget_37,QWidget#widget_43,QWidget#widget_38{"
                         "border:2px solid #EEEEEE;"
                         "}";

    // Apply the stylesheet to tab_2
    ui->tab_2->setStyleSheet(styleSheet);
    ui->tab_5->setStyleSheet(styleSheet);
    ui->tab_6->setStyleSheet(styleSheet);


    ui->pack_start->setDate(QDate::currentDate());
    ui->pack_end->setDate(QDate::currentDate());

    connect(ui->pack_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(onPackComboBoxSelectionChanged(int)));
    connect(ui->pack_dis, SIGNAL(textChanged(const QString &)), this, SLOT(onPayDiscChanged(const QString &)));
    // Assuming this is in your constructor or initialization function
    connect(ui->start_shift, QOverload<int>::of(&QSpinBox::valueChanged), this, &Member::change_in_shift);
    connect(ui->adder, QOverload<int>::of(&QSpinBox::valueChanged), this, &Member::add_on_end_date);

    ui->all->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->freeze_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->specs_pack->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->pt_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    onPackComboBoxSelectionChanged(0);


    //freeze
    ui->freeze_start->setDate(QDate::currentDate());
    ui->freeze->setDate(QDate::currentDate());


    blockSignalsFlag=false;

    connect(ui->freeze_count, SIGNAL(valueChanged(int)), this, SLOT(FreezeChangeDate(int)));
    // Connect the QDateEdit signal to the slot
    connect(ui->freeze, SIGNAL(dateChanged(QDate)), this, SLOT(freezezboxchange(QDate)));
    connect(ui->save_freeze, &QPushButton::clicked, this, &Member::save_freeze_slot);
    connect(ui->freeze_table, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(onFreezeTableDoubleClicked(int,int)));
    connect(ui->freeze_edit, &QPushButton::clicked, this, &Member::edit_freeze);
    connect(ui->freez_delete, &QPushButton::clicked, this, &Member::delete_freeze);
    connect(ui->save_pt,&QPushButton::clicked,this,&Member::save_pt);
    connect(ui->pt_edit,&QPushButton::clicked,this,&Member::pt_edit);
    connect(ui->pt_delete,&QPushButton::clicked,this,&Member::pt_delete);

    connect(ui->invsave,&QPushButton::clicked,this,&Member::save_inv);


    freezing_id=-1;
    package_id=-1;
    pt_id=-1;

    ui->freeze_table->setColumnCount(7); // Number of columns
    QStringList headers;
    headers << "ID" << "Customer ID" << "Package ID" << "Start Date" << "End Date" << "Days" <<"Reason";
    ui->freeze_table->setHorizontalHeaderLabels(headers);
    ui->freeze_table->setColumnWidth(6,400);

    QStringList paymentHeaders = {"ID", "Type", "Date", "Amount", "Note"};
    int cols = paymentHeaders.size();
    ui->payment->setColumnCount(cols);
    ui->payment->setHorizontalHeaderLabels(paymentHeaders);
    // Adjust column widths
    ui->payment->resizeColumnsToContents(); // Adjust other columns first
    ui->payment->setColumnWidth(1, 150); // Set width for 'Type' column
    ui->payment->setColumnWidth(4, 250);

    // Set headers for the package table
    QStringList packageHeaders = {"ID","Day registered", "Package Name", "Package Value","Discount", "Start Date", "End Date" ,"After Discount" , "Total Paid"};
    ui->all->setColumnCount(packageHeaders.size());

    QStringList logHeaders = {"Finger print ID", "Time"};
    QStringList invHeaders = {"ID","name","Phone Number", "Time"};
    ui->invtable->setColumnCount(invHeaders.size());
    ui->invtable->setHorizontalHeaderLabels(invHeaders);
    ui->invtable->setRowCount(6);
    ui->invtable->setColumnWidth(3, 500);
    ui->invtable->setColumnWidth(2, 200);


    ui->log->setColumnCount(logHeaders.size());
    ui->log->setHorizontalHeaderLabels(logHeaders);
    ui->log->setColumnWidth(1, 600);

    ui->all->setHorizontalHeaderLabels(packageHeaders);
    ui->all->resizeColumnsToContents(); // Adjust other columns first

    pack_idd_for_inv=-1;

    // Populate the QTableWidget
    ui->freeze_table->setRowCount(2);
    ui->freeze_table->resizeColumnsToContents(); // Adjust other columns first
    ui->all->setRowCount(2);
    ui->payment->setRowCount(8);
    ui->log->setRowCount(9);
    ui->pt_table->setRowCount(3);    // Clear existing rows



    //pt logic
    QSqlQuery query_pt;
    query_pt.prepare("SELECT name FROM pt_ondesk");

    if (!query_pt.exec()) {
        qDebug() << "Query execution error: in pt displaying  " << query_pt.lastError();
        return;
    }

    ui->pt_pack->clear(); // Clear existing items in the combo box

    while (query_pt.next()) {
        QString name = query_pt.value("name").toString();
        ui->pt_pack->addItem(name);
    }
    //change value by pt selcection
    connect(ui->pt_pack, QOverload<const QString &>::of(&QComboBox::currentTextChanged),
            this, &Member::updatePtValue);

    ui->pt_pack->setCurrentIndex(1);
    inv_id=-1;

    connect(ui->pt_discount, &QLineEdit::textChanged, this, &Member::updatePtNet);// Assuming ui->invtable is a QTableWidget
    connect(ui->invtable, &QTableWidget::cellDoubleClicked, this, &Member::on_invtable_doubleClicked);
    connect(ui->invdelete, &QPushButton::clicked, this, &Member::inv_delete);



    QSqlQuery query_cap;
    query_cap.prepare("SELECT name FROM cap");

    // Execute the query
    if (!query_cap.exec()) {
        qDebug() << "Error executing query_cap:" << query_cap.lastError().text();
        return; // Handle error as needed
    }

    // Populate combo box with names from cap table
    while (query_cap.next()) {
        QString name = query_cap.value("name").toString();
        ui->pt_cap->addItem(name);
    }

    ui->pt_table->setColumnCount(8);

    // Set header labels
    ui->pt_table->setHorizontalHeaderLabels(QStringList() << "Date" << "Package Name" << "Value" << "Discount" << "Package ID" <<"Pt Id" <<"Captain"<<"Num Sessions");

    ui->pt_table->resizeColumnsToContents();
    connect(ui->pt_table, &QTableWidget::itemDoubleClicked, this, &Member::pt_table_select);

    connect(ui->pt_table, &QTableWidget::doubleClicked, this, &Member::onPtTableDoubleClicked);

    QSqlQuery salesQuery;
    salesQuery.prepare("SELECT name FROM saales");

    if (!salesQuery.exec()) {
        qDebug() << "Failed to execute sales query:" << salesQuery.lastError().text();
        return;
    }

    ui->sales->clear(); // Assuming comboBox is the name of your QComboBox

    while (salesQuery.next()) {
        QString name = salesQuery.value(0).toString();
        ui->sales->addItem(name);
    }



    ui->freezebox->setDisabled(true);

}

Member::~Member()
{
    if (db.isOpen())
    {
        db.close();
    }
    delete ui;
}
void Member::closeEvent(QCloseEvent *event) {
    emit memberClosed();  // Emit the signal when the widget is closed
    qDebug() << "Member widget closed";
    QWidget::closeEvent(event);  // Call the base class implementation
}
bool Member::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        QLabel *label = qobject_cast<QLabel*>(obj);
        if (!label)
            return false;

        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image File"), "", tr("Images (*.png *.xpm *.jpg *.jpeg *.bmp *.gif)"));
        if (!fileName.isEmpty())
        {
            QPixmap pixmap(fileName);
            pixmap = pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
            label->setPixmap(pixmap);
            label->setScaledContents(true);
        }
        return true;
    }
    return QObject::eventFilter(obj, event);
}
void Member::clear_tables(){
    ui->payment->clearContents();
    ui->pt_table->clearContents();// Clear the contents of all cells
    ui->payment->setRowCount(8);
    ui->pt_table->setRowCount(3);

    ui->all->clearContents(); // Clear the contents of all cells
    ui->all->setRowCount(2);
    ui->freeze_table->clearContents();
    ui->freeze_table->setRowCount(2);
    //ui->freeze_table->resizeColumnsToContents(); // Adjust other columns first
    ui->all->resizeColumnsToContents(); // Adjust other columns first
    //ui->payment->resizeColumnsToContents();

    //ui->pt_table->resizeColumnsToContents();

    clearRow(ui->specs_pack, 1);

}
void Member::clear_data(){
    ui->name->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->note->clear();
    ui->mob1->clear();
    ui->mob2->clear();
    ui->imagep->clear();
    ui->imageid->clear();
    ui->gender->setCurrentIndex(0);


    ui->payment->clearContents();
    ui->pt_table->clearContents();// Clear the contents of all cells
    ui->payment->setRowCount(8);
    ui->pt_table->setRowCount(3);

    ui->all->clearContents(); // Clear the contents of all cells
    ui->all->setRowCount(2);
    ui->freeze_table->clearContents();
    ui->freeze_table->setRowCount(2);
    ui->freeze_table->resizeColumnsToContents(); // Adjust other columns first
    ui->all->resizeColumnsToContents(); // Adjust other columns first
    ui->payment->resizeColumnsToContents(); // Adjust other columns first

    ui->pt_table->resizeColumnsToContents(); // Adjust other columns first
    clearRow(ui->specs_pack, 1);

}
void Member::free_id(){
    QSqlQuery query;
    query.prepare("SELECT MAX(id) FROM customer");
    if(!query.exec()||!query.next()){
        qDebug()<<"eroor free_id";
    }
    else {
        int id=query.value(0).toInt();
        ui->id->setValue(id+1);
    }
    clear_data();
}
void Member::onSaveButtonClicked()
{
    // Disable the save button temporarily to prevent multiple clicks
    ui->save->setEnabled(false);

    // Create a QTimer instance
    QTimer *delayTimer = new QTimer(this);
    delayTimer->setSingleShot(true); // Fire timer only once

    // Connect the timeout signal of the QTimer to a lambda function
    QString mob1 = ui->mob1->text();
    QString mob2 = ui->mob2->text();
    QString name = ui->name->text();
    static QRegularExpression re("^[0-9]{11}$"); // Regular expression for at least 11 numeric characters

    if (name.isEmpty()) {
        QMessageBox::warning(this, "إدخال غير صحيح", "الاسم فاضى .");
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }

    if (!re.match(mob1).hasMatch()) {
        QMessageBox::warning(this, "إدخال غير صحيح", "الارقام مش 11");
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }

    if (mob2.isEmpty()) {
        QMessageBox::warning(this, "إدخال غير صحيح", "موبيل التانى فاضى");
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }
    // Define the directory to save images
    QString appDir = QCoreApplication::applicationDirPath();
    QString imageDirectoryName = "saved_images";
    QString imageDirectory = appDir + "/" + imageDirectoryName;

    // Define the backup directory on D:
    QString backupDirectory = "C:/saved_images";

    // Function to ensure a directory exists and create it if necessary
    auto ensureDirectoryExists = [](const QString& directory) -> bool {
        QDir dir(directory);
        if (!dir.exists()) {
            if (!dir.mkpath(directory)) {
                qDebug() << "Failed to create directory: " << directory;
                return false;
            } else {
                qDebug() << "Directory created successfully: " << directory;
            }
        } else {
            qDebug() << "Directory already exists: " << directory;
        }
        return true;
    };

    // Ensure both directories exist
    if (!ensureDirectoryExists(imageDirectory) || !ensureDirectoryExists(backupDirectory)) {
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }

    // Function to save an image to a given path
    auto saveImage = [](const QPixmap& pixmap, const QString& path) -> bool {
        if (!pixmap.isNull()) {
            if (!pixmap.save(path, "PNG")) {
                qDebug() << "Failed to save image at path:" << path;
                return false;
            }
        }
        return true;
    };

    // Initialize paths for both images
    QString timestamp = QDateTime::currentDateTime().toString("yyyyMMddHHmmss");
    QString imagePPath = imageDirectory + "/personal_" + timestamp + ".png";
    QString imageIDPath = imageDirectory + "/id_" + timestamp + ".png";
    QString backupPPath = backupDirectory + "/personal_" + timestamp + ".png";
    QString backupIDPath = backupDirectory + "/id_" + timestamp + ".png";

    // Save personal image if it exists
    QPixmap pixmapP = ui->imagep->pixmap(Qt::ReturnByValue);
    if (!saveImage(pixmapP, imagePPath) || !saveImage(pixmapP, backupPPath)) {
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }

    // Save ID image if it exists
    QPixmap pixmapID = ui->imageid->pixmap(Qt::ReturnByValue);
    if (!saveImage(pixmapID, imageIDPath) || !saveImage(pixmapID, backupIDPath)) {
        ui->save->setEnabled(true); // Re-enable save button
        return;
    }

    qDebug() << "Images saved successfully in both directories.";

    int customerId = ui->id->value();
    QDate joinDate = ui->dateEdit->date();
    QString note = ui->note->toPlainText();
    QString salesName = ui->sales->currentText();
    bool gender = ui->gender->currentText() == "Male"; // Assuming "Male" is true, otherwise false

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM customer WHERE id = :id");
    checkQuery.bindValue(":id", customerId);
    if (!checkQuery.exec() || !checkQuery.next())
    {
        QMessageBox::critical(this, "Database Error", checkQuery.lastError().text());
        ui->save->setEnabled(true);
        return;
    }

    int count = checkQuery.value(0).toInt();
    QSqlQuery query;

    if (count > 0) // Record exists, perform update
    {
        query.prepare("UPDATE customer SET personal_image = :personal_image, card_image = :card_image, join_date = :join_date, name = :name, mob_1 = :mob_1, mob_2 = :mob_2, note = :note, sales_name = :sales_name, gender = :gender WHERE id = :id");
    }
    else // Record does not exist, perform insert
    {
        query.prepare("INSERT INTO customer (id, personal_image, card_image, join_date, name, mob_1, mob_2, note, sales_name, gender) "
                      "VALUES (:id, :personal_image, :card_image, :join_date, :name, :mob_1, :mob_2, :note, :sales_name, :gender)");
    }

    query.bindValue(":id", customerId);
    query.bindValue(":personal_image", imagePPath.isEmpty() ? QVariant() : imagePPath);
    query.bindValue(":card_image", imageIDPath.isEmpty() ? QVariant() : imageIDPath);
    query.bindValue(":join_date", joinDate);
    query.bindValue(":name", name);
    query.bindValue(":mob_1", mob1);
    query.bindValue(":mob_2", mob2);
    query.bindValue(":note", note);
    query.bindValue(":sales_name", salesName);
    query.bindValue(":gender", gender);

    // Debugging output: print the SQL query before execution
    qDebug() << "SQL Query: " << query.lastQuery();

    // Execute query and check for errors
    if (!query.exec())
    {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
    else
    {
        QMessageBox::information(this, "Success", "Data saved successfully!");
    }

    // Re-enable the save button after processing
    QTimer::singleShot(100, this, [this]() { ui->save->setEnabled(true); });



}

void Member::deletee()
{
    int idToDelete = ui->id->value();  // Get the ID to delete from the spin box
    ui->Delete->setEnabled(false);

    // Check if the ID exists in the database
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM customer WHERE id = :id");
    checkQuery.bindValue(":id", idToDelete);

    if (!checkQuery.exec() || !checkQuery.next()) {
        qDebug() << "Error checking if ID exists:" << checkQuery.lastError().text();
        ui->Delete->setEnabled(true);
        return;
    }

    int count = checkQuery.value(0).toInt();

    if (count == 0) {
        QMessageBox::warning(this, "No Data", "No data related to that ID.");
        clear_data();
        ui->Delete->setEnabled(true);
        return;
    }

    // Retrieve paths to images to be deleted, if they exist
    QSqlQuery getImagePathsQuery;
    getImagePathsQuery.prepare("SELECT personal_image, card_image FROM customer WHERE id = :id");
    getImagePathsQuery.bindValue(":id", idToDelete);

    if (!getImagePathsQuery.exec() || !getImagePathsQuery.next()) {
        qDebug() << "Error retrieving image paths:" << getImagePathsQuery.lastError().text();
        ui->Delete->setEnabled(true);
        return;
    }

    QString personalImagePath = getImagePathsQuery.value("personal_image").toString();
    QString cardImagePath = getImagePathsQuery.value("card_image").toString();

    // Proceed with deletion from the database
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM customer WHERE id = :id");
    deleteQuery.bindValue(":id", idToDelete);

    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Database Error", deleteQuery.lastError().text());
        ui->Delete->setEnabled(true);
        return;
    }

    QMessageBox::information(this, "Success", "Member deleted successfully.");


    free_id();

    // Delete images from disk, if they exist
    if (!personalImagePath.isEmpty()) {
        QFile personalImageFile(personalImagePath);
        if (personalImageFile.exists()) {
            if (!personalImageFile.remove()) {
                qDebug() << "Failed to delete personal image file:" << personalImageFile.errorString();
            }
        }
    }

    if (!cardImagePath.isEmpty()) {
        QFile cardImageFile(cardImagePath);
        if (cardImageFile.exists()) {
            if (!cardImageFile.remove()) {
                qDebug() << "Failed to delete card image file:" << cardImageFile.errorString();
            }
        }
    }
    QTimer::singleShot(100, this, [this]() { ui->Delete->setEnabled(true); });

}

void Member::seearch(int i=0){
    ui->Search->setDisabled(true);
    int id = ui->id->value();
    if(i==0){
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Confirm");
    msgBox.setText("Customer with ID " + QString::number(id) + " اسيرش بالاى دى ده ولا مش عارفه اصلا?");
    QPushButton *yesButton = msgBox.addButton("مش عارفه لاء", QMessageBox::YesRole);
    QPushButton *noButton = msgBox.addButton("هو ده", QMessageBox::NoRole);

    msgBox.exec();

    if (msgBox.clickedButton() == yesButton) {
        search search_win;
        QEventLoop loop;

        // Connect the closed signal to the quit slot of the event loop
        QObject::connect(&search_win, &search::closed, [&](const int &idd) {
            if(idd!=-1){
            id = idd;  // Store the emitted ID
            ui->id->setValue(idd);
            }
            loop.quit();  // Quit the event loop
        });


        search_win.setAttribute(Qt::WA_DeleteOnClose);  // Optional: delete the widget when closed
        search_win.show();  // Show the search window

        // Start the event loop to wait for the search window to close
        loop.exec();

    }
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM customer WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                qDebug() << "ID exists in the database.";

                // Prepare a new query to retrieve the customer's details
                QSqlQuery detailsQuery;
                detailsQuery.prepare("SELECT * FROM customer WHERE id = :id");
                detailsQuery.bindValue(":id", id);

                if (detailsQuery.exec()) {
                    if (detailsQuery.next()) {
                        // Retrieve customer details
                        QString name = detailsQuery.value("name").toString().trimmed();
                        QString mob1 = detailsQuery.value("mob_1").toString().trimmed();
                        QString mob2 = detailsQuery.value("mob_2").toString().trimmed();
                        QDate joinDate = detailsQuery.value("join_date").toDate();
                        QString cardImage = detailsQuery.value("card_image").toString().trimmed();
                        QString personalImage = detailsQuery.value("personal_image").toString().trimmed();
                        QString note = detailsQuery.value("note").toString().trimmed();
                        QString salesName = detailsQuery.value("sales_name").toString().trimmed();
                        QString gender = detailsQuery.value("gender").toString();
                        ui->sales->setCurrentText(salesName);

                        // Display the customer details



                        // Further actions to display these details in your UI can be added here
                        QPixmap personalPixmap(personalImage);
                        QPixmap cardPixmap(cardImage);
                        ui->name->setText(name);
                        ui->dateEdit->setDate(joinDate);
                        ui->note->setText(note);
                        ui->mob1->setText(mob1);
                        ui->mob2->setText(mob2);
                        if (gender == "Male")
                        {
                            ui->gender->setCurrentIndex(1); // Assuming "Male" is at index 1 (0-based index)
                        }
                        else if (gender == "Female")
                        {
                            ui->gender->setCurrentIndex(2); // Assuming "Female" is at index 2 (0-based index)
                        }

                        // Assuming ui->imagep and ui->imageid are QLabel objects
                        ui->imagep->setPixmap(personalPixmap.scaled(ui->imagep->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                        ui->imageid->setPixmap(cardPixmap.scaled(ui->imageid->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));


                    }
                } else {
                    qDebug() << "Details query execution failed: " << detailsQuery.lastError();
                }
            }
            else {
                clear_data();
                ui->name->setText("كلام ده مش على السستم شيك على الاى دى");
                ui->dateEdit->setDate(QDate::currentDate());
            }
            //clear_tables();

        }
    } else {
        qDebug() << "Query execution failed: " << query.lastError();
    }
    ui->show->click();
    ui->Search->setEnabled(true);
}
void Member::left(){
    ui->left->setEnabled(false);
    if(ui->id->value()>0){
        ui->id->setValue((ui->id->value())-1);
        seearch(-1);
    }
    ui->left->setEnabled(true);

}
void Member::right(){
    ui->right->setEnabled(false);

    ui->id->setValue((ui->id->value())+1);
    seearch(-1);
    ui->right->setEnabled(true);


}
void Member::showwing() {
    ui->show->setDisabled(true);
    int id = ui->id->value();
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM customer WHERE id = :id");
    query.bindValue(":id", id);
    ui->pay_date->setDate(QDate::currentDate());

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            if (count > 0) {
                qDebug() << "ID exists in the database.";

                // Clear existing data in the payments table
                ui->freeze_table->clearContents();
                ui->freeze_table->setRowCount(2);
                ui->all->clearContents();
                ui->all->setRowCount(2);

                ui->payment->clearContents();
                ui->payment->setRowCount(8);

                ui->pt_table->clearContents();
                ui->pt_table->setRowCount(8);




                // Retrieve payment details for the customer
                QSqlQuery detailsQuery;
                detailsQuery.prepare("SELECT id, type, date_pay, amount, note FROM payment WHERE customer_id = :id ORDER BY date_pay DESC, id DESC");
                detailsQuery.bindValue(":id", id);
                qDebug()<<"payment";

                if (detailsQuery.exec()) {
                    // Populate the table with the retrieved data
                    int row = 0;
                    ui->payment->setRowCount(detailsQuery.size());
                    while (detailsQuery.next()) {
                        ui->payment->setItem(row, 0, new QTableWidgetItem(detailsQuery.value("id").toString()));
                        ui->payment->setItem(row, 1, new QTableWidgetItem(detailsQuery.value("type").toString()));
                        ui->payment->setItem(row, 2, new QTableWidgetItem(detailsQuery.value("date_pay").toString()));
                        ui->payment->setItem(row, 3, new QTableWidgetItem(detailsQuery.value("amount").toString()));
                        ui->payment->setItem(row, 4, new QTableWidgetItem(detailsQuery.value("note").toString()));
                        row++;
                    }
                    ui->payment->resizeColumnsToContents(); // Adjust other columns first
                    ui->payment->setColumnWidth(4, 400);


                    // Package query
                    QSqlQuery specsQuery;
                    specsQuery.prepare("SELECT inbody, pt, inv, freezze, spa, id, end_date FROM paackage WHERE customer_id = :id ORDER BY start_date DESC");
                    specsQuery.bindValue(":id", id);
                    qDebug()<<"specs";


                    if (!specsQuery.exec() || !specsQuery.next()) {
                        qDebug()<<"مفيش باكدج للاى دى ده";
                        clearRow(ui->specs_pack, 1);
                        ui->show->setEnabled(true);
                        //return;
                    }
                    QDate endDate = specsQuery.value("end_date").toDate();
                    bool flag=1;
                    if(endDate<QDate::currentDate()){
                        qDebug()<<"مفيش باكدج اكتيف";
                        flag=0;
                    }
                    pack_idd_for_inv = specsQuery.value(5).toInt();
                    if(flag){
                        int inbody = specsQuery.value(0).toInt();
                        int pt = specsQuery.value(1).toInt();
                        int inv = specsQuery.value(2).toInt();
                        int freeze = specsQuery.value(3).toInt();
                        int spa = specsQuery.value(4).toInt();
                        // Populate table cells with data
                        ui->specs_pack->setItem(1, 0, new QTableWidgetItem(QString::number(inbody)));
                        ui->specs_pack->setItem(1, 1, new QTableWidgetItem(QString::number(pt)));
                        ui->specs_pack->setItem(1, 2, new QTableWidgetItem(QString::number(inv)));
                        ui->specs_pack->setItem(1, 3, new QTableWidgetItem(QString::number(freeze)));
                        ui->specs_pack->setItem(1, 4, new QTableWidgetItem(QString::number(spa)));
                    }
                    //ui->specs_pack->resizeColumnsToContents(); // Adjust other columns first


                    // Retrieve package details for the customer
                    QSqlQuery packageQuery;
                    packageQuery.prepare(R"(
                            SELECT
                                p.id,
                                p.today_date,
                                pod.name,
                                pod.price,
                                p.discount,
                                p.start_date,
                                p.end_date,
                                p.net,  -- Include net column
                                COALESCE(SUM(py.amount), 0) AS total_amount
                            FROM
                                paackage p
                            JOIN
                                package_on_desk pod ON p.pack_id = pod.id
                            LEFT JOIN
                                payment py ON p.id = py.pack_id AND py.pt_id IS NULL
                            WHERE
                                p.customer_id = :customer_id
                            GROUP BY
                                p.id, p.today_date, pod.name, pod.price, p.discount, p.start_date, p.end_date, p.net  -- Include net column in GROUP BY
                            ORDER BY
                                p.start_date DESC
                        )");

                    packageQuery.bindValue(":customer_id", id);
                    qDebug()<<"all";


                    if (!packageQuery.exec()) {
                        QMessageBox::critical(this, "Database Error", packageQuery.lastError().text());
                        ui->show->setEnabled(true);
                        return;
                    }

                    // Populate the package table
                    ui->all->setRowCount(0); // Clear existing rows
                    while (packageQuery.next()) {
                        int row = ui->all->rowCount();
                        ui->all->insertRow(row);

                        ui->all->setItem(row, 0, new QTableWidgetItem(packageQuery.value("id").toString())); // ID column
                        ui->all->setItem(row, 1, new QTableWidgetItem(packageQuery.value("today_date").toDate().toString("yyyy-MM-dd")));
                        ui->all->setItem(row, 2, new QTableWidgetItem(packageQuery.value("name").toString()));
                        ui->all->setItem(row, 3, new QTableWidgetItem(packageQuery.value("price").toString()));
                        ui->all->setItem(row, 4, new QTableWidgetItem(packageQuery.value("discount").toString()));
                        ui->all->setItem(row, 5, new QTableWidgetItem(packageQuery.value("start_date").toDate().toString("yyyy-MM-dd")));
                        ui->all->setItem(row, 6, new QTableWidgetItem(packageQuery.value("end_date").toDate().toString("yyyy-MM-dd")));
                        ui->all->setItem(row, 7, new QTableWidgetItem(packageQuery.value("net").toString())); // Net column
                        ui->all->setItem(row, 8, new QTableWidgetItem(packageQuery.value("total_amount").toString())); // Total amount column
                    }

                    ui->all->resizeColumnsToContents();

                    QSqlQuery query_1;
                    query_1.prepare("SELECT id, customer_id, package_id, start_date, end_date, note, count "
                                    "FROM freeze_schedule WHERE customer_id = :customer_id "
                                    "ORDER BY start_date, id DESC");

                    query_1.bindValue(":customer_id", id);

                    if (!query_1.exec()) {
                        qDebug() << "Query execution error:" << query_1.lastError().text();
                        ui->show->setEnabled(true);
                        return;
                    }
                    qDebug()<<"freeze_table";




                    row = 0;
                    while (query_1.next()) {
                        ui->freeze_table->insertRow(row);
                        ui->freeze_table->setItem(row, 0, new QTableWidgetItem(query_1.value(0).toString())); // ID
                        ui->freeze_table->setItem(row, 1, new QTableWidgetItem(query_1.value(1).toString())); // Customer ID
                        ui->freeze_table->setItem(row, 2, new QTableWidgetItem(query_1.value(2).toString())); // Package ID
                        ui->freeze_table->setItem(row, 3, new QTableWidgetItem(query_1.value(3).toDate().toString("yyyy-MM-dd"))); // Start Date
                        ui->freeze_table->setItem(row, 4, new QTableWidgetItem(query_1.value(4).toDate().toString("yyyy-MM-dd"))); // End Date
                        ui->freeze_table->setItem(row, 5, new QTableWidgetItem(query_1.value(6).toString())); // Count
                        ui->freeze_table->setItem(row, 6, new QTableWidgetItem(query_1.value(5).toString())); // Note
                        row++;
                    }
                    ui->freeze_table->resizeColumnsToContents(); // Adjust other columns first

                    //pt

                    QSqlQuery ptQuery;
                    ptQuery.prepare("SELECT pt.date AS pt_date, pt.pt_ondesk_id, pt.package_id, pt.discount, pt.net, pt.cap_id, pt.id, pt.num_sessions "
                                    "FROM pt "
                                    "JOIN paackage ON pt.package_id = paackage.id "
                                    "WHERE paackage.customer_id = :customerId "
                                    "ORDER BY pt.date DESC, pt.id DESC");
                    ptQuery.bindValue(":customerId", id);



                    // Execute the SQL Query
                    if (!ptQuery.exec()) {
                        qDebug() << "Failed to execute PT query:" << ptQuery.lastError().text();
                        ui->show->setEnabled(true);
                        return; // Or handle the error appropriately
                    }
                    qDebug()<<"pt";

                    // Clear existing content in pt_table
                    ui->pt_table->clearContents(); // Only clears cell contents, not headers
                    ui->pt_table->setRowCount(3); // Ensure table is empty initially

                    // Populate ui->pt_table with query results
                    row = 0;
                    while (ptQuery.next()) {
                        int pt_ondesk_id = ptQuery.value("pt_ondesk_id").toInt();

                        // Fetch pt_ondesk_name
                        QSqlQuery query_pt_name;
                        query_pt_name.prepare("SELECT name FROM pt_ondesk WHERE id = :id");
                        query_pt_name.bindValue(":id", pt_ondesk_id);

                        QString pt_ondesk_name;
                        if (query_pt_name.exec() && query_pt_name.next()) {
                            pt_ondesk_name = query_pt_name.value(0).toString();
                        } else {
                            qDebug() << "Failed to retrieve pt_ondesk name for pt_ondesk_id:" << pt_ondesk_id;
                            qDebug() << "Error:" << query_pt_name.lastError().text();
                            continue; // Skip current row if name retrieval fails
                        }

                        // Fetch cap_name
                        int cap_id = ptQuery.value("cap_id").toInt();
                        QSqlQuery query_cap_name;
                        query_cap_name.prepare("SELECT name FROM cap WHERE id = :id");
                        query_cap_name.bindValue(":id", cap_id);

                        QString cap_name;
                        if (query_cap_name.exec() && query_cap_name.next()) {
                            cap_name = query_cap_name.value(0).toString();
                        } else {
                            qDebug() << "Failed to retrieve cap name for cap_id:" << cap_id;
                            qDebug() << "Error:" << query_cap_name.lastError().text();
                            continue; // Skip current row if name retrieval fails
                        }

                        // Populate ui->pt_table with fetched data including cap_name
                        ui->pt_table->insertRow(row);
                        ui->pt_table->setItem(row, 0, new QTableWidgetItem(ptQuery.value("pt_date").toDate().toString("yyyy-MM-dd")));
                        ui->pt_table->setItem(row, 1, new QTableWidgetItem(pt_ondesk_name)); // Package Name fetched dynamically
                        ui->pt_table->setItem(row, 2, new QTableWidgetItem(ptQuery.value("net").toString())); // Value fetched directly
                        ui->pt_table->setItem(row, 3, new QTableWidgetItem(ptQuery.value("discount").toString()));
                        ui->pt_table->setItem(row, 4, new QTableWidgetItem(ptQuery.value("package_id").toString()));
                        ui->pt_table->setItem(row, 5, new QTableWidgetItem(ptQuery.value("pt.id").toString()));
                        ui->pt_table->setItem(row, 6, new QTableWidgetItem(cap_name));// Display cap_name
                        ui->pt_table->setItem(row,7 ,new QTableWidgetItem(ptQuery.value("num_sessions").toString()));

                        row++;
                    }



                    // Resize columns to contents
                    ui->pt_table->resizeColumnsToContents();

                    // QSqlDatabase otherDb = QSqlDatabase::addDatabase("QSQLSERVER", "otherConnection"); // Replace "QSQLSERVER" with your database driver
                    // otherDb.setHostName("hostname"); // Replace with your database hostname
                    // otherDb.setDatabaseName("otherDatabase"); // Replace with the name of the database
                    // otherDb.setUserName("username"); // Replace with your database username
                    // otherDb.setPassword("password");
                    // if (!otherDb.open()) {
                    //     QMessageBox::critical(this, "Database Error", "Failed to connect to the database: " + otherDb.lastError().text());
                    //     ui->show->setEnabled(true);
                    //     return;
                    // }

                    qDebug()<< "wslt ++++";
                    QString queryString =
                        "SELECT Date, code, hour, minute "
                        "FROM CheckIN2 "
                        "WHERE code = :customer_id "
                        "ORDER BY Date DESC";


                    QSqlQuery query; //QSqlQuery query(otherDb)
                    query.prepare(queryString);
                    query.bindValue(":customer_id", id);

                    if (!query.exec()) {
                        QMessageBox::critical(this, "SQL Error", query.lastError().text());
                        ui->show->setEnabled(true);
                        // return;
                    }

                    // Clear the table before populating new data
                    ui->log->clearContents();
                    ui->log->setRowCount(0); // Reset row count

                    row = 0;

                    // Populate the table with the retrieved data
                    // Populate the table with the retrieved data
                    while (query.next()) {
                        QString rawDate = query.value("Date").toString();
                        QString rawHour = query.value("hour").toString();
                        QString rawMinute = query.value("minute").toString();

                        // Extract year, month, and day
                        QString year = rawDate.mid(0, 4);
                        QString month = rawDate.mid(4, 2);
                        QString day = rawDate.mid(6, 2);

                        // Combine the date parts with dashes
                        QString formattedDate = year + "-" + month + "-" + day;

                        QString combinedDateTime = formattedDate + " " + rawHour + ":" + rawMinute;



                        ui->log->insertRow(row);
                        QTableWidgetItem *customerIdItem = new QTableWidgetItem(query.value("code").toString());
                        QTableWidgetItem *timeItem = new QTableWidgetItem(combinedDateTime);

                        ui->log->setItem(row, 0, customerIdItem); // Customer ID column
                        ui->log->setItem(row, 1, timeItem);       // Time column

                        row++;
                    }

                    ui->log->setRowCount(std::max(row,9));
                    // Close the connection
                    //otherDb.close();

                    QSqlQuery queryinv;
                    queryinv.prepare("SELECT id, name, phone_number, time FROM inv WHERE pack_id = :pack_id");
                    queryinv.bindValue(":pack_id", pack_idd_for_inv);

                    if (!queryinv.exec()) {
                        qDebug() << "Error executing query:" << queryinv.lastError().text();
                        ui->show->setEnabled(true);
                        return;
                    }

                    ui->invtable->clearContents();
                    ui->invtable->setRowCount(0); // Clear all existing rows

                    // Populate the QTableWidget with the query results
                    row = 0;
                    while (queryinv.next()) {
                        int id = queryinv.value(0).toInt();
                        QString name = queryinv.value(1).toString();
                        QString phone_number = queryinv.value(2).toString();
                        QDateTime time = queryinv.value(3).toDateTime();

                        ui->invtable->insertRow(row);
                        ui->invtable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
                        ui->invtable->setItem(row, 1, new QTableWidgetItem(name));
                        ui->invtable->setItem(row, 2, new QTableWidgetItem(phone_number));
                        ui->invtable->setItem(row, 3, new QTableWidgetItem(time.toString("yyyy-MM-dd hh:mm:ss")));

                        row++;
                    }

                    ui->invtable->setRowCount(std::max(row,6));




                }
                else {
                    qDebug() << "Details query execution failed: " << detailsQuery.lastError();
                }
            }
            else {
                clearRow(ui->specs_pack, 1);
                qDebug() << "ID does not exist in the database.";
            }
        }
    } else {
        qDebug() << "Count query execution failed: " << query.lastError();
    }
    package_id = -1;
    QTimer::singleShot(40, this, [this]() { ui->show->setEnabled(true); });


}


void Member::pay_save() {
    ui->save_pay->setDisabled(true);
    QSqlQuery maxIdQuery;
    maxIdQuery.prepare("select max(id) from payment");

    // Start a QTimer to re-enable the save button after 200 milliseconds

    if (!maxIdQuery.exec() || !maxIdQuery.next()) {
        qDebug() << "Error retrieving maximum id:" << maxIdQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to retrieve maximum id from payment table.");
        ui->save_pay->setEnabled(true);
        return;
    }

    int maxId = maxIdQuery.value(0).toInt();
    int nextId = maxId + 1;

    // Get payment details from UI elements
    QString type = ui->pay_type->currentText();
    QDate date_pay = ui->pay_date->date();
    int cus_id = ui->id->value();
    QString amountStr = ui->pay_value->text();
    bool ok;
    int amount = amountStr.toInt(&ok);
    if (!ok) {
        qDebug() << "Failed to convert amount to integer";
        QMessageBox::critical(this, "Input Error", "Invalid amount entered. Please enter a valid number.");
        ui->save_pay->setEnabled(true);
        return;
    }
    QString note = ui->pay_note->toPlainText();
    int pack_id = ui->pack_id_pay->value();

    // Insert query with manually assigned id
    QSqlQuery insertQuery;

    if (pack_id != 0 ) {  // Assuming pack_id is 0 when it's null
        insertQuery.prepare("INSERT INTO payment (id, type, date_pay, customer_id, amount, note, pack_id) "
                            "VALUES (:id, :type, :date_pay, :customer_id, :amount, :note, :pack_id)");

        insertQuery.bindValue(":pack_id", pack_id);
    } else {
        insertQuery.prepare("INSERT INTO payment (id, type, date_pay, customer_id, amount, note) "
                            "VALUES (:id, :type, :date_pay, :customer_id, :amount, :note)");
    }

    insertQuery.bindValue(":id", nextId);
    insertQuery.bindValue(":type", type);
    insertQuery.bindValue(":date_pay", date_pay);
    insertQuery.bindValue(":customer_id", cus_id);
    insertQuery.bindValue(":amount", amount);
    insertQuery.bindValue(":note", note);

    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Payment record inserted successfully.");
    }
    // Clear the input fields
    ui->pay_note->clear();
    ui->pay_value->clear();
    ui->pay_type->setCurrentIndex(0);
    ui->pay_date->setDate(QDate::currentDate());
    ui->pack_id_pay->setValue(0);

    // Optionally, you may also want to update the UI to show the new payment record
    ui->show->click();
    QTimer::singleShot(80, this, [this]() {
        ui->save_pay->setEnabled(true);
    });
}


void Member::delete_pay() {
    // Disable the delete button to prevent multiple clicks
    ui->delete_pay->setDisabled(true);

    // Start a QTimer to re-enable the delete button after 300 milliseconds

    // Get the selected row in the table
    int selectedRow = ui->payment->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a payment record to delete.");
        ui->delete_pay->setEnabled(true); // Re-enable the delete button
        return;
    }

    // Retrieve the payment ID from the table
    QTableWidgetItem* idItem = ui->payment->item(selectedRow, 0); // Assuming ID is in the first column
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Selected payment record is invalid.");
        ui->delete_pay->setEnabled(true); // Re-enable the delete button
        return;
    }
    int paymentId = idItem->text().toInt();

    // Confirm deletion with user
    QMessageBox::StandardButton confirmDelete;
    confirmDelete = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this payment record?",
                                          QMessageBox::Yes | QMessageBox::No);
    if (confirmDelete == QMessageBox::No) {
        ui->delete_pay->setEnabled(true); // Re-enable the delete button
        return;
    }

    // Perform deletion from the database
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM payment WHERE id = :id");
    deleteQuery.bindValue(":id", paymentId);

    if (!deleteQuery.exec()) {
        qDebug() << "Error deleting payment record:" << deleteQuery.lastError().text();
        QMessageBox::critical(this, "Delete Error", "Failed to delete payment record:\n" + deleteQuery.lastError().text());
    } else {
        qDebug() << "Payment record deleted successfully!";
        QMessageBox::information(this, "Delete Successful", "Payment record deleted successfully!");

        // Remove the row from the table widget
        ui->payment->removeRow(selectedRow);

        ui->pay_note->clear();
        ui->pay_value->clear();
        ui->pay_type->setCurrentIndex(0);
        ui->pay_date->setDate(QDate::currentDate());
        ui->pack_id_pay->setValue(0);


        // Clear the selection
        ui->payment->setCurrentItem(nullptr);
        ui->show->click();
    }
    QTimer::singleShot(50, this, [this]() {
        ui->delete_pay->setEnabled(true);
    });

}

void Member::edit_pay() {
    ui->edit_pa->setDisabled(true);
    int selectedRow = ui->payment->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a payment record to edit.");
        return;
    }

    // Retrieve the payment ID from the table
    QTableWidgetItem* idItem = ui->payment->item(selectedRow, 0); // Assuming ID is in the first column
    if (!idItem) {
        QMessageBox::warning(this, "Error", "Selected payment record is invalid.");
        return;
    }
    int paymentId = idItem->text().toInt();

    // Get the new values from the UI elements
    QString type = ui->pay_type->currentText();
    QDate date_pay = ui->pay_date->date();
    QString amountStr = ui->pay_value->text();
    bool ok;
    int amount = amountStr.toInt(&ok);
    if (!ok) {
        qDebug() << "Failed to convert amount to integer";
        QMessageBox::critical(this, "Input Error", "Invalid amount entered. Please enter a valid number.");
        QTimer::singleShot(50, this, [this]() {
            ui->edit_pa->setEnabled(true);
        });
        return;
    }
    QString note = ui->pay_note->toPlainText();

    // Update query
    QSqlQuery updateQuery;
    int cus_id=ui->id->value();
    updateQuery.prepare("UPDATE payment SET type = :type, date_pay = :date_pay, customer_id = :customer_id, amount = :amount, note = :note "
                        "WHERE id = :id");

    updateQuery.bindValue(":id", paymentId);
    updateQuery.bindValue(":type", type);
    updateQuery.bindValue(":date_pay", date_pay);
    updateQuery.bindValue(":customer_id", cus_id); // Assuming customer_id is also updated, if not, remove this line
    updateQuery.bindValue(":amount", amount);
    updateQuery.bindValue(":note", note);

    if (!updateQuery.exec()) {
        qDebug() << "Error updating payment record:" << updateQuery.lastError();
        QMessageBox::critical(this, "Update Error", "Failed to update payment record:\n" + updateQuery.lastError().text());
    } else {
        qDebug() << "Payment record updated successfully!";
        QMessageBox::information(this, "Update Successful", "Payment record updated successfully!");
        ui->payment->setCurrentItem(nullptr);


        // Refresh the table view to reflect the changes
        ui->pay_note->clear();
        ui->pay_value->clear();
        ui->pay_type->setCurrentIndex(0);
        ui->pay_date->setDate(QDate::currentDate());
        ui->show->click();
        ui->pack_id_pay->setValue(0);

    }
    QTimer::singleShot(50, this, [this]() {
        ui->edit_pa->setEnabled(true);
    });
}
void Member::onPaymentCellDoubleClicked(int row, int column) {
    Q_UNUSED(column); // We don't need the column parameter for this operation

    qDebug() << "Double-clicked on row:" << row;

    // Retrieve the data from the selected row
    QTableWidgetItem* paymentId = ui->payment->item(row, 0);
    QTableWidgetItem* typeItem = ui->payment->item(row, 1); // Assuming Type is in the second column
    QTableWidgetItem* datePayItem = ui->payment->item(row, 2); // Assuming Date is in the third column
    QTableWidgetItem* amountItem = ui->payment->item(row, 3); // Assuming Amount is in the fifth column
    QTableWidgetItem* noteItem = ui->payment->item(row, 4); // Assuming Note is in the sixth column

    QSqlQuery query;


    // Prepare the SQL query to select pack_id from payment table
    query.prepare("SELECT pack_id FROM payment WHERE id = :id");
    query.bindValue(":id", paymentId->text().toInt());

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        return;
    }
    QString packId;

    // Check if the query returned a result
    if (query.next()) {
        // Retrieve the pack_id from the result
        packId = query.value(0).toString();
        qDebug() << "Pack ID:" << packId;

        // Use the pack_id as needed
    } else {
        qDebug() << "No record found for ID:" << paymentId;
        return;
    }

    // Ensure that all items are valid before using them
    if ( !typeItem || !datePayItem  || !amountItem) {
        QMessageBox::warning(this, "Error", "Selected payment record is invalid.");
        return;
    }

    // Populate the UI elements with the data from the selected row
    ui->pack_id_pay->setValue(packId.toInt());
    ui->pay_type->setCurrentText(typeItem->text());
    ui->pay_date->setDate(QDate::fromString(datePayItem->text(), "yyyy-MM-dd")); // Adjust format if needed
    ui->pay_value->setText(amountItem->text());

    // Check if noteItem is valid before setting text
    if (noteItem) {
        ui->pay_note->setPlainText(noteItem->text());
    } else {
        ui->pay_note->clear(); // Clear the note text edit if noteItem is invalid
    }
}

void Member::onPackComboBoxSelectionChanged(int index)
{
    QString selectedItem = ui->pack_combo->itemText(index).trimmed(); // Trim selected item

    // Query to fetch price of selected package
    QSqlQuery priceQuery;
    priceQuery.prepare("SELECT price FROM package_on_desk WHERE name = :name");
    priceQuery.bindValue(":name", selectedItem);

    if (!priceQuery.exec()) {
        QMessageBox::critical(this, "Query Error", priceQuery.lastError().text());
        return;
    }

    // Retrieve price if available
    if (priceQuery.next()) {
        QString value = priceQuery.value(0).toString();
        ui->pack_value->setText(value);
        onPayDiscChanged(ui->pack_dis->text());        // Set price in ui->pack_value
    } else {
        ui->pack_value->clear(); // Clear price field if no value found
        QMessageBox::information(this, "No Value", "No value found for the selected package.");
    }

    // Query to fetch package specifications
    QSqlQuery specsQuery;
    specsQuery.prepare("SELECT inbody, Pt, inv, freezze, spa  ,duration FROM package_on_desk WHERE name = :name");
    specsQuery.bindValue(":name", selectedItem);

    if (!specsQuery.exec()) {
        QMessageBox::critical(this, "Query Error", specsQuery.lastError().text());
        return;
    }

    // Clear previous contents of ui->specs_pack
    clearRow(ui->specs_pack,0);
    ui->specs_pack->setRowCount(2); // Set row count to 1 for the single row display

    // Set headers for the specs_pack table
    QStringList headers = {"Inbody", "Pt", "Inv", "Freeze", "Spa"};
    QStringList rows = {"Pack", "current"};
    ui->specs_pack->setVerticalHeaderLabels(rows);

    ui->specs_pack->setColumnCount(headers.size());
    ui->specs_pack->setHorizontalHeaderLabels(headers);

    // Populate ui->specs_pack with fetched specifications
    if (specsQuery.next()) {
        int inbody = specsQuery.value(0).toInt();
        int pt = specsQuery.value(1).toInt();
        int inv = specsQuery.value(2).toInt();
        int freeze = specsQuery.value(3).toInt();
        int spa = specsQuery.value(4).toInt();
        duration_package=specsQuery.value(5).toInt();

        // Populate table cells with data
        ui->specs_pack->setItem(0, 0, new QTableWidgetItem(QString::number(inbody)));
        ui->specs_pack->setItem(0, 1, new QTableWidgetItem(QString::number(pt)));
        ui->specs_pack->setItem(0, 2, new QTableWidgetItem(QString::number(inv)));
        ui->specs_pack->setItem(0, 3, new QTableWidgetItem(QString::number(freeze)));
        ui->specs_pack->setItem(0, 4, new QTableWidgetItem(QString::number(spa)));
        updateEndDate(ui->pack_start->date());
        //QSqlQuery specsQuery;
        // specsQuery.prepare("SELECT inbody, pt, inv, freezze, spa, id FROM paackage WHERE customer_id = :id ORDER BY start_date DESC");
        // specsQuery.bindValue(":id", ui->id->value());

        // if (!specsQuery.exec() || !specsQuery.next()) {
        //     QMessageBox::about(this, "", "No packages recorded.");
        //     clearRow(ui->specs_pack, 1);
        //     return;
        // }

        // inbody = specsQuery.value(0).toInt();
        // pt = specsQuery.value(1).toInt();
        // inv = specsQuery.value(2).toInt();
        // freeze = specsQuery.value(3).toInt();
        // spa = specsQuery.value(4).toInt();
        // package_id = specsQuery.value(5).toInt();

        // // Populate table cells with data
        // ui->specs_pack->setItem(1, 0, new QTableWidgetItem(QString::number(inbody)));
        // ui->specs_pack->setItem(1, 1, new QTableWidgetItem(QString::number(pt)));
        // ui->specs_pack->setItem(1, 2, new QTableWidgetItem(QString::number(inv)));
        // ui->specs_pack->setItem(1, 3, new QTableWidgetItem(QString::number(freeze)));
        // ui->specs_pack->setItem(1, 4, new QTableWidgetItem(QString::number(spa)));


        // Adjust column widths to contents
        ui->specs_pack->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    } else {
        // If no specifications found, inform the user
        QMessageBox::information(this, "No Data", "No specifications found for the selected package.");
    }

}



void Member::onPayDiscChanged(const QString &text)
{
    QString cleanText = text.trimmed(); // Remove any leading/trailing whitespace

    // Check if the text ends with '%'
    bool isPercentage = cleanText.endsWith('%');

    // Remove '%' if it exists
    if (isPercentage) {
        cleanText.chop(1); // Remove the '%' character
    }

    // Convert the cleaned text to a double
    bool ok;
    double discount = cleanText.toDouble(&ok);
    double value = ui->pack_value->text().toDouble();

    if (ok) {
        if (isPercentage && discount<100 && discount >=0 ) {
            // Percentage case: convert to absolute discount value
            discount = discount / 100.0 * value;
        }

        if (discount < value) {
            double netValue = value - discount;
            ui->pack_net->setText(QString::number(netValue, 'f', 2));  // Display net value with 2 decimal places
        } else {
            ui->pack_net->clear();
        }
    } else {
        ui->pack_net->clear();
    }
}
void Member::pack_save() {
    ui->pack_save->setDisabled(true);
    QString package_name = ui->pack_combo->currentText();
    int customer_id = ui->id->text().toInt();  // Assuming ui->id_ represents customer id

    QSqlQuery checker;
    checker.prepare("SELECT COUNT(*) FROM customer WHERE id = :id");
    checker.bindValue(":id", customer_id);

    if (checker.exec()) {
        checker.next(); // Move to the first (and only) result

        int count = checker.value(0).toInt();
        if (count == 0) {
            // Customer does not exist, trigger save button click
            ui->save->click();
        }
    }

    QSqlQuery packquery;
    packquery.prepare("SELECT id , inbody, spa , inv, freezze, pt, count  FROM package_on_desk WHERE name = :name");
    packquery.bindValue(":name", package_name);

    if (!packquery.exec()) {
        QMessageBox::critical(this, "Query Error", packquery.lastError().text());
        ui->pack_save->setEnabled(true);
        return;
    }

    // Retrieve id, price, and other values if available
    if (!packquery.next()) {
        QMessageBox::information(this, "No Value", "No package found with the selected name.");
        ui->pack_save->setEnabled(true);
        return;
    }
    QSqlQuery maxi;
    maxi.prepare("select max(id) from paackage");
    if(!maxi.exec() || !maxi.next()){
        QMessageBox::warning(this,"m4 la2y akbar package","sasas");
        return;
    }
    int id=maxi.value(0).toInt()+1;
    int pack_id = packquery.value("id").toInt();
    int inbody = packquery.value("inbody").toInt();
    int spa = packquery.value("spa").toInt();
    int inv = packquery.value("inv").toInt();
    int freezze = ui->freezebox->value() >= 1 ? ui->freezebox->value() : packquery.value("freezze").toInt();
    int pt = packquery.value("pt").toInt();
    int count=packquery.value("count").toInt();
    if (count == 0) {
        QMessageBox::information(nullptr, "Count Check", "Count for the package is zero.");
        ui->pack_save->setEnabled(true);
        return;
    }
    QString discount = ui->pack_dis->text();

    QString amountText = ui->pack_net->text().isEmpty()?ui->pack_value->text():ui->pack_net->text();

    // Attempt to convert the amountText to an integer
    float amountFloat = amountText.toFloat();
    int amount = qRound(amountFloat);
    QString net = QString::number(amount); // Convert amount to text

    // Insert into package table
    QSqlQuery insertQuery;
    insertQuery.prepare(R"(
    INSERT INTO paackage (
        id,
        customer_id,
        pack_id,
        inbody,
        spa,
        start_date,
        inv,
        freezze,
        pt,
        end_date,
        discount,
        net,
        today_date
    )
    VALUES (
        :id,
        :customer_id,
        :pack_id,
        :inbody,
        :spa,
        :start_date,
        :inv,
        :freezze,
        :pt,
        :end_date,
        :discount,
        :net,
        GETDATE()  -- Inserts the current date and time from SQL Server
    )
)");
    QDate packStartDate = ui->pack_start->date();
    QString start_date = packStartDate.toString("yyyy-MM-dd");

    QDate packEndDate = ui->pack_end->date();
    QString end_date = packEndDate.toString("yyyy-MM-dd");

    // Set parameters for the insert query
    insertQuery.bindValue(":id", id);  // Correct placeholder for id
    insertQuery.bindValue(":customer_id", customer_id);
    insertQuery.bindValue(":pack_id", pack_id);
    insertQuery.bindValue(":inbody", inbody);
    insertQuery.bindValue(":spa", spa);
    insertQuery.bindValue(":start_date", start_date);
    insertQuery.bindValue(":inv", inv);
    insertQuery.bindValue(":freezze", freezze);
    insertQuery.bindValue(":pt", pt);
    insertQuery.bindValue(":end_date", end_date);
    insertQuery.bindValue(":discount", discount);
    insertQuery.bindValue(":net", net);

    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Database Error", insertQuery.lastError().text());
    }
     else {
        qDebug() << "Insert query executed successfully.";
        QMessageBox::information(this, "Success", "Package inserted successfully.");
        // Handle success appropriately
    }
    // Update the count in package_on_desk
    QSqlQuery updateCountQuery;
    updateCountQuery.prepare(R"(
    UPDATE package_on_desk
    SET count = count - 1
    WHERE id = :id
    AND count > 0
    )");
    updateCountQuery.bindValue(":id", pack_id);

    if (!updateCountQuery.exec()) {
        QMessageBox::critical(this, "Update Error", updateCountQuery.lastError().text());
        ui->pack_save->setEnabled(true);
        return;
    }

    QSqlQuery maxIdQuery ;
    maxIdQuery.prepare(R"(
    SELECT COALESCE(MAX(id), 0) AS max_id
    FROM payment
    )");
    if (!maxIdQuery.exec() || !maxIdQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve maximum id: " + maxIdQuery.lastError().text());
        ui->pack_save->setEnabled(true);
        return;
    }

    int maxId = maxIdQuery.value(0).toInt();  // Retrieve the maximum id
    int newId = maxId + 1;  // Increment to get the new id

    QSqlQuery paymentQuery;
    paymentQuery.prepare("INSERT INTO payment (id, type, date_pay, customer_id, amount, note, pack_id) "
                         "VALUES (:id, :type, :date_pay, :customer_id, :amount, :note, :pack_id)");
    QString type = ui->pay_type_2->currentText();

    paymentQuery.bindValue(":id", newId);  // Bind the new id
    paymentQuery.bindValue(":pack_id", id);  // Correct placeholder for id
    paymentQuery.bindValue(":id", newId);  // Bind the new id
    paymentQuery.bindValue(":type", type);
    paymentQuery.bindValue(":date_pay", QDate::currentDate().toString("yyyy-MM-dd"));
    paymentQuery.bindValue(":customer_id", customer_id); // Assuming customer_id is defined somewhere
    paymentQuery.bindValue(":amount", amount);
    paymentQuery.bindValue(":note", ""); // Bind an empty string or actual note value

    // Execute the query to insert the record
    if (!paymentQuery.exec()) {
        QMessageBox::critical(this, "Insert Error", paymentQuery.lastError().text());
        ui->pack_save->setEnabled(true);
        return;
    }

    // QMessageBox::information(this, "Success", "payment inserted successfully.");
    ui->show->click();
    package_id = -1;


    // Optionally, clear UI elements or perform additional actions after successful insertion
    QTimer::singleShot(100, this, [this]() { ui->pack_save->setEnabled(true); });

}

void Member::pack_edit() {
    ui->pack_edit->setDisabled(true);
    if (package_id == -1) {
        QMessageBox::critical(this, "Error", "Double click on a row in the table below to edit before editing.");
        ui->pack_edit->setEnabled(true);
        return;
    }

    QString selectedPackageName = ui->pack_combo->currentText();
    qint64 packId = -1;

    // Query to get the pack_id based on the selected package name
    QSqlQuery getPackIdQuery;
    getPackIdQuery.prepare(R"(
    SELECT id, count
    FROM package_on_desk
    WHERE name = :name
    )");
    int count;
    getPackIdQuery.bindValue(":name", selectedPackageName);


    if (getPackIdQuery.exec() && getPackIdQuery.next()) {
        packId = getPackIdQuery.value(0).toLongLong();
        count = getPackIdQuery.value("count").toInt();
    } else {
        QMessageBox::critical(this, "Error", "Failed to retrieve pack ID: " + getPackIdQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }
    if (count == 0) {
        QMessageBox::information(nullptr, "Count Check", "Count for the new package is zero.");
        ui->pack_edit->setEnabled(true);
        return;
    }

    QSqlQuery countQuery;
    countQuery.prepare("SELECT COUNT(*) FROM freeze_schedule WHERE package_id = :packageId");
    countQuery.bindValue(":packageId", package_id);

    if (!countQuery.exec()) {
        qDebug() << "Error querying freeze schedule count:" << countQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to query freeze schedules count. Please try again.");
        return;
    }

    int freezeCount = 0;
    if (countQuery.next()) {
        freezeCount = countQuery.value(0).toInt();
    }

    // Step 2: If there are freeze schedules, show custom QMessageBox with options
    if (freezeCount > 0) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Delete Freeze ");
        msgBox.setText("There are freeze related to this package.");
        msgBox.setInformativeText("Do you want to delete all freeze schedules?");
        msgBox.setIcon(QMessageBox::Warning);
        QPushButton *deleteButton = msgBox.addButton(tr("امسح اى فريز "), QMessageBox::ActionRole);
        QPushButton *completeButton = msgBox.addButton(tr("لو معدلتش تاريخ البدا او قللت ايام الفريز متمسحش حاجه"), QMessageBox::ActionRole);
        QPushButton *cancelButton = msgBox.addButton(QMessageBox::Cancel);

        msgBox.exec();

        if (msgBox.clickedButton() == deleteButton) {
            // Delete all freeze schedules
            QSqlQuery deleteQuery;
            deleteQuery.prepare("DELETE FROM freeze_schedule WHERE package_id = :packageId");
            deleteQuery.bindValue(":packageId", package_id);

            if (!deleteQuery.exec()) {
                qDebug() << "Error deleting freeze schedules:" << deleteQuery.lastError().text();
                QMessageBox::critical(this, "Error", "Failed to delete freeze. Please try again.");
                ui->pack_edit->setEnabled(true);
                return;
            }

            QMessageBox::information(this, "Success", "All freeze schedules deleted successfully.");
        } else if (msgBox.clickedButton() == completeButton) {
            // Complete without deleting (do nothing)
            QMessageBox::information(this, "Complete", "Completed without deleting freeze.");
        } else {
            ui->pack_edit->setEnabled(true);
            return;
        }
    } else {
        QMessageBox::information(this, "Info", "No freeze schedules found for this package.");
    }




    // Update the count in package_on_desk
    QSqlQuery updateCountQuery;
    updateCountQuery.prepare(R"(
    UPDATE package_on_desk
    SET count = count - 1
    WHERE id = :id
    AND count > 0
    )");
    updateCountQuery.bindValue(":id", packId);

    if (!updateCountQuery.exec()) {
        QMessageBox::critical(this, "Update Error", updateCountQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }



    // Read values from ui->specs_pack table
    int inbody = ui->specs_pack->item(0, 0)->text().toInt();
    int pt = ui->specs_pack->item(0, 1)->text().toInt();
    int inv = ui->specs_pack->item(0, 2)->text().toInt();
    int freeze = ui->freezebox->value()>=1?ui->freezebox->value(): ui->specs_pack->item(0, 3)->text().toInt();
    int spa = ui->specs_pack->item(0, 4)->text().toInt();

    //count+1
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
    UPDATE package_on_desk
    SET count = count + 1
    WHERE id = (
        SELECT pack_id
        FROM paackage
        WHERE id = :package_id
    )
    AND count != -1
)");
    updateQuery.bindValue(":package_id", package_id);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Update Error", "Failed to update count: " + updateQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }
    //count +1

    QString discount = ui->pack_dis->text();
    QString amountText = ui->pack_net->text().isEmpty() ? ui->pack_value->text() : ui->pack_net->text();

    // Attempt to convert the amountText to a float and then to an integer
    float amountFloat = amountText.toFloat();
    int newAmount = qRound(amountFloat);

    QDate startDate = ui->pack_start->date();
    QDate endDate = ui->pack_end->date();

    // Debugging output
    qDebug() << "Updating package with ID:" << package_id;
    qDebug() << "Values - inbody:" << inbody << ", spa:" << spa << ", inv:" << inv << ", freezze:" << freeze << ", pt:" << pt;
    qDebug() << "Start Date:" << startDate << ", End Date:" << endDate;
    qDebug() << "Discount:" << discount << ", Today Date:" << QDate::currentDate();
    qDebug() << "Pack ID:" << packId;

    QSqlQuery packageQuery;
    packageQuery.prepare("UPDATE paackage SET inbody = :inbody, spa = :spa, inv = :inv, freezze = :freezze, pt = :pt, start_date = :start_date, end_date = :end_date, discount = :discount, today_date = :today_date, pack_id = :pack_id, net = :net WHERE id = :id");
    packageQuery.bindValue(":inbody", inbody);
    packageQuery.bindValue(":spa", spa);
    packageQuery.bindValue(":inv", inv);
    packageQuery.bindValue(":freezze", freeze);
    packageQuery.bindValue(":pt", pt);
    packageQuery.bindValue(":start_date", startDate);
    packageQuery.bindValue(":end_date", endDate);
    packageQuery.bindValue(":discount", discount);
    packageQuery.bindValue(":today_date", QDate::currentDate()); // Set to current date
    packageQuery.bindValue(":pack_id", packId);
    packageQuery.bindValue(":net", newAmount); // Set the new amount for the net column
    packageQuery.bindValue(":id", package_id); // Use the stored package_id

    if (!packageQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update package: " + packageQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    } else {
        QMessageBox::information(this, "Success", "Package updated successfully.");
    }

    // Retrieve the current amount from the payment table
    int currentAmount = 0;
    QSqlQuery getCurrentAmountQuery;
    getCurrentAmountQuery.prepare("SELECT amount FROM payment WHERE pack_id = :pack_id AND pt_id IS NULL");
    getCurrentAmountQuery.bindValue(":pack_id", package_id);

    if (getCurrentAmountQuery.exec()) {
        while (getCurrentAmountQuery.next()) {
            QVariant amountVariant = getCurrentAmountQuery.value(0);
            currentAmount += amountVariant.toInt();
        }

        if (currentAmount == 0) {
            QMessageBox::information(this, "Info", "No valid payments found or amounts are NULL.");
            ui->pack_edit->setEnabled(true);
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Failed to retrieve payment amounts: " + getCurrentAmountQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }
    // Calculate the difference

    QTableWidgetItem *itemCol8 = ui->all->item(all_row, 8);
    int valueCol8 = 0;
    bool ok2 = false;

    if (itemCol8) {
        valueCol8 = itemCol8->text().toInt(&ok2);

        qDebug() << "Value Col 8:" << valueCol8 << "OK2:" << ok2;



        if (!ok2) {
            qDebug() << "Failed to convert value in column 8 to int.";
        }

        if (ok2) {
            // Calculate the difference
            int amountDifference = newAmount - valueCol8;
            qDebug() << "Amount Difference:" << amountDifference << "New Amount:" << newAmount << "Value Col 8:" << valueCol8;

            // Show the difference in a QMessageBox
            QString differenceMessage;
            if (amountDifference > 0) {
                differenceMessage = QString("The new amount is %1 more than the current amount.خد منه").arg(amountDifference);
            } else if (amountDifference < 0) {
                differenceMessage = QString("The new amount is %1 less than the current amount.رجعله").arg(-amountDifference);
            } else {
                differenceMessage = "The new amount is the same as the current amount.";
            }

            QMessageBox::information(this, "Amount Difference", differenceMessage);
        }
    } else {
        qDebug() << "Failed to retrieve items from columns 7 and 8.";
    }
    // Update the amount in the payment table
    QSqlQuery paymentQuery;
    paymentQuery.prepare("SELECT TOP 1 id FROM payment WHERE pack_id = :pack_id AND pt_id IS NULL ORDER BY id ASC");
    paymentQuery.bindValue(":pack_id", package_id);

    if (!paymentQuery.exec() || !paymentQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve the record with the smallest ID: " + paymentQuery.lastError().text());
        QSqlDatabase::database().rollback();
        ui->pack_edit->setEnabled(true);
        return;
    }

    // Retrieve the smallest ID
    int smallestId = paymentQuery.value(0).toInt();

    // Update the record with the smallest ID
    QSqlQuery updatepay;
    updatepay.prepare("UPDATE payment SET amount = :amount WHERE id = :id");
    updatepay.bindValue(":amount", newAmount);
    updatepay.bindValue(":id", smallestId);

    if (!updatepay.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update the record: " + updatepay.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }

    // Delete all records with the same pack_id but with higher IDs
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM payment WHERE pack_id = :pack_id AND id > :id");
    deleteQuery.bindValue(":pack_id", package_id);
    deleteQuery.bindValue(":id", smallestId);

    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete other records: " + deleteQuery.lastError().text());
        ui->pack_edit->setEnabled(true);
        return;
    }
    ui->show->click();
    ui->pack_start->setDate(QDate::currentDate());
    package_id=-1;

    QTimer::singleShot(100, this, [this]() { ui->pack_edit->setEnabled(true); });
}


void Member::pack_delete() {
    ui->pack_delete->setDisabled(true);
    if (package_id == -1) {
        QMessageBox::critical(this, "Error", "No package selected to delete, Double click row to be selected.");
        QTimer::singleShot(30, this, [this]() { ui->pack_delete->setEnabled(true); });
        return;
    }

    // Confirm deletion with user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this package?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        return;
    }
    QSqlQuery checkPtQuery;
    checkPtQuery.prepare("SELECT COUNT(*) FROM pt WHERE package_id = :package_id");
    checkPtQuery.bindValue(":package_id", package_id);

    if (!checkPtQuery.exec()) {
        QMessageBox::critical(this, "Query Error", "Failed to check related pt records: " + checkPtQuery.lastError().text());
        return;
    }

    if (checkPtQuery.next()) {
        int ptCount = checkPtQuery.value(0).toInt();
        if (ptCount > 0) {
            QMessageBox::warning(this, "Delete Error", " امسح كل البى تى العندها نفس رقم الباكديج الاول");
            ui->pack_delete->setEnabled(true);
            return; // Exit function if related pt records exist
        }
    }

    //count+1
    QSqlQuery updateQuery;
    updateQuery.prepare(R"(
        UPDATE package_on_desk
        SET count = count + 1
        WHERE id = (
            SELECT pack_id
            FROM paackage
            WHERE id = :package_id
        )
        AND count != -1
        )");
    updateQuery.bindValue(":package_id", package_id);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Update Error", "Failed to update count: " + updateQuery.lastError().text());
        ui->pack_delete->setEnabled(true);
        return;
    }

    // Delete the package from the database
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM paackage WHERE id = :id");
    deleteQuery.bindValue(":id", package_id);

    if (!deleteQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to delete package: " + deleteQuery.lastError().text());
        ui->pack_delete->setEnabled(true);
        return;
    } else {
        QMessageBox::information(this, "Success", "Package deleted successfully.");
        ui->show->click();
    }

    // Reset package_id
    ui->pack_start->setDate(QDate::currentDate());
    package_id = -1;
    QTimer::singleShot(50, this, [this]() { ui->pack_delete->setEnabled(true); });

}


void Member::updateEndDate(const QDate &startDate ) {
    // Assuming ui->pack_end is also a QDateEdit widget
    // Calculate end date as per your application logic, e.g., adding a month
    QDate endDate = startDate.addDays(duration_package+ui->adder->value()); // Example: end date is one month after start date

    ui->pack_end->setDate(endDate); // Set the calculated end date in ui->pack_end
}

void Member::clearRow(QTableWidget *tableWidget, int row)
{
    int columnCount = tableWidget->columnCount();

    // Iterate through each column in the specified row
    for (int col = 0; col < columnCount; ++col) {
        QTableWidgetItem *item = tableWidget->item(row, col); // Get the item in the specified row and column

        if (item) {
            item->setText(""); // Set the text of the item to an empty string
        } else {
            tableWidget->setItem(row, col, new QTableWidgetItem("")); // Create new item if it doesn't exist
        }
    }
}
void Member::change_in_shift(int shift){
    ui->pack_start->setDate(QDate::currentDate().addDays(shift));
}
void Member::onCellClicked(int row, int column)
{
    // Ensure only 2nd row is processed
    if (row != 1)
        return;
    if(column==2){
        QMessageBox::critical(this, "Error", "اعملها من تاب عشان نسجل الداتا بتاعتهم");
        return;
    }
    QTableWidgetItem *item = ui->specs_pack->item(row, column);
    if (!item || item->text().isEmpty() || item->text() == "0")
        return;

    bool ok;
    int currentValue = item->text().toInt(&ok);
    if (!ok)
        return; // Conversion to int failed

    // Get the customer ID from ui->id->value
    qint64 customer_id = ui->id->value();

    // Query to get the package_id for the given customer_id
    QSqlQuery packageQuery;
    packageQuery.prepare("SELECT id "
                         "FROM paackage "
                         "WHERE customer_id = :customer_id "
                         "AND GETDATE() >= start_date "
                         "AND GETDATE() <= end_date "
                         "ORDER BY end_date DESC");


    packageQuery.bindValue(":customer_id", customer_id);

    if (!packageQuery.exec() || !packageQuery.next()) {
        qDebug() << "Error querying package id:" << packageQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to retrieve package ID. Please try again.");
        return;
    }

    qint64 package_id = packageQuery.value(0).toLongLong();

    int maxSubtract = currentValue; // Limit the input to be subtracted to the current value

    // For inv and spa columns, ask for confirmation
    if (column != 2 && column != 4) { // Assuming 2 is inv and 4 is spa
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirm Update", QString("Do you want to decrement the value of %1 by 1?").arg(item->text()),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return;
        }

        currentValue -= 1; // Decrement the value
    } else {
        int maxSubtract = currentValue; // Limit the input to be subtracted to the current value
        int newValue = QInputDialog::getInt(this, "Enter New Value", "Enter the new value:", currentValue,
                                            0, maxSubtract, 1);
        if (newValue == currentValue) {
            return;
        }

        currentValue = newValue;
    }
    qDebug() << "New Value=" << currentValue;
    if (column == 0) {
        QSqlQuery insertQuery;
        insertQuery.prepare("INSERT INTO inbody (id, time, pack_id) "
                            "VALUES (COALESCE((SELECT MAX(id) + 1 FROM inbody), 0), :time, :pack_id)");
        insertQuery.bindValue(":time", QDateTime::currentDateTime()); // Use current date time directly
        insertQuery.bindValue(":pack_id", package_id);

        if (!insertQuery.exec()) {
            QMessageBox::critical(this, "Insert Error", insertQuery.lastError().text());
            qDebug() << "Insertion failed:" << insertQuery.lastError().text();
            return;
        } else {
            qDebug() << "Insertion successful";
        }
    }

    // Update the value in the database
    QSqlQuery updateQuery;
    QString columnName;
    switch (column) {
    case 0: columnName = "inbody"; break;
    case 1: columnName = "pt"; break;
    case 2: columnName = "inv"; break;
    case 3: columnName = "freezze"; break;
    case 4: columnName = "spa"; break;
    default: return; // Invalid column, return early
    }

    updateQuery.prepare(QString("UPDATE paackage SET %1 = :value WHERE id = :id").arg(columnName));
    updateQuery.bindValue(":value", currentValue);
    updateQuery.bindValue(":id", package_id);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Update Error", updateQuery.lastError().text());
    }
    else {
        item->setText(QString::number(currentValue));
    }
    qDebug() << "Insert Bindings - time: pack_id:ssdsd****" ;
}



void Member::onalldoubleclicked(int row, int column) {
    int id = ui->all->item(row, 0)->text().toInt();
    QString package_name = ui->all->item(row, 2)->text();
    QString discount = ui->all->item(row, 4)->text();
    QString start_date = ui->all->item(row, 5)->text();
    QString end_date = ui->all->item(row, 6)->text();
    package_id=id;
    all_row=row;

    QSqlQuery query;
    query.prepare("SELECT id, freezze "
                  "FROM paackage "
                  "WHERE id = :id");
    query.bindValue(":id", id);


    if (query.exec()) {
        if (query.next()) {
            int package_id = query.value("id").toInt();
            int freezze = query.value("freezze").toInt();

            ui->freezebox->setValue(freezze);
            ui->pack_combo->setCurrentText(package_name);
            ui->pack_dis->setText(discount);
            ui->pack_start->setDate(QDate::fromString(start_date, "yyyy-MM-dd"));
            ui->pack_end->setDate(QDate::fromString(end_date, "yyyy-MM-dd"));

            // Store the package_id for further use
            this->package_id = package_id;
        } else {
            QMessageBox::warning(this, "Error", "Package not found.");
        }
    } else {
        QMessageBox::critical(this, "Database Error", query.lastError().text());
    }
}

void Member::FreezeChangeDate(int days)
{
    if (blockSignalsFlag)
        return;

    qDebug() << "FreezeChangeDate called with days:" << days;

    blockSignalsFlag = true;
    QDate newDate =ui->freeze_start->date().addDays(days);
    ui->freeze->setDate(newDate);
    blockSignalsFlag = false;
}

void Member::freezezboxchange(QDate date)
{
    if (blockSignalsFlag)
        return;

    qDebug() << "freezezboxchange called with date:" << date;

    blockSignalsFlag = true;
    int daysDifference = ui->freeze_start->date().daysTo(date);
    ui->freeze_count->setValue(daysDifference);
    blockSignalsFlag = false;
}



void Member::save_freeze_slot() {
    ui->save_freeze->setDisabled(true);
    int customerId = ui->id->value(); // Assuming ui->id is a QSpinBox

    // 1. Query the database to fetch the package details for the customer ID
    QSqlQuery query;
    query.prepare("SELECT id, end_date, freezze, start_date FROM paackage WHERE customer_id = :customer_id ORDER BY end_date DESC");
    query.bindValue(":customer_id", customerId);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to fetch package details.");
        ui->save_freeze->setDisabled(false);
        return;
    }

    int packageId;
    QDate pack_start;
    QDate endDate;
    int freeze;
    if (query.next()) {
        packageId = query.value(0).toInt();
        endDate = query.value(1).toDate();
        freeze = query.value(2).toInt();
        pack_start=query.value(3).toDate();
    }
    else {
        qDebug() << "No package found for customer ID:" << customerId;
        QMessageBox::warning(this, "No Active Package", "No active package found for this customer.");
        ui->save_freeze->setDisabled(false);
        return;
    }

    // 2. Compare the package end date with the current date
    QDate currentDate = QDate::currentDate();
    if (endDate <= currentDate) {
        qDebug() << "Package end date is not greater than current date.";
        QMessageBox::warning(this, "Package Expired", "The package for this customer has expired.");
        ui->save_freeze->setDisabled(false);
        return;
    }

    // 3. Check if the freeze days requested exceed the current freeze days
    int requestedFreezeDays = ui->freeze_count->value(); // Calculate days inclusive
    if (freeze <requestedFreezeDays) {
        qDebug() << "Requested freeze days exceed the current freeze days.";
        qDebug()<< freeze;
        QMessageBox::warning(this, "Freeze Days Exceeded", "Error: More freeze days requested than available.");
        ui->save_freeze->setDisabled(false);
        return;
    }
    if(ui->freeze->date() <= ui->freeze_start->date()) {
        QMessageBox::warning(this, "Invalid Freeze Start Date",
                             "Caution: Freeze must start after the package itself starts.");
        ui->save_freeze->setDisabled(false);
        return;
    }
    if(ui->freeze_start->date() < pack_start){
        QMessageBox::warning(this, "Invalid Freeze Start Date",
                             "يوم الفريز  قبل بدايه الباكدج اصلا عدلتك الستارت ل تاريخ بدايه الباكديج.");
        ui->freeze_start->setDate(pack_start);
        ui->freeze->setDate(ui->freeze->date());
        ui->save_freeze->setDisabled(false);
        return;

    }

    // 4. Generate a new freeze schedule ID
    int freezeScheduleId=0;
    // Insert into freeze_schedule table
    QSqlQuery idmax;
    idmax.prepare("SELECT MAX(id) FROM freeze_schedule");// Function to generate new ID
    if (!idmax.exec()) {
        qDebug() << "Error executing query:" << idmax.lastError().text();
        QMessageBox::warning(this, "**", "++");
        ui->save_freeze->setDisabled(false);
        return ;
    }
    if (idmax.next()) {
        int maxId = idmax.value(0).isNull() ? 0 : idmax.value(0).toInt() + 1;
        qDebug() << "Max ID retrieved from freeze_schedule:" << maxId;
        freezeScheduleId= maxId;
    }
    else {
        qDebug() << "No results returned from query.";
        ui->save_freeze->setDisabled(false);
        return ;
    }

    // 5. Insert into freeze_schedule table
    query.prepare("INSERT INTO freeze_schedule (id, customer_id, package_id, start_date, end_date, note, count) "
                  "VALUES (:id, :customerId, :packageId, :startDate, :endDate, :note, :count)");

    query.bindValue(":id", freezeScheduleId);
    query.bindValue(":customerId", customerId);
    query.bindValue(":packageId", packageId);
    query.bindValue(":startDate", ui->freeze_start->date().toString(Qt::ISODate)); // Format date as ISO date string
    query.bindValue(":endDate", ui->freeze->date().toString(Qt::ISODate)); // Format date as ISO date string
    query.bindValue(":note", ui->reason->toPlainText());
    query.bindValue(":count", requestedFreezeDays); // Set initial value for count column

    QSqlQuery endDateQuery;
    endDateQuery.prepare("SELECT end_date FROM paackage WHERE id = :packageId ");
    endDateQuery.bindValue(":packageId", packageId);

    if (!endDateQuery.exec() || !endDateQuery.first()) {
        qDebug() << "Error retrieving end date from freeze_schedule:" << endDateQuery.lastError().text();
        ui->save_freeze->setDisabled(false);
        return;
    }

    QDate endDate_package = endDateQuery.value("end_date").toDate();

    // Calculate the new end date
    requestedFreezeDays = ui->freeze_count->value(); // Assuming this is how you retrieve the freeze count
    QDate newEndDate = endDate_package.addDays(requestedFreezeDays);

    // Update the package table with the new end date
    int newFreeze = freeze - requestedFreezeDays;
    QSqlQuery updatePackageQuery;
    updatePackageQuery.prepare("UPDATE paackage SET end_date = :newEndDate ,freezze = :newFreeze WHERE id = :packageId");
    updatePackageQuery.bindValue(":newEndDate", newEndDate);
    updatePackageQuery.bindValue(":packageId", packageId);
    updatePackageQuery.bindValue(":newFreeze",newFreeze);

    if (!updatePackageQuery.exec()) {
        qDebug() << "Error updating package table:" << updatePackageQuery.lastError().text();
        ui->save_freeze->setDisabled(false);
        return;
    }


    if (!query.exec()) {
        qDebug() << "Error inserting into freeze_schedule:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to insert into freeze_schedule.");
        ui->save_freeze->setDisabled(false);
        return;
    }

    qDebug() << "Successfully inserted into freeze_schedule with ID:" << freezeScheduleId;
    QMessageBox::information(this, "Insert Successful", "Successfully inserted into freeze_schedule.");
    ui->show->click();
    ui->save_freeze->setDisabled(false);


}

void Member::onFreezeTableDoubleClicked(int row, int column) {
    QTableWidgetItem *item = ui->freeze_table->item(row, column);
    if (item) {
        freezing_id=ui->freeze_table->item(row, 0)->text().toInt();
        ui->freeze_start->setDate(QDate::fromString(ui->freeze_table->item(row, 3)->text(), "yyyy-MM-dd")); // Example for start date in column 3
        ui->freeze->setDate(QDate::fromString(ui->freeze_table->item(row, 4)->text(), "yyyy-MM-dd")); // Example for end date in column 4
        ui->reason->setPlainText(ui->freeze_table->item(row, 6)->text()); // Example for note in column 5
        freeze_counts=ui->freeze_table->item(row, 5)->text().toInt();
        freeze_row=row;
        //QDate endDate = QDate::fromString(ui->freeze_table->item(row, 4)->text(), "yyyy-MM-dd");
        //freezezboxchange(endDate);
    }
}

void Member::edit_freeze() {
    ui->freeze_edit->setDisabled(true);
    if (freezing_id == -1) {
        QMessageBox::critical(this, "Error", "Please double-click on a row to edit in the table below.");
        ui->freeze_edit->setEnabled(true);
        return;
    }

    QDate startDate = ui->freeze_start->date();
    QDate endDate = ui->freeze->date();
    int freeze_count = ui->freeze_count->value();
    QString note=ui->reason->toPlainText();

    int pk_id= ui->freeze_table->item(freeze_row, 2)->text().toInt();

    // Fetch package details
    QSqlQuery query;
    query.prepare("SELECT end_date, freezze, start_date FROM paackage WHERE id = :pk_id ");
    query.bindValue(":pk_id", pk_id);

    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to fetch package details.");
        ui->freeze_edit->setEnabled(true);
        return;
    }

    QDate packageEndDate;
    QDate packageStartDate;
    int freeze;

    if (query.next()) {
        packageEndDate = query.value(0).toDate();
        freeze = query.value(1).toInt();
        packageStartDate=query.value(2).toDate();
    } else {
        qDebug() << "Failed to get package details.";
        ui->freeze_edit->setEnabled(true);
        return;
    }

    // Validate start date against package start date
    if (startDate < packageStartDate) {
        QMessageBox::warning(this, "Error", "Start date cannot be before the package start date.");
        ui->freeze_edit->setEnabled(true);
        return;
    }

    // Validate end date against package end date
    if (endDate > packageEndDate) {
        QMessageBox::warning(this, "Error", "End date cannot be after the package end date.");
        ui->freeze_edit->setEnabled(true);
        return;
    }

    // Check if freeze days requested exceed available freeze days
    if ((freeze + freeze_counts) < freeze_count) {
        QMessageBox::warning(this, "Error", "More freeze days requested than available.");
        ui->freeze_edit->setEnabled(true);
        return;
    }

    // Prepare the SQL update query for freeze_schedule table
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE freeze_schedule SET start_date = :startDate, end_date = :endDate ,count = :count,note = :note WHERE id = :freezingId");
    updateQuery.bindValue(":startDate", startDate.toString(Qt::ISODate));
    updateQuery.bindValue(":endDate", endDate.toString(Qt::ISODate));
    updateQuery.bindValue(":note", note);
    updateQuery.bindValue(":count", freeze_count);

    updateQuery.bindValue(":freezingId", freezing_id);

    // Execute the update query for freeze_schedule
    if (!updateQuery.exec()) {
        qDebug() << "Error updating freeze schedule:" << updateQuery.lastError().text();
        ui->freeze_edit->setEnabled(true);
        return;
    }

    qDebug() << "Freeze schedule updated successfully.";

    // Calculate new end_date and freeze count for package table
    QDate newPackageEndDate = packageEndDate.addDays(freeze_count -freeze_counts);
    int newFreeze=freeze+freeze_counts-freeze_count;

    // Prepare and execute update query for package table
    QSqlQuery updatePackageQuery;
    updatePackageQuery.prepare("UPDATE paackage SET end_date = :newEndDate, freezze = :newFreeze WHERE id = :pk_id");
    updatePackageQuery.bindValue(":newEndDate", newPackageEndDate.toString(Qt::ISODate));
    updatePackageQuery.bindValue(":newFreeze", newFreeze);
    updatePackageQuery.bindValue(":pk_id",pk_id);

    if (!updatePackageQuery.exec()) {
        qDebug() << "Error updating package details:" << updatePackageQuery.lastError().text();
        ui->freeze_edit->setEnabled(true);
        return;
    }

    qDebug() << "Package details updated successfully.";

    // Inform user of success
    QMessageBox::information(this, "Success", "Freeze and package details updated successfully.");
    ui->show->click();
    ui->freeze_edit->setEnabled(true);
}

void Member::delete_freeze() {
    // Check if freezing_id is valid
    ui->freez_delete->setDisabled(true);
    if (freezing_id == -1) {
        QMessageBox::critical(this, "Error", "Double click on a row in the table below to edit before deleting.");
        ui->freez_delete->setEnabled(true);
        return;
    }

    // Query to get the package_id, start_date, and end_date from freeze_schedule
    QSqlQuery query;
    query.prepare("SELECT package_id, start_date, end_date FROM freeze_schedule WHERE id = :freezingId");
    query.bindValue(":freezingId", freezing_id);

    if (!query.exec()) {
        qDebug() << "Error querying freeze schedule:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to query freeze schedule. Please try again.");
        return;
    }

    if (!query.next()) {
        qDebug() << "No matching freeze schedule found.";
        QMessageBox::critical(this, "Error", "No matching freeze schedule found.");
        ui->freez_delete->setEnabled(true);
        return;
    }

    // Retrieve package_id, start_date, and end_date
    qint64 package_id = query.value("package_id").toLongLong();
    QDate start_date = query.value("start_date").toDate();
    QDate end_date = query.value("end_date").toDate();

    // Calculate the duration to subtract
    int duration = start_date.daysTo(end_date);

    // Query to get the current end_date of the package
    QSqlQuery packageQuery;
    packageQuery.prepare("SELECT end_date ,freezze FROM paackage WHERE id = :packageId");
    packageQuery.bindValue(":packageId", package_id);

    if (!packageQuery.exec() || !packageQuery.next()) {
        qDebug() << "Error querying package end date:" << packageQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to query package end date. Please try again.");
        ui->freez_delete->setEnabled(true);
        return;
    }

    // Retrieve the current end_date of the package
    QDate package_end_date = packageQuery.value("end_date").toDate();
    int before_freeze=packageQuery.value("freezze").toInt();

    // Calculate the new end_date by subtracting the duration
    QDate new_end_date = package_end_date.addDays(-freeze_counts);

    // Update the end date of the package
    QSqlQuery updatePackageQuery;
    updatePackageQuery.prepare("UPDATE paackage SET end_date = :newEndDate, \"freezze\" = :freezeCounts WHERE id = :packageId");
    updatePackageQuery.bindValue(":newEndDate", new_end_date.toString(Qt::ISODate)); // Ensure date format is correct
    updatePackageQuery.bindValue(":freezeCounts", freeze_counts+before_freeze);
    updatePackageQuery.bindValue(":packageId", package_id);


    if (!updatePackageQuery.exec()) {
        qDebug() << "Error updating package end date:" << updatePackageQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to update package end date. Please try again.");
        ui->freez_delete->setEnabled(true);
        return;
    }

    // Delete the freeze schedule entry
    QSqlQuery deleteQuery;
    deleteQuery.prepare("DELETE FROM freeze_schedule WHERE id = :freezingId");
    deleteQuery.bindValue(":freezingId", freezing_id);

    if (!deleteQuery.exec()) {
        qDebug() << "Error deleting freeze schedule:" << deleteQuery.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete freeze schedule. Please try again.");
        ui->freez_delete->setEnabled(true);
        return;
    }

    qDebug() << "Freeze schedule deleted successfully and package end date updated.";

    QMessageBox::information(this,"delete success","done");


    // Optionally reset freezing_id or perform any cleanup tasks
    ui->show->click();
    freezing_id = -1; // Reset freezing_id after successful deletion, if needed
    ui->freez_delete->setEnabled(true);

}

//pt

void Member::updatePtValue(const QString &itemName){
    QSqlQuery query;
    query.prepare("SELECT value FROM pt_ondesk WHERE name = :itemName");
    query.bindValue(":itemName", itemName);

    if (!query.exec() || !query.next()) {
        qDebug() << "Query execution error or no results: " << query.lastError().text();
        return;
    }

    int ptValue = query.value("value").toInt();
    ui->pt_value->setText(QString::number(ptValue));
    updatePtNet(ui->pt_discount->text());
}

void Member::updatePtNet(const QString &discountText){

    QString discountStr = discountText.trimmed();

    if (discountStr.isEmpty()) {
        ui->pt_net->clear();
        return;
    }

    bool isPercentage = discountStr.endsWith('%');
    QString discountValueStr = discountStr;
    if (isPercentage) {
        discountValueStr.chop(1);
    }

    bool conversionOK = false;
    double discountValue = discountValueStr.toDouble(&conversionOK);
    if (!conversionOK) {
        qDebug() << "Invalid discount format";
        return;
    }

    double initialValue = ui->pt_value->text().toDouble();
    double netValue;
    if(isPercentage && discountValue>99){
        isPercentage=false;
    }
    if(!isPercentage && discountValue>=initialValue){
        QMessageBox::critical(this,"too much discount","discount is more than tha pack value");
        return;
    }

    if (isPercentage) {
        // Discount is percentage
        netValue = initialValue * (1.0 - discountValue / 100.0);
    } else {
        // Direct discount value
        netValue = initialValue - discountValue;
    }

    // Check if net value is less than or equal to package limit (e.g., 0 or some minimum)
    double packageLimit = 0.0; // Adjust as per your requirement
    if (netValue < packageLimit) {
        // Handle case where net value is less than package limit
        qDebug() << "Net value is less than package limit";
        netValue = packageLimit; // Or set to some default value
    }
    int roundedNetValue = qRound(netValue);


    // Update ui->pt_net with the calculated net value
    ui->pt_net->setText(QString::number(roundedNetValue));
}

void Member::save_pt() {
    ui->save_pt->setDisabled(true);
    QString pack_name = ui->pt_pack->currentText();
    QString value = (ui->pt_net->text().isEmpty()) ? ui->pt_value->text() : ui->pt_net->text();
    QDate date = QDate::currentDate();
    QString dis = ui->pt_discount->text();
    QString type = ui->pt_type->currentText();

    // Retrieve captain ID
    QSqlQuery captain;
    captain.prepare("SELECT id FROM cap WHERE name = :name");
    captain.bindValue(":name", ui->pt_cap->currentText());

    if (!captain.exec() || !captain.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve captain ID or no results found.");
        ui->save_pt->setEnabled(true);
        return;
    }
    int cap_id = captain.value(0).toInt();

    // Retrieve pt_ondesk_id based on pack_name
    QSqlQuery ptOndeskQuery;
    ptOndeskQuery.prepare("SELECT id ,num_sessions FROM pt_ondesk WHERE name = :pack_name");
    ptOndeskQuery.bindValue(":pack_name", pack_name);

    if (!ptOndeskQuery.exec() || !ptOndeskQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve pt_ondesk ID for the selected pack_name.");
        ui->save_pt->setEnabled(true);
        return;
    }
    int pt_ondesk_id = ptOndeskQuery.value(0).toInt();
    int pt_ondesk = ptOndeskQuery.value(1).toInt();


    // Retrieve active package ID for the customer
    int customer_id = ui->id->value(); // Assuming ui->id is a spin box or similar
    QSqlQuery packageQuery;
    packageQuery.prepare("SELECT id, pt FROM paackage "
                         "WHERE customer_id = :customer_id "
                         "AND end_date >= GETDATE() "
                         "ORDER BY end_date DESC");
    packageQuery.bindValue(":customer_id", customer_id);

    if (!packageQuery.exec() || !packageQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve active package ID or no active package found.");
        ui->save_pt->setEnabled(true);
        return;
    }
    int package_id = packageQuery.value("id").toInt();
    int pt = packageQuery.value("pt").toInt();

    int new_pt = pt + pt_ondesk;

    // Update the package table with the new pt value
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE paackage SET pt = :new_pt WHERE id = :package_id");
    updateQuery.bindValue(":new_pt", new_pt);
    updateQuery.bindValue(":package_id", package_id);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update package: " + updateQuery.lastError().text());
    } else {
        QMessageBox::information(this, "Success", "Package updated successfully with new pt value.");
    }

    // Retrieve max id from pt table
    QSqlQuery maxIdQuery;
    QString queryString = "SELECT COALESCE(MAX(id), 0) AS max_id FROM pt";
    maxIdQuery.prepare(queryString);

    // Execute the SQL query and check for errors
    if (!maxIdQuery.exec()) {
        // Log any errors that occur during query execution
        qDebug() << "Error executing maxIdQuery:" << maxIdQuery.lastError().text();
        qDebug() << "Query string: " << queryString;
        ui->save_pt->setEnabled(true);
        return;
    }
    int maxId = 0;

    // Check if the query returned any results
    if (maxIdQuery.next()) {
        // Retrieve the maximum ID from the query result
        maxId = maxIdQuery.value("max_id").toInt();
    } else {
        // Log a message if the query did not return any results
        qDebug() << "Error: maxIdQuery did not return any results.";
        qDebug() << "Query string: " << queryString;
        ui->save_pt->setEnabled(true);
        return;
    }

    // Insert into pt table
    QSqlQuery insertPtQuery;
    int newId=maxId+1;
    insertPtQuery.prepare("INSERT INTO pt (id, pt_ondesk_id, package_id, discount, date, net, cap_id, num_sessions) "
                          "VALUES (:id, :pt_ondesk_id, :package_id, :discount, :date, :net, :cap_id, :num_sessions)");
    insertPtQuery.bindValue(":id", newId);
    insertPtQuery.bindValue(":pt_ondesk_id", pt_ondesk_id);
    insertPtQuery.bindValue(":num_sessions", pt_ondesk);
    insertPtQuery.bindValue(":package_id", package_id);
    insertPtQuery.bindValue(":discount", dis);
    insertPtQuery.bindValue(":date", date);
    insertPtQuery.bindValue(":net", value.toInt());
    insertPtQuery.bindValue(":cap_id", cap_id);

    if (!insertPtQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert into pt table: " + insertPtQuery.lastError().text());
        ui->save_pt->setEnabled(true);
        return;
    }

    // Retrieve max id from payment table
    // Query to get the maximum id from the payment table
    QString maxPaymentIdQueryString = "SELECT COALESCE(MAX(id), 0) AS max_id FROM payment";
    QSqlQuery maxPaymentIdQuery;
    maxPaymentIdQuery.prepare(maxPaymentIdQueryString);

    int maxPaymentId = 0;
    if (maxPaymentIdQuery.exec()) {
        if (maxPaymentIdQuery.next()) {
            maxPaymentId = maxPaymentIdQuery.value("max_id").toInt();
        } else {
            qDebug() << "Error: maxPaymentIdQuery did not return any results.";
        }
    } else {
        qDebug() << "Error executing maxPaymentIdQuery:" << maxPaymentIdQuery.lastError().text();
    }

    int newPaymentId = maxPaymentId + 1;

    QString insertPaymentQueryString = "INSERT INTO payment (id, type, date_pay, customer_id, amount, note, pack_id, pt_id) "
                                       "VALUES (:id, :type, :date, :customer_id, :amount, :note, :pack_id, :pt_id)";
    QSqlQuery insertPaymentQuery;
    insertPaymentQuery.prepare(insertPaymentQueryString);
    insertPaymentQuery.bindValue(":id", newPaymentId);
    insertPaymentQuery.bindValue(":type", type);
    insertPaymentQuery.bindValue(":date", date);
    insertPaymentQuery.bindValue(":customer_id", customer_id);
    insertPaymentQuery.bindValue(":amount", value.toInt());
    insertPaymentQuery.bindValue(":note", "private session");  // Note value as QString
    insertPaymentQuery.bindValue(":pack_id", package_id);
    insertPaymentQuery.bindValue(":pt_id", newId);

    if (!insertPaymentQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to insert into payment table: " + insertPaymentQuery.lastError().text());
        ui->save_pt->setEnabled(true);
        return;
    }
    pt_id=-1;
    QMessageBox::information(this, "Success", "Inserted into pt and payment tables successfully.");
    ui->show->click();
    ui->save_pt->setEnabled(true);


    // Optionally, clear fields or update UI after successful insertion

}


void Member::pt_table_select(QTableWidgetItem *item) {
    if (!item) {
        return;
    }


    int row = item->row();
    pt_id= ui->pt_table->item(row, 5)->text().toInt();
    QString pack_name = ui->pt_table->item(row, 1)->text(); // Package Name
    QString value = ui->pt_table->item(row, 2)->text(); // Value
    QString discount = ui->pt_table->item(row, 3)->text(); // Discount
    QString captain = ui->pt_table->item(row, 6)->text(); // Captain Name    pt_row=row;
    pt_row=row;

    // Populate your UI components with the retrieved data
    ui->pt_pack->setCurrentText(pack_name); // Assuming ui->pt_pack is a QComboBox
    ui->pt_net->setText(value); // Assuming ui->pt_net is a QLineEdit or similar
    ui->pt_discount->setText(discount);
    ui->pt_cap->setCurrentText(captain); // Assuming ui->pt_cap is a QComboBox

    // Query to retrieve types from payment table based on pt_id, limiting to one result
    QSqlQuery query;
    query.prepare("SELECT type FROM payment WHERE pt_id = :pt_id LIMIT 1");
    query.bindValue(":pt_id", pt_id);

    if (!query.exec()) {
        qDebug() << "Failed to execute query:" << query.lastError().text();
        return;
    }


    if (query.next()) {
        QString type = query.value("type").toString();
        ui->pt_type->setCurrentText(type);
    }
}

void Member::pt_edit() {
    ui->pt_edit->setDisabled(true);
    if (pt_id == -1) {
        QMessageBox::critical(this, "Error", "Double click on a row in the table below to edit before editing.");
        ui->pt_edit->setEnabled(true);

        return;
    }

    // Retrieve updated values from UI components
    QString pack_name = ui->pt_pack->currentText();
    QString value = ui->pt_net->text().isEmpty() ? ui->pt_value->text() : ui->pt_net->text();
    QString discount = ui->pt_discount->text();
    QString type = ui->pt_type->currentText();
    QString captain = ui->pt_cap->currentText(); // Assuming ui->pt_cap is a QComboBox or similar

    // Query to get pt_ondesk_id based on pack_name
    QSqlQuery ptOndeskQuery;
    ptOndeskQuery.prepare("SELECT id, num_sessions FROM pt_ondesk WHERE name = :name");
    ptOndeskQuery.bindValue(":name", pack_name);

    if (!ptOndeskQuery.exec() || !ptOndeskQuery.next()) {
        qDebug() << "Failed to retrieve pt_ondesk_id:" << ptOndeskQuery.lastError().text();
        ui->pt_edit->setEnabled(true);
        return;
    }
    QSqlQuery beforePtQuery;
    beforePtQuery.prepare("SELECT pod.num_sessions "
                          "FROM pt p "
                          "JOIN pt_ondesk pod ON p.pt_ondesk_id = pod.id "
                          "WHERE p.id = :pt_id");
    beforePtQuery.bindValue(":pt_id", pt_id); // Assuming pt_id is the id from your pt table

    if (!beforePtQuery.exec() || !beforePtQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve num_sessions from pt_ondesk: " + beforePtQuery.lastError().text());
        ui->pt_edit->setEnabled(true);
        return;
    }

    int num_sessions = beforePtQuery.value(0).toInt();

    int pt_ondesk_id = ptOndeskQuery.value("id").toInt();
    int new_pt=ptOndeskQuery.value("num_sessions").toInt();

    int old_pt = ui->pt_table->item(pt_row, 7)->text().toInt();
    int used=num_sessions-old_pt;
    int customer_id = ui->id->value(); // Assuming ui->id is a spin box or similar

    QSqlQuery selectPackageIdQuery;
    selectPackageIdQuery.prepare("SELECT id, pt "
                                 "FROM paackage "
                                 "WHERE customer_id = :customer_id "
                                 "AND GETDATE() >= start_date "
                                 "AND GETDATE() <= end_date "
                                 "ORDER BY end_date DESC");
    selectPackageIdQuery.bindValue(":customer_id", customer_id);

    if (!selectPackageIdQuery.exec() || !selectPackageIdQuery.next()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve package_id: " + selectPackageIdQuery.lastError().text());
        ui->pt_edit->setEnabled(true);
        return;
    }
    int package_pt=selectPackageIdQuery.value(1).toInt();

    int package_id = selectPackageIdQuery.value(0).toInt();

    QSqlQuery updatePackQuery;
    updatePackQuery.prepare("UPDATE paackage "
                          "SET pt = :new_pt "
                          "WHERE id = :package_id");
    updatePackQuery.bindValue(":new_pt", package_pt-old_pt+new_pt-used);
    updatePackQuery.bindValue(":package_id", package_id);

    if (!updatePackQuery.exec()) {
        QMessageBox::critical(this, "Error", "Failed to update pt in package table: " + updatePackQuery.lastError().text());
        ui->pt_edit->setEnabled(true);
        return;
    }

    // Query to get cap_id based on captain name
    QSqlQuery capQuery;
    capQuery.prepare("SELECT id FROM cap WHERE name = :name");
    capQuery.bindValue(":name", captain);

    if (!capQuery.exec() || !capQuery.next()) {
        qDebug() << "Failed to retrieve cap_id:" << capQuery.lastError().text();
        ui->pt_edit->setEnabled(true);
        return;
    }

    int cap_id = capQuery.value("id").toInt();

    // Update pt table based on pt_id (excluding package_id)
    QSqlQuery updatePtQuery;
    updatePtQuery.prepare("UPDATE pt SET pt_ondesk_id = :pt_ondesk_id, discount = :discount, net = :net, cap_id = :cap_id, num_sessions = :new_val WHERE id = :pt_id");
    updatePtQuery.bindValue(":pt_ondesk_id", pt_ondesk_id);
    updatePtQuery.bindValue(":discount", discount);
    updatePtQuery.bindValue(":net", value);
    updatePtQuery.bindValue(":cap_id", cap_id); // Set cap_id obtained from cap table
    updatePtQuery.bindValue(":pt_id", pt_id);
    updatePtQuery.bindValue(":new_val", new_pt-used );


    if (!updatePtQuery.exec()) {
        qDebug() << "Failed to update pt table:" << updatePtQuery.lastError().text();
        ui->pt_edit->setEnabled(true);
        return;
    }

    // Update payment table based on pt_id
    QSqlQuery updatePaymentQuery;
    updatePaymentQuery.prepare("UPDATE payment SET type = :type, amount = :amount WHERE pt_id = :pt_id");
    updatePaymentQuery.bindValue(":type", type);
    updatePaymentQuery.bindValue(":amount", value.toInt()); // Assuming value is QString containing the amount
    updatePaymentQuery.bindValue(":pt_id", pt_id);
    if (!updatePaymentQuery.exec()) {
        qDebug() << "Failed to update payment table:" << updatePaymentQuery.lastError().text();
        ui->pt_edit->setEnabled(true);
        return;
    }

    QMessageBox::information(this, "Success", "Updated pt and payment entries successfully.");
    // Optionally, clear fields or update UI after successful update
    pt_id=-1;
    ui->pt_net->clear();
    ui->pt_discount->clear();
    ui->show->click();
    ui->pt_edit->setEnabled(true);

}

void Member::pt_delete() {
    ui->pt_delete->setDisabled(true);
    if (pt_id == -1) {
        QMessageBox::critical(this, "Error", "Double click on a row in the table below to delete.");
        ui->pt_delete->setEnabled(true);
        return;
    }

    // Get the row number (1-indexed)
    // Assuming ui->pt_table is your QTableWidget

    // Confirmation message
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion",
                                  QString("Are you sure you want to delete row %1 with pt id = %2?")
                                      .arg(pt_row).arg(pt_id),
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        ui->pt_delete->setEnabled(true);

        return; // Abort deletion
    }

    int pack_id = ui->pt_table->item(pt_row, 4)->text().toInt(); // Assuming pack_id is in column 4 (0-indexed)

    // Retrieve value from column 7 to subtract from PT
    int value_to_subtract = ui->pt_table->item(pt_row, 7)->text().toInt(); // Assuming value to subtract is in column 7 (0-indexed)

    // Update package table to subtract PT value
    QSqlQuery updatePackageQuery;
    updatePackageQuery.prepare("UPDATE paackage SET pt = pt - :value_to_subtract WHERE id = :pack_id");
    updatePackageQuery.bindValue(":value_to_subtract", value_to_subtract);
    updatePackageQuery.bindValue(":pack_id", pack_id);

    if (!updatePackageQuery.exec()) {
        qDebug() << "Failed to update package PT:" << updatePackageQuery.lastError().text();
        ui->pt_delete->setEnabled(true);

        return;
    }

    // Delete from pt table
    QSqlQuery deletePtQuery;
    deletePtQuery.prepare("DELETE FROM pt WHERE id = :pt_id");
    deletePtQuery.bindValue(":pt_id", pt_id);

    if (!deletePtQuery.exec()) {
        qDebug() << "Failed to delete from pt table:" << deletePtQuery.lastError().text();
        ui->pt_delete->setEnabled(true);

        return;
    }

    // Delete from payment table
    QSqlQuery deletePaymentQuery;
    deletePaymentQuery.prepare("DELETE FROM payment WHERE pt_id = :pt_id");
    deletePaymentQuery.bindValue(":pt_id", pt_id);

    if (!deletePaymentQuery.exec()) {
        qDebug() << "Failed to delete related payments:" << deletePaymentQuery.lastError().text();
        ui->pt_delete->setEnabled(true);

        return;
    }

    QMessageBox::information(this, "Success", "Deleted pt and related payments successfully.");
    pt_id = -1;
    ui->show->click();
    ui->pt_delete->setEnabled(true);


    // Set pt_id to -1 to indicate no selected row

}

void Member::onPtTableDoubleClicked(const QModelIndex &index) {
    if (index.column() == 7) { // Assuming column 8 (0-based index)
        int pt_id = ui->pt_table->item(index.row(), 5)->text().toInt(); // Assuming id is in column 6 (0-based index)
        int customer_id = ui->id->value(); // Assuming ui->id is a spin box or similar

        // Ask for confirmation
        QMessageBox::StandardButton confirmation;
        confirmation = QMessageBox::question(this, "Confirmation", "Are you sure you want to update PT and Package?",
                                             QMessageBox::Yes | QMessageBox::No);

        if (confirmation != QMessageBox::Yes) {
            return; // User clicked No or Cancel
        }

        // Query to decrease num_sessions related to pt_id in pt table
        QSqlQuery decreasePtQuery;
        decreasePtQuery.prepare("UPDATE pt SET num_sessions = num_sessions - 1 WHERE id = :pt_id");
        decreasePtQuery.bindValue(":pt_id", pt_id);

        if (!decreasePtQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update pt: " + decreasePtQuery.lastError().text());
            return;
        }

        // Query to retrieve the active package_id associated with customer_id
        QSqlQuery selectPackageIdQuery;
        selectPackageIdQuery.prepare("SELECT id "
                                     "FROM paackage "
                                     "WHERE customer_id = :customer_id "
                                     "AND GETDATE() >= start_date "
                                     "AND GETDATE() <= end_date "
                                     "ORDER BY end_date DESC");
        selectPackageIdQuery.bindValue(":customer_id", customer_id);

        if (!selectPackageIdQuery.exec() || !selectPackageIdQuery.next()) {
            QMessageBox::critical(this, "Error", "Failed to retrieve package_id: " + selectPackageIdQuery.lastError().text());
            return;
        }

        int package_id = selectPackageIdQuery.value(0).toInt();

        // Query to decrease pt related to package_id in package table
        QSqlQuery decreasePackagePtQuery;
        decreasePackagePtQuery.prepare("UPDATE paackage SET pt = pt - 1 WHERE id = :package_id");
        decreasePackagePtQuery.bindValue(":package_id", package_id);

        if (!decreasePackagePtQuery.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update package pt: " + decreasePackagePtQuery.lastError().text());
            return;
        }

        // Show success message
        QMessageBox::information(this, "Success", "PT and Package updated successfully.");
        ui->show->click();
    }
}

void Member::save_inv(){
    ui->invsave->setDisabled(true);
    // Retrieve data from UI widgets
    QString name = ui->invname->text().trimmed();
    QString phone = ui->invphone->text().trimmed();

    // Check if name or phone is empty
    if (name.isEmpty() || phone.isEmpty()) {
        QMessageBox::warning(this, "Empty Fields", "Please enter both name and phone number.");
        ui->invsave->setEnabled(true);

        return;
    }

    // Check if the phone number already exists in the inv table
    QSqlQuery checkQuery(db); // Pass db as the database connection
    checkQuery.prepare("SELECT * FROM inv WHERE phone_number = :phone");
    checkQuery.bindValue(":phone", phone);

    if (!checkQuery.exec()) {
        qDebug() << "Query execution failed:" << checkQuery.lastError().text();
        ui->invsave->setEnabled(true);

        return;
    }

    // Debug output to check query execution and results
    qDebug() << "Executed query:" << checkQuery.lastQuery();

    int rowCount = 0;
    while (checkQuery.next()) {
        rowCount++;
    }


    if (rowCount > 0) {
        // Phone number already exists, show a QMessageBox with a table of matching records
        QSqlQueryModel *model = new QSqlQueryModel();
        model->setQuery(checkQuery);
        qDebug() << "Query:" << checkQuery.lastQuery();
        qDebug() << "Errors:" << checkQuery.lastError();
        QTableView *tableView = new QTableView();
        tableView->setModel(model);
        tableView->resizeColumnsToContents();
        tableView->setWindowTitle("Existing Records with Phone Number");
        tableView->resize(800, 600); // Set width and height as needed
        tableView->show();


          // Phone number already exists, show a QMessageBox with options
        QString message = "Phone number already exists in the database " + QString::number(rowCount)+ " times .\n"
                            "Do you want to continue adding new inv?";

          QMessageBox msgBox;
          msgBox.setText(message);
          msgBox.setWindowTitle("Duplicate Phone Number");
          msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
          msgBox.setDefaultButton(QMessageBox::No);

          int choice = msgBox.exec();
          if (choice == QMessageBox::No) {
              ui->invsave->setEnabled(true);

              return; // User chose not to continue
          }
          // If user chooses Yes, continue with insertion


    }

    QSqlQuery countQuery(db); // Assuming db is your database connection
    countQuery.prepare("SELECT inv FROM paackage WHERE id = :package_id");
    countQuery.bindValue(":package_id", pack_idd_for_inv);

    if (!countQuery.exec()) {
        qDebug() << "Failed to retrieve inv count:" << countQuery.lastError().text();
        ui->invsave->setEnabled(true);

        return;
    }

    int invCount = 0;
    if (countQuery.next()) {
        invCount = countQuery.value("inv").toInt();
    }

    if (invCount > 0) {
        // Decrease inv by one
        invCount--;

        // Update the package table with the decreased inv count
        QSqlQuery updateQuery(db);
        updateQuery.prepare("UPDATE paackage SET inv = :inv WHERE id = :package_id");
        updateQuery.bindValue(":inv", invCount);
        updateQuery.bindValue(":package_id", pack_idd_for_inv);

        if (!updateQuery.exec()) {
            qDebug() << "Failed to update inv count:" << updateQuery.lastError().text();
            ui->invsave->setEnabled(true);

            return;
        }

        qDebug() << "inv count decremented successfully for package_id:" << pack_idd_for_inv;
    } else {
        qDebug() << "No inv to decrement for package_id:" << pack_idd_for_inv;
        ui->invsave->setEnabled(true);

        return;
    }


    // Retrieve the next available id for insertion
    int next_id = 0;  // Initialize next_id with a default value
    QSqlQuery query_max_id(db); // Pass db as the database connection
    query_max_id.prepare("SELECT COALESCE(MAX(id), 0) + 1 AS next_id FROM inv");
    if (!query_max_id.exec()) {
        qDebug() << "Failed to retrieve next id from inv table:" << query_max_id.lastError().text();
        ui->invsave->setEnabled(true);

        return;
    }

    if (query_max_id.next()) {
        next_id = query_max_id.value("next_id").toInt();
    } else {
        qDebug() << "No next id found in query result";
        ui->invsave->setEnabled(true);

        return;
    }

    // Get current date/time
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Insert data into database table
    QSqlQuery query_insert(db); // Pass db as the database connection
    query_insert.prepare("INSERT INTO inv (id, name, phone_number, pack_id, time) VALUES (:id, :name, :phone, :pack_id, :time)");
    query_insert.bindValue(":id", next_id);
    query_insert.bindValue(":name", name);
    query_insert.bindValue(":phone", phone);
    query_insert.bindValue(":pack_id", pack_idd_for_inv); // Assuming pack_id is the same as id for simplicity
    query_insert.bindValue(":time", currentDateTime);

    if (query_insert.exec()) {
        qDebug() << "Record inserted successfully";
        // You can update your UI or perform other actions upon successful insertion
    } else {
        qDebug() << "Error inserting record:" << query_insert.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to insert record into database.");
        ui->invsave->setEnabled(true);

        return;
    }

    // Perform any additional actions after insertion
    ui->show->click();
    ui->invsave->setEnabled(true);


}

void Member::on_invtable_doubleClicked(int row, int column){
    // Retrieve the values from the double-clicked row
    inv_id = ui->invtable->item(row, 0)->text().toInt();
}

void Member::inv_delete(){
    ui->invdelete->setDisabled(true);
    if(inv_id==-1){
        QMessageBox::warning(this, "selection", " rowدابل كليك على ال");
        return;
    }
    // Confirm deletion with the user
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Confirmation", "Are you sure you want to delete this record?",
                                  QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::No) {
        ui->invdelete->setEnabled(true);

        return;
    }

    QSqlQuery query;
    query.prepare("DELETE FROM inv WHERE id = :id");
    query.bindValue(":id", inv_id);

    if (!query.exec()) {
        qDebug() << "Error executing delete query:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to delete the record.");
        ui->invdelete->setEnabled(true);

        return;
    }

    // Find the row in the table and remove it
    for (int i = 0; i < ui->invtable->rowCount(); ++i) {
        if (ui->invtable->item(i, 0)->text().toInt() == inv_id) {
            ui->invtable->removeRow(i);
            break;
        }
    }

    inv_id = -1; // Reset the inv_id after deletion
    QMessageBox::information(this, "Success", "Record deleted successfully.");
    ui->invdelete->setEnabled(true);


}
void Member::front_setter(){
    ui->pack_edit->setDisabled(true);
    ui->pack_delete->setDisabled(true);
    ui->delete_pay->setDisabled(true);
    ui->pt_delete->setDisabled(true);
    ui->pt_edit->setDisabled(true);
    ui->invdelete->setDisabled(true);
    ui->start_shift->setDisabled(true);
    ui->freezebox->setDisabled(true);
    ui->pack_start->setDisabled(true);
    ui->pack_dis->setDisabled(true);
    ui->pt_discount->setDisabled(true);
    ui->freez_delete->setDisabled(true);
    ui->freeze_edit->setDisabled(true);
    ui->adder->setDisabled(true);

}
void Member::update_packages(){
    disconnect(ui->pack_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(onPackComboBoxSelectionChanged(int)));
    ui->pack_combo->clear();

    QSqlQuery query;
    query.prepare(R"(
    SELECT name
    FROM package_on_desk
    WHERE active = 1
    ORDER BY start_date
)");
    if (!query.exec()) {
        QMessageBox::critical(this, "Query Error in package names", query.lastError().text());
        return;
    }

    while (query.next()) {
        QString packageName = query.value(0).toString();
        ui->pack_combo->addItem(packageName);
    }
    connect(ui->pack_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(onPackComboBoxSelectionChanged(int)));

}

void Member::emplyee_capturred(){
    QSqlQuery salesQuery;
    salesQuery.prepare("SELECT name FROM saales");

    if (!salesQuery.exec()) {
        qDebug() << "Failed to execute sales query:" << salesQuery.lastError().text();
        return;
    }

    ui->sales->clear();
    ui->pt_cap->clear();

    while(salesQuery.next()) {
        QString name = salesQuery.value(0).toString();
        ui->sales->addItem(name);
    }

    QSqlQuery query_cap;

    query_cap.prepare("SELECT name FROM cap");

    if (!query_cap.exec()) {
        qDebug() << "Error executing query_cap:" << query_cap.lastError().text();
        return;
    }

    while (query_cap.next()) {
        QString name = query_cap.value("name").toString();
        ui->pt_cap->addItem(name);
    }

}
void Member::add_on_end_date(){
    int shift=ui->adder->value();
    QSqlQuery query;
    query.prepare("SELECT duration FROM package_on_desk WHERE name = :packName");
    query.bindValue(":packName", ui->pack_combo->currentText().trimmed());  // Bind the package name from the UI
    int duration=0;
    if (!query.exec()) {
        qDebug() << "Query execution error: " << query.lastError();
    } else {
        if (query.next()) {
            duration = query.value("duration").toInt();
            qDebug() << "Package Duration:" << duration;
        } else {
            qDebug() << "No package found with the given name.";
        }
    }
    if(duration<=(-1*shift)){
        QMessageBox::critical(this,"as7aaaaaaaaaaaaaaa","انت بتحاول تشيل ايام اكتر من مده الباكديج اصلا");
        ui->adder->setValue(ui->adder->value()+1);
        return;
    }
    ui->pack_end->setDate(ui->pack_start->date().addDays(duration+shift));
}


