#include "safe.h"
#include "ui_safe.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDateEdit>
#include <QTextStream>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QLineEdit>  // Include QLineEdit header
#include <QFileInfo>
#include <QPageSize>
#include <QDesktopServices>




safe::safe(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::safe)
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
    setWindowTitle("الخزنة");

    ui->start->setDate(QDate::currentDate());
    ui->end->setDate(QDate::currentDate());

    connect(ui->print,&QPushButton::clicked,this,&safe::print);
    connect(ui->save,&QPushButton::clicked,this,&safe::saveQueryResults);
    QString globalStyleSheet =
        // QWidget and QLabel styles
        "QWidget { background-color: #040D12; color: #FFFFFF; }"
        "QWidget#widget_4 ,QWidget#widget_3, QWidget#widget_2 { background-color: #040D12; border: 2px solid #87CEEB;color: #FFFFFF; }"
        "QLabel { background-color: transparent; color: #FFFFFF; }"
        "QLineEdit, QDateEdit, QTextEdit, QSpinBox, QComboBox { background-color: #31363F; color: #FFFFFF; border: 2px solid #222831; }"
        "QLineEdit:focus, QDateEdit:focus, QTextEdit:focus, QSpinBox:focus, QComboBox:focus { border: 2px solid #FFA62F; background-color: #1F1B24; }"

        // QPushButton styles
        "QPushButton { border: 2px solid #FFA62F; background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #005C78, stop:1 #003C43); color: #FFFFFF; }"
        "QPushButton:hover { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #FF8C00, stop:1 #F05941); }"
        "QPushButton:pressed { background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #5D001E, stop:1 #8A3324); border: 2px solid #87431D; }";

    this->setStyleSheet(globalStyleSheet);

    dialog = new QFileDialog(this, "Save File");
    dialog->setFileMode(QFileDialog::AnyFile);
    dialog->setNameFilters(QStringList() << "CSV Files (*.csv)" << "PDF Files (*.pdf)");
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    // Connect filterSelected signal to updateFileNameExtension slot
    qDebug() << "Connecting filterSelected signal to updateFileNameExtension slot...";
    connect(dialog, &QFileDialog::filterSelected, this, &safe::updateFileNameExtension);
    qDebug() << "Connection established.";



}
void safe::print(){
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();
    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "Start date cannot be greater than end date.");
        return;
    }

    QSqlQuery query;
    QString queryString =
        "SELECT "
        "p.id AS payment_id, "
        "p.type AS payment_type, "
        "p.date_pay, "
        "p.customer_id, "
        "p.amount, "
        "p.note, "
        "p.pack_id, "
        "p.pt_id, "
        "c.name AS customer_name, "
        "pod.name AS package_name, "
        "pt_ondesk.name AS pt_name, "
        "cap.name AS cap_name "
        "FROM payment p "
        "LEFT JOIN customer c ON p.customer_id = c.id "
        "LEFT JOIN paackage pack ON p.pack_id = pack.id "
        "LEFT JOIN pt ON p.pt_id = pt.id "
        "LEFT JOIN pt_ondesk pt_ondesk ON pt.pt_ondesk_id = pt_ondesk.id "
        "LEFT JOIN cap ON pt.cap_id = cap.id "
        "LEFT JOIN package_on_desk pod ON pack.pack_id = pod.id "
        "WHERE p.date_pay BETWEEN :start_date AND :end_date "
        "ORDER BY p.date_pay DESC;";

    query.prepare(queryString);

    query.bindValue(":start_date", startDate.toString(Qt::ISODate));
    query.bindValue(":end_date", endDate.toString(Qt::ISODate));

    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    QString results;

    results.append("<html><body>");
    results.append("<h1>All payments from " + startDate.toString(Qt::ISODate) + " to " + endDate.toString(Qt::ISODate) + "</h1>");
    results.append("<h2 style='text-align: right;'> حركه الخزنة </h2>");

    results.append("<h3></h3>");



    // Table styling to stretch across the page
    results.append("<style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th, td { border: 1px solid black; padding: 8px; text-align: left; }"
                   "th { background-color: #f2f2f2; }"
                   ".valu-column { color: #995400; }"
                   ".cash-column { color: #1A5319; }"
               ".date-column { font-size: 12px; }"
                   "</style>");

    results.append("<table>");
    results.append("<tr>");
    results.append("<th>ID</th><th>Date</th><th>Description</th><th>Visa Amount</th><th>Cash Amount</th><th>Valu Amount</th><th>Note</th>");
    results.append("</tr>");

    double totalVisa = 0.0;
    double totalCash = 0.0;
    double totalValu = 0.0;

    while (query.next()) {
        QString description;
        QString visaAmount = "0";
        QString cashAmount = "0";
        QString valuAmount = "0";

        // Construct description based on conditions
        if (!query.value("pack_id").isNull() && query.value("pt_id").isNull()) {
            description = "<b>ID:</b> " + query.value("customer_id").toString() + "<br>"
                                                                                  "<b>Pack Name:</b> " + query.value("package_name").toString() + "<br>"
                          +"<b>Cus:</b> "+ query.value("customer_name").toString();
        } else if (!query.value("pack_id").isNull() && !query.value("pt_id").isNull()) {
            description = "<b>ID:</b> " + query.value("customer_id").toString() + "<br>"
                                                                                  "<b>PT name:</b> " + query.value("pt_name").toString() + "<br>"
                                                                "<b>Cap:</b> " + query.value("cap_name").toString() + "<br>"
                          + "<b>Cus:</b> "+query.value("customer_name").toString();
        } else {
            description = ""; // Example default case
        }

        // Determine payment type and set amounts accordingly
        QString paymentTypeStr = query.value("payment_type").toString().toLower(); // Convert to lower case for case insensitivity
        if (paymentTypeStr == "cash") {
            cashAmount = query.value("amount").toString();
            totalCash += query.value("amount").toDouble();
        } else if (paymentTypeStr == "visa") {
            visaAmount = query.value("amount").toString();
            totalVisa += query.value("amount").toDouble();
        } else if (paymentTypeStr == "valu") {
            valuAmount = query.value("amount").toString();
            totalValu += query.value("amount").toDouble();
        }

        results.append("<tr>");
        results.append("<td>" + query.value("payment_id").toString() + "</td>");
        results.append("<td class='date-column' >" + query.value("date_pay").toDate().toString(Qt::ISODate) + "</td>");
        results.append("<td>" + description + "</td>");
        results.append("<td>" + visaAmount + "</td>");
        results.append("<td class='cash-column'>" + cashAmount + "</td>");
        results.append("<td class='valu-column'>" + valuAmount + "</td>"); // Apply valu-column class for styling
        results.append("<td>" + query.value("note").toString() + "</td>");
        results.append("</tr>");
    }

    // Adding footer row for totals
    results.append("<tr>");
    results.append("<td colspan='3'><b>Total:</b></td>");
    results.append("<td><b>" + QString::number(totalVisa) + "</b></td>");
    results.append("<td class='cash-column'><b>" + QString::number(totalCash) + "</b></td>");
    results.append("<td class='valu-column'><b>" + QString::number(totalValu) + "</b></td>");
    results.append("<td></td>"); // Note column
    results.append("</tr>");

    results.append("</table>");
    results.append("</body></html>");

    // For testing, you can output results to qDebug() to verify the HTML structure
    qDebug() << results;
    // Print the results
    QPrinter printer;
    QPrintDialog dialog(&printer, this);

    if (dialog.exec() != QDialog::Accepted) {
        return;
    }

    QTextDocument doc;
    doc.setHtml(results);

    // Set page size and orientation to A4
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait);

    doc.setDefaultFont(QFont("Arial", 10));
    doc.print(&printer);
}
void safe::saveAsCsv(QSqlQuery& query, const QString& fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Failed to open file for writing.");
        return;
    }

    QTextStream out(&file);
    out.setEncoding(QStringConverter::Utf8);
    out << QChar(0xFEFF);
    // Write headers
    out << "ID,Date,Description,Visa,Cash,Valu,Note\n";

    // Write data
    while (query.next()) {
        QString description;
        QString visaAmount = "0";
        QString cashAmount = "0";
        QString valuAmount = "0";

        // Construct description based on conditions
        if (!query.value("pack_id").isNull() && query.value("pt_id").isNull()) {
            description = "ID: " + query.value("customer_id").toString() + " "
                          + "Pack Name: " + query.value("package_name").toString() + " "
                          + "Cus: " + query.value("customer_name").toString() + " ";

        } else if (!query.value("pack_id").isNull() && !query.value("pt_id").isNull()) {
            description = "ID: " + query.value("customer_id").toString() + " "
                          + "PT name: " + query.value("pt_name").toString() + " "
                          + "Cap: " + query.value("cap_name").toString() + " "
                          + "Cus: " + query.value("customer_name").toString() + " ";
        } else {
            description = ""; // Example default case
        }

        // Determine payment type and set amounts accordingly
        QString paymentTypeStr = query.value("payment_type").toString().toLower(); // Convert to lower case for case insensitivity
        if (paymentTypeStr == "cash") {
            cashAmount = query.value("amount").toString();
        } else if (paymentTypeStr == "visa") {
            visaAmount = query.value("amount").toString();
        } else if (paymentTypeStr == "valu") {
            valuAmount = query.value("amount").toString();
        }

        out << query.value("payment_id").toString() << ','
            << query.value("date_pay").toDate().toString(Qt::ISODate) << ','
            << description <<','
            << visaAmount << ','
            << cashAmount << ','
            << valuAmount << ','
            << query.value("note").toString() << '\n';
    }

    file.close();
    QMessageBox::information(this, "Success", "File saved successfully.");
}

void safe::saveAsPdf(QSqlQuery& query, const QString& fileName) {
    QString results;

    results.append("<html><body>");
    results.append("<h1>All payments from " + ui->start->date().toString(Qt::ISODate) + " to " + ui->end->date().toString(Qt::ISODate) + "</h1>");
    results.append("<h2 style='text-align: right;'> حركه الخزنة </h2>");

    results.append("<h3></h3>");



    // Table styling to stretch across the page
    results.append("<style>"
                   "table { width: 100%; border-collapse: collapse; }"
                   "th, td { border: 1px solid black; padding: 8px; text-align: left; }"
                   "th { background-color: #f2f2f2; }"
                   ".cash-column { color: #1A5319; }"
                   ".visa-column { color: #0033CC; }"
                   ".valu-column { color: #FF6600; }"
                   ".Vodafone-column { color: #FF0000; }"
                   ".fawary-column { color: #f8ed62 ; }"
                   ".type-column { font-weight: bold; }"
                   ".date-column { font-size: 9px; }"
                   "</style>");

    results.append("<table>");
    results.append("<tr>");
    results.append("<th>ID</th><th>Date</th><th>Description</th><th>Type</th><th>Amount</th><th>Note</th>");
    results.append("</tr>");

    double totalCash = 0.0;
    double totalVisa = 0.0;
    double totalValu = 0.0;
    double totalVodaphone = 0.0;
    double totalFawary = 0.0;
    double totalCredit = 0.0; // Added total for credit
    double grandTotal = 0.0;

    while (query.next()) {
        QString description;
        QString typeClass;
        QString amount = "0";

        // Construct description based on conditions
        if (!query.value("pack_id").isNull() && query.value("pt_id").isNull()) {
            description = "<b>ID:</b> " + query.value("customer_id").toString() + "<br>"
                                                                                  "<b>Pack Name:</b> " + query.value("package_name").toString() + "<br>"
                          + "<b>Cus:</b> " + query.value("customer_name").toString();
        } else if (!query.value("pack_id").isNull() && !query.value("pt_id").isNull()) {
            description = "<b>ID:</b> " + query.value("customer_id").toString() + "<br>"
                                                                                  "<b>PT name:</b> " + query.value("pt_name").toString() + "<br>"
                          + "<b>Cap:</b> " + query.value("cap_name").toString() + "<br>"
                          + "<b>Cus:</b> " + query.value("customer_name").toString();
        } else {
            description = ""; // Example default case
        }

        // Determine payment type and set amounts accordingly
        QString paymentTypeStr = query.value("payment_type").toString().toLower(); // Convert to lower case for case insensitivity
        double amountValue = query.value("amount").toDouble();
        if (paymentTypeStr == "cash") {
            typeClass = "cash-column";
            totalCash += amountValue;
        } else if (paymentTypeStr == "credit") {
            typeClass = "visa-column";
            totalVisa += amountValue;
        } else if (paymentTypeStr == "valu") {
            typeClass = "valu-column";
            totalValu += amountValue;
        } else if (paymentTypeStr == "vodafone") {
            typeClass = "Vodafone-column";
            totalVodaphone += amountValue;
        } else if (paymentTypeStr == "fawary") {
            typeClass = "fawary-column";
            totalFawary += amountValue;
        }else {
            typeClass = ""; // Default case
        }

        grandTotal += amountValue;

        results.append("<tr>");
        results.append("<td>" + query.value("payment_id").toString() + "</td>");
        results.append("<td class='date-column'>" + query.value("date_pay").toDate().toString(Qt::ISODate) + "</td>");
        results.append("<td>" + description + "</td>");
        results.append("<td class='type-column " + typeClass + "'>" + paymentTypeStr + "</td>");
        results.append("<td>" + QString::number(amountValue) + "</td>");
        results.append("<td>" + query.value("note").toString() + "</td>");
        results.append("</tr>");
    }

    // Adding footer rows for totals
    results.append("<tr>");
    results.append("<td colspan='3'><b>Total per Type:</b></td>");
    results.append("<td class='cash-column'><b>" + QString::number(totalCash) + " Cash </b></td>");
    results.append("<td class='visa-column'><b>" + QString::number(totalVisa) + " Visa </b></td>");
    results.append("<td class='valu-column'><b>" + QString::number(totalValu) + " Valu</b></td>");
    results.append("<td class='Vodafone-column'><b>" + QString::number(totalVodaphone) + " Voda </b></td>");
    results.append("<td class='fawary-column'><b>" + QString::number(totalFawary) + " Fawary </b></td>");
    results.append("</tr>");

    // Adding grand total row
    results.append("<tr>");
    results.append("<td colspan='4'><b>Grand Total:</b></td>");
    results.append("<td><b>" + QString::number(grandTotal) + " ALL </b></td>");
    results.append("<td></td>"); // Note column
    results.append("</tr>");

    results.append("</table>");
    results.append("</body></html>");
    QTextDocument doc;
    doc.setHtml(results);

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);

    // Set page size and orientation
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageOrientation(QPageLayout::Portrait);

    doc.print(&printer);

    QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
}
void safe::saveQueryResults() {
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    // Check if start date is greater than end date
    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "Start date cannot be greater than end date.");
        return;
    }

    // Query the database
    QSqlQuery query;
    QString queryString =
        "SELECT "
        "p.id AS payment_id, "
        "p.type AS payment_type, "
        "p.date_pay, "
        "p.customer_id, "
        "p.amount, "
        "p.note, "
        "p.pack_id, "
        "p.pt_id, "
        "c.name AS customer_name, "
        "pod.name AS package_name, "
        "pt_ondesk.name AS pt_name, "
        "cap.name AS cap_name "
        "FROM payment p "
        "LEFT JOIN customer c ON p.customer_id = c.id "
        "LEFT JOIN paackage pack ON p.pack_id = pack.id "
        "LEFT JOIN pt ON p.pt_id = pt.id "
        "LEFT JOIN pt_ondesk pt_ondesk ON pt.pt_ondesk_id = pt_ondesk.id "
        "LEFT JOIN cap ON pt.cap_id = cap.id "
        "LEFT JOIN package_on_desk pod ON pack.pack_id = pod.id "
        "WHERE p.date_pay BETWEEN :start_date AND :end_date "
        "ORDER BY p.date_pay DESC;";

    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);



    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    // Define file filters
    QString defaultSuffix = "csv"; // Default to CSV extension

    updateFileNameExtension("CSV Files (*.csv)");

    if (dialog->exec()) {
        // Get selected file URL and determine selected filter
        QString selectedFilter = dialog->selectedNameFilter();

        // Determine new defaultSuffix based on selected filter
        if (selectedFilter.endsWith("PDF Files (*.pdf)")) {
            defaultSuffix = "pdf";
        } else {
            defaultSuffix = "csv";
        }

        // Get selected file URL and ensure correct extension
        QUrl fileUrl = dialog->selectedUrls().first(); // Get the selected URL
        QString fileName = fileUrl.toLocalFile();

        // Append the correct extension if not already present
        if (!fileName.endsWith("." + defaultSuffix)) {
            fileName += "." + defaultSuffix;
        }

        // Determine saving format and call appropriate function
        if (defaultSuffix == "csv") {
            saveAsCsv(query, fileName);
        } else if (defaultSuffix == "pdf") {
            saveAsPdf(query, fileName);
        } else {
            QMessageBox::warning(this, "Error", "Unsupported file format.");
        }
    }
}
void safe::updateFileNameExtension(const QString &selectedFilter) {
    // Ensure dialog is initialized
    if (!dialog) {
        qDebug() << "QFileDialog dialog is null or not initialized.";
        return;
    }
    QString defaultFileName = "Untitled";  // Default file name
    QString newExtension = "";

    if (selectedFilter == "CSV Files (*.csv)") {
        newExtension = ".csv";
    } else if (selectedFilter == "PDF Files (*.pdf)") {
        newExtension = ".pdf";
    }
    else {
        newExtension = ".csv";
    }

    QString defaultFileNameWithExtension = defaultFileName + newExtension;
    dialog->selectFile(defaultFileNameWithExtension);
}
void safe::closeEvent(QCloseEvent *event){
    emit safe_closed();  // Emit the signal when the widget is close
    QWidget::closeEvent(event);  // Call the base class implementation
}


safe::~safe()
{
    delete ui;
    delete dialog;
}
