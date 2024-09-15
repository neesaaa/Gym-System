#include "sheets.h"
#include "ui_sheets.h"
#include <QTextStream>
#include <QTextDocument>
#include <QDesktopServices>


// For QTextEdit to input multi-line text
sheets::sheets(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::sheets)
{
    ui->setupUi(this);
    result="";

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
    dialog = new QFileDialog(this);
    dialog->setAcceptMode(QFileDialog::AcceptSave);
    dialog->setNameFilters({"CSV Files (*.csv)", "PDF Files (*.pdf)", "All Files (*)"});

    QString darkStyleSheet = R"(
    /* QWidget styling */
    QWidget {
        background-color: #2C3333;
        color: #FFFFFF;
        font-family: Arial, sans-serif;
        font-size: 14px;
    }

    /* Specific widget styling */
    #widget, #widget_16, #widget_17, #widget_18 {
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
    ui->start->setDate(QDate::currentDate());
    ui->end->setDate(QDate::currentDate());


    // Create radio buttons and add them to the layout
    QButtonGroup *buttonGroup = new QButtonGroup(this);
    connect(dialog, &QFileDialog::filterSelected, this, &sheets::updateFileNameExtension);

    for (int i = 1; i <= 11; ++i) {
        QString buttonName = QString("r%1").arg(i);
        QRadioButton *radioButton = findChild<QRadioButton*>(buttonName);

        if (radioButton) {
            buttonGroup->addButton(radioButton, i);
        }
    }
    buttonGroup->setExclusive(true);

    // Connect the button group signal to a slot
    connect(buttonGroup, QOverload<QAbstractButton *, bool>::of(&QButtonGroup::buttonToggled),
            this, &sheets::onButtonToggled);
    connect(ui->print,&QPushButton::clicked,this,&sheets::print);
    connect(ui->save, &QPushButton::clicked, this, &sheets::save);



    this->setStyleSheet(darkStyleSheet);
}

void sheets::onButtonToggled(QAbstractButton *button, bool checked) {
    if (checked) {
        lastSelectedRadioButton = dynamic_cast<QRadioButton*>(button);

        // Assuming endadate is a QDateEdit widget
        if (lastSelectedRadioButton == ui->r5) {
            ui->end->setEnabled(false); // Disable endadate QDateEdit
        } else {
            ui->end->setEnabled(true);  // Enable endadate QDateEdit
        }
    }
}

void sheets::save() {
    if (!lastSelectedRadioButton) {
        QMessageBox::warning(this, "Error", "No radio button selected.");
        return;
    }
    if (dialog->exec() != QDialog::Accepted) {
        return; // If the file dialog is canceled, exit the function
    }

    QUrl fileUrl = dialog->selectedUrls().first(); // Get the selected URL
    QString fileName = fileUrl.toLocalFile();
    if (fileName.isEmpty()) {
        return; // If no file is selected, exit the function
    }


    // Example: Assume lastSelectedRadioButton is the ID of the radio button selected
    int radioButtonId = lastSelectedRadioButton->objectName().mid(1).toInt();

    qDebug() << "Print function called for Radio Button " << radioButtonId;

    switch (radioButtonId) {
    case 1:
        r1_save_slot(); // Call r1_save_slot with data
        break;
    case 2:
        r2_save_slot(); // Call r2_save_slot with data
        break;
    case 3:
        r3_save_slot(); // Call r3_save_slot with data
        break;
    case 4:
        r4_save_slot(); // Call r4_save_slot with data
        break;
    case 5:
        r5_save_slot(); // Call r5_save_slot with data
        break;
    case 6:
        r6_save_slot(); // Call r6_save_slot with data
        break;
    case 7:
        r7_save_slot(); // Call r7_save_slot with data
        break;
    case 8:
        r8_save_slot(); // Call r8_save_slot with data
        break;
    case 9:
        r9_save_slot(); // Call r9_save_slot with data
        break;
    case 10:
        r10_save_slot(); // Call r10_save_slot with data
        break;
    case 11:
        r11_save_slot(); // Call r11_save_slot with data
        break;
    default:
        qDebug() << "Unknown radio button ID.";
        return;
        break;
    }
    if (!result.isEmpty()) {
        if (isPDF) {
            // Generate PDF document
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);
            printer.setPageSize(QPageSize(QPageSize::A4));

            QTextDocument doc;
            doc.clear();  // Clear existing content if any
            doc.setHtml(result);

            // Print the HTML content to PDF
            doc.print(&printer);

            QMessageBox::information(this, "PDF Saved", "PDF file saved successfully.");
            QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
        } else {
            // Export as CSV


            // Save CSV content to file
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream stream(&file);
                stream.setEncoding(QStringConverter::Utf8);
                stream << QChar(0xFEFF);
                stream << result;
                file.close();
                QMessageBox::information(this, "CSV Saved", "CSV file saved successfully.");
            } else {
                QMessageBox::critical(this, "Error", "Could not open file for writing.");
            }
        }
    } else {
        if (isPDF) {
            QMessageBox::warning(this, "Error", "Failed to generate PDF content.");
        } else {
            QMessageBox::warning(this, "Error", "No data to export as CSV.");
        }
    }
    result="";
    isPDF=false;
}


void sheets::print()
{
    if (!lastSelectedRadioButton) {
        QMessageBox::warning(this, "Error", "No radio button selected.");
        return;
    }

    int radioButtonId = lastSelectedRadioButton->objectName().mid(1).toInt();
    qDebug() << "Print function called for Radio Button " << radioButtonId;

    switch (radioButtonId) {
    case 1:
        r1_slot();
        break;
    case 2:
        r2_slot();
        break;
    case 3:
        r3_slot();
        break;
    case 4:
        r4_slot();
        break;
    case 5:
        r5_slot();
        break;
    case 6:
        r6_slot();
        break;
    case 7:
        r7_slot();
        break;
    case 8:
        r8_slot();
        break;
    case 9:
        r9_slot();
        break;
    case 10:
        r10_slot();
        break;
    case 11:
        r11_slot();
        break;
    default:
        qDebug() << "Unknown radio button ID.";
        return;
        break;
    }
    if (!result.isEmpty()) {
        QPrinter printer;
        QPrintDialog dialog(&printer, this);

        if (dialog.exec() != QDialog::Accepted) {
            return;
        }

        QTextDocument doc;
        doc.clear();
        doc.setHtml(result);

        // Set page size and orientation to A4
        printer.setPageSize(QPageSize(QPageSize::A4));
        printer.setPageOrientation(QPageLayout::Portrait);

        doc.setDefaultFont(QFont("Arial", 10));
        doc.print(&printer);
        if (printer.isValid()) {
            doc.print(&printer);
            QMessageBox::information(this, "PDF Saved", "PDF printed and saved successfully.");
        } else {
            QMessageBox::warning(this, "Printer Error", "تقريبا انت فاتح الفايل الهتبدله بنفس الاسم اقفله");
        }
    } else {
        QMessageBox::warning(this, "Error", "Failed to generate PDF content.");
    }
    result="";
    isPDF=false;
}


void sheets::r1_slot() {
    isPDF=true;
    r1_save_slot();

}

void sheets::r2_slot() {
    qDebug() << "Radio Button 2 toggled";
    // Example action for r2
    isPDF=true;
    r2_save_slot();
}

void sheets::r3_slot() {
    qDebug() << "Radio Button 3 toggled";
    isPDF=true;
    r3_save_slot();
}

void sheets::r4_slot() {
    qDebug() << "Radio Button 4 toggled";
    isPDF=true;
    r4_save_slot();
}

void sheets::r5_slot() {
    qDebug() << "Radio Button 5 toggled";
    isPDF=true;
    r5_save_slot();
}

void sheets::r6_slot() {
    qDebug() << "Radio Button 6 toggled";
    isPDF=true;
    r6_save_slot();
}

void sheets::r7_slot() {
    qDebug() << "Radio Button 7 toggled";
    isPDF=true;
    r7_save_slot();
}

void sheets::r8_slot() {
    qDebug() << "Radio Button 8 toggled";
    isPDF=true;
    r8_save_slot();
}

void sheets::r9_slot() {
    qDebug() << "Radio Button 9 toggled";
    isPDF=true;
    r9_save_slot();
}

void sheets::r10_slot() {
    qDebug() << "Radio Button 10 toggled";
    isPDF=true;
    r10_save_slot();
}

void sheets::r11_slot() {
    qDebug() << "Radio Button 11 toggled";
    isPDF=true;
    r11_save_slot();
}


void sheets::r1_save_slot() {
    qDebug() << "Radio Button 1 slot executed for save.";

    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if(startDate>endDate){
        QMessageBox::critical(this, " Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    // Construct SQL query
    QString queryStringPackage =
        "SELECT "
        "    c.name AS customer_name, "
        "    p.today_date AS pack_start, "
        "    p.end_date AS pack_end, "
        "    c.mob_1, "
        "    p.id AS package_id, "
        "    p.net AS pack_net, "
        "    pod.name AS pack_name " // Add pack_name column from package_on_desk table
        "FROM paackage p "
        "LEFT JOIN customer c ON p.customer_id = c.id "
        "LEFT JOIN package_on_desk pod ON p.pack_id = pod.id " // Join with package_on_desk table
        "WHERE p.today_date BETWEEN :start_date AND :end_date "
        "ORDER BY p.today_date DESC;"; // Order by start_date in descending order

    QString queryStringPT =
        "SELECT "
        "    c.name AS customer_name, "
        "    pt.date AS pack_start, "
        "    pt.date AS pack_end, "
        "    c.mob_1, "
        "    pt.package_id AS package_id, "
        "    pt.net AS pack_net, "
        "    pod.name AS pack_name " // Add pack_name column from package_on_desk table
        "FROM pt "
        "INNER JOIN pt_ondesk pod ON pt.pt_ondesk_id = pod.id "
        "INNER JOIN paackage p ON pt.package_id = p.id "
        "INNER JOIN customer c ON p.customer_id = c.id "
        "WHERE pt.date BETWEEN :start_date AND :end_date "
        "ORDER BY pt.date DESC;"; // Order by date in descending order



    QSqlQuery queryPackage, queryPT;

    // Prepare and bind values for package query
    queryPackage.prepare(queryStringPackage);
    queryPackage.bindValue(":start_date", startDate);
    queryPackage.bindValue(":end_date", endDate);

    // Prepare and bind values for pt query
    queryPT.prepare(queryStringPT);
    queryPT.bindValue(":start_date", startDate);
    queryPT.bindValue(":end_date", endDate);

    // Execute the queries
    if (!queryPackage.exec()) {
        QMessageBox::critical(this, "SQL Error", queryPackage.lastError().text());
        return;
    }

    if (!queryPT.exec()) {
        QMessageBox::critical(this, "SQL Error", queryPT.lastError().text());
        return;
    }

    // Create a list to store all rows
    QList<QSqlRecord> allRecords;

    // Fetch all rows from package query
    while (queryPackage.next()) {
        allRecords.append(queryPackage.record());
    }

    // Fetch all rows from pt query
    while (queryPT.next()) {
        allRecords.append(queryPT.record());
    }

    // Sort allRecords by pack_start or pack_end, whichever is larger, in descending order
    std::sort(allRecords.begin(), allRecords.end(), [](const QSqlRecord &r1, const QSqlRecord &r2) {
        QDate date1 = r1.value("pack_start").toDate(); // Use pack_start or pack_end, adjust as needed
        QDate date2 = r2.value("pack_start").toDate(); // Use pack_start or pack_end, adjust as needed
        return date1 > date2; // Sort in descending order
    });
    if(isPDF){

        // Generate HTML content for display
        QString htmlContent = "<html><head><style>"
                              "table {"
                              "  width: 100%;"
                              "  border-collapse: collapse;"
                              "}"
                              "th, td {"
                              "  border: 1px solid black;"
                              "  padding: 8px;"
                              "  text-align: left;"
                              "}"
                              "th {"
                              "  background-color: #f2f2f2;"
                              "}"
                              "</style></head><body>"
                              "<h1>All Packages from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                             "<br>" // Line break for spacing
                                                                                                             "<h2></h2>"
                                                                                                             "<table>"
                                                                                                             "<tr>"
                                                                                                             "<th>Customer Name</th>"
                                                                                                             "<th>Pack Name</th>"
                                                                                                             "<th>Pack Start</th>"
                                                                                                             "<th>Pack End</th>"
                                                                                                             "<th>Mob1</th>"
                                                                                                             "<th>ID</th>"
                                                                                                             "<th>Pack Net</th>"
                                                                                                             "</tr>";

        int totalCount = 0;
        int totalPackNet = 0;

        // Iterate through sorted results
        for (const auto &record : allRecords) {
            QString customerName = record.value("customer_name").toString();
            QString packName = record.value("pack_name").toString(); // Retrieve pack_name
            QString packStart = record.value("pack_start").toDate().toString("yyyy-MM-dd");
            QString packEnd = record.value("pack_end").toDate().toString("yyyy-MM-dd");
            QString mob1 = record.value("mob_1").toString();
            QString packageId = record.value("package_id").toString();
            QString packNetStr = record.value("pack_net").toString();
            int packNet = packNetStr.toInt();

            // Append row to HTML content
            htmlContent += "<tr>"
                           "<td>" + customerName + "</td>"
                                            "<td>" + packName + "</td>"
                                        "<td>" + packStart + "</td>"
                                         "<td>" + packEnd + "</td>"
                                       "<td>" + mob1 + "</td>"
                                    "<td>" + packageId + "</td>"
                                         "<td>" + packNetStr + "</td>"
                                          "</tr>";

            // Increment total count and sum of pack_net
            totalCount++;
            totalPackNet += packNet;
        }

        htmlContent += "</table>";

        // Add footer with total count and sum of pack_net
        htmlContent += "<div style='margin-top: 10px;'>"
                       "<h3>Total Packages: " + QString::number(totalCount) + "</h3>"
                                                       "<h3>Total Pack Net: " + QString::number(totalPackNet) + "</h3>"
                                                         "</div>";

        htmlContent += "</body></html>";

        result = htmlContent;
}
    else {
        QString csvContent = "Customer Name,Pack Name,Pack Start,Pack End,Mob1,ID,Pack Net\n";

        // Iterate through sorted results
        for (const auto &record : allRecords) {
            QString customerName = record.value("customer_name").toString().replace(",", " ");
            QString packName = record.value("pack_name").toString().replace(",", " ");
            QString packStart = record.value("pack_start").toDate().toString("yyyy-MM-dd");
            QString packEnd = record.value("pack_end").toDate().toString("yyyy-MM-dd");
            QString mob1 = record.value("mob_1").toString().replace(",", " ");
            QString packageId = record.value("package_id").toString();
            QString packNetStr = record.value("pack_net").toString();

            // Append row to CSV content
            csvContent += "\"" + customerName + "\","
                                                "\"" + packName + "\","
                                       "\"" + packStart + "\","
                                        "\"" + packEnd + "\","
                                      "\"" + mob1 + "\","
                                   "\"" + packageId + "\","
                                        "\"" + packNetStr + "\"\n";
        }

        result = csvContent;
        }

}

void sheets::r2_save_slot() {
    qDebug() << "Radio Button 2 slot executed for save.";
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if(startDate>endDate){
        QMessageBox::critical(this, " Error", "انت مشقلب التواريخ تقريبا");
        return;
    }
    int daysBetween = startDate.daysTo(endDate);

    // Calculate 0.25% of the number of days (threshold)
    int threshold = static_cast<int>(std::ceil(daysBetween * 0.4));
    threshold=std::max(threshold,1);


    QString queryString =
        "SELECT "
        "    c.name AS customer_name, "
        "    p.start_date AS pack_start, "
        "    p.end_date AS pack_end, "
        "    c.mob_1, "
        "    c.id, " // Add pack_name column from package_on_desk table if needed
        "    fp.count AS fingerprint_count " // Include count attribute from finger_print table
        "FROM "
        "    paackage p "
        "INNER JOIN "
        "    customer c ON p.customer_id = c.id "
        "INNER JOIN ("
        "    SELECT "
        "        f.customer_id, "
        "        COUNT(*) AS count "
        "    FROM "
        "        finger_print f "
        "    WHERE "
        "        f.time BETWEEN :start_date AND :end_date "
        "    GROUP BY "
        "        f.customer_id "
        "    HAVING "
        "        COUNT(*) >= :threshold"
        ") fp ON c.id = fp.customer_id "
        "WHERE "
        "    ("
        "        (p.start_date <= :end_date AND p.end_date >= :start_date) "
        "        OR "
        "        (p.end_date <= :end_date AND p.start_date >= :start_date) "
        "        OR "
        "        (p.start_date <= :start_date AND p.end_date >= :start_date AND p.end_date <= :end_date) "
        "        OR "
        "        (p.start_date >= :start_date AND p.start_date <= :end_date AND p.end_date <= :end_date) "
        "    ) "
        "ORDER BY "
        "    p.end_date;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":end_date", endDate);
    query.bindValue(":start_date", startDate);
    query.bindValue(":threshold", threshold);  // Bind your threshold value


    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    if (isPDF){
        QString html = "<html><head><style>"
                              "table {"
                              "  width: 100%;"
                              "  border-collapse: collapse;"
                              "}"
                              "th, td {"
                              "  border: 1px solid black;"
                              "  padding: 8px;"
                              "  text-align: left;"
                              "}"
                              "th {"
                              "  background-color: #f2f2f2;"
                              "}"
                              "</style></head><body>"
                              "<h1>All Active Packages from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                             "<br>" // Line break for spacing
                                                                                                             "<h2></h2>"
                                                                                                             "<table>"
                                                                                                             "<tr>"
                                                                                                             "<th>Customer ID</th>"
                                                                                                             "<th>Customer Name</th>"
                                                                                                             "<th>Mob1</th>"
                                                                                                             "<th>Start Date</th>"
                                                                                                             "<th>End Date</th>"
                                                                                                             "<th>count</th>"

                                                                                                             "</tr>";
        int totalCount=0;
        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            int count = query.value("fingerprint_count").toInt();  // Corrected variable name

            totalCount++;

            html += "<tr>"
                    "<td>" + QString::number(customerId) + "</td>"
                                                    "<td>" + customerName + "</td>"
                                     "<td>" + mob1 + "</td>"
                             "<td>" + packStart.toString("yyyy-MM-dd") + "</td>"
                                                         "<td>" + packEnd.toString("yyyy-MM-dd") + "</td>"
                                                       "<td>" + QString::number(count) + "</td>"  // Corrected count display
                                               "</tr>";
        }
        html += "</table>"
                       "<footer>"
                       "<p>Total Records: <b>" + QString::number(totalCount) + "</b></p>"
                                                       "</footer>"
                                                       "</body>"
                                                       "</html>";
        result=html;
    }
    else {
        QString csv = "ID,Customer Name,Mobile,Start Date,End Date\n";

        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();

            csv += QString::number(customerId) + ","
                   + customerName + ","
                   + mob1 + ","
                   + packStart.toString("yyyy-MM-dd") + ","
                   + packEnd.toString("yyyy-MM-dd") + "\n";
        }
        result=csv;


    }


}

void sheets::r3_save_slot() {
    qDebug() << "Radio Button 3 slot executed for save.";
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if(startDate>endDate){
        QMessageBox::critical(this, " Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    QString queryString =
        "SELECT "
        "c.sales_name AS sales_rep, " // Assuming 'sales_name' is the correct column name for sales representative
        "COUNT(p.customer_id) AS id_count, "   // Count of customer IDs
        "SUM(CAST(p.net AS INTEGER)) AS total_net "    // Sum of pack.net (assuming net is stored as text)
        "FROM paackage p "
        "INNER JOIN customer c ON p.customer_id = c.id "
        "WHERE p.today_date >= :start_date AND p.today_date <= :end_date " // Filter by start_date and end_date
        "GROUP BY c.sales_name "   // Grouping by sales representative's name
        "ORDER BY c.sales_name;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);


    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    if (isPDF){
        QString htmlContent = "<html><head><style>"
                              "table {"
                              "  width: 100%;"
                              "  border-collapse: collapse;"
                              "}"
                              "th, td {"
                              "  border: 1px solid black;"
                              "  padding: 12px;"
                              "  text-align: left;"
                              "}"
                              "th {"
                              "  background-color: #f2f2f2;"
                              "}"
                              ".sales-column {"
                              "  width: auto; /* Allow column to stretch */"
                              "}"
                              ".count-column, .total-column {"
                              "  width: 1px; /* Minimum width, will stretch */"
                              "  white-space: nowrap; /* Prevent wrapping */"
                              "}"
                              "</style></head><body>"
                              "<h1><i>Sales Report</i> from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd")+ "</h1>"
                              "<br></br>"
                              "<table>"
                              "<tr>"
                              "<th class='sales-column'>Sales  &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp; &nbsp;</th>" // Adjust spacing as needed
                              "<th class='count-column'>Count           &nbsp;</th>"
                              "<th class='total-column'>Total           &nbsp;</th>"
                              "</tr>";


        // Loop through your query results to populate the table rows
        while (query.next()) {
            QString salesRep = query.value("sales_rep").toString();
            int idCount = query.value("id_count").toInt();
            double totalNet = query.value("total_net").toDouble();

            htmlContent += "<tr>"
                           "<td class='sales-column'>" + salesRep + "</td>"
                                        "<td class='count-column'>" + QString::number(idCount) + "</td>"
                                                        "<td class='total-column'>" + QString::number(totalNet) + "</td>"
                                                         "</tr>";
        }

        htmlContent += "</table>"
                       "</body>"
                       "</html>";

        result = htmlContent;

    }
    else{
        QString csvContent = "Sales,Count,Total\n"; // CSV header

        while (query.next()) {
            QString salesRep = query.value("sales_rep").toString();
            int idCount = query.value("id_count").toInt();
            double totalNet = query.value("total_net").toDouble();

            csvContent += salesRep + "," + QString::number(idCount) + "," + QString::number(totalNet) + "\n";
        }
        result=csvContent;
    }
}


void sheets::r4_save_slot() {
    qDebug() << "Radio Button 4 slot executed for save.";
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "Start date cannot be after end date.");
        return;
    }

    if (isPDF) {
        result = "<html><head><style>"
                 "table {"
                 "  width: 100%;"
                 "  border-collapse: collapse;"
                 "}"
                 "th, td {"
                 "  border: 1px solid black;"
                 "  padding: 8px;"
                 "  text-align: left;"
                 "}"
                 "th {"
                 "  background-color: #f2f2f2;"
                 "}"
                 "</style></head><body>";
        result += "<h1> كشف تفصيلى باقه </h1>";
        result += "<h1> From " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>";
    } else {
        result = "Package,Customer ID,Customer Name,Start Date,End Date,Net Value\n";
    }

    QString packageQueryStr =
        "SELECT DISTINCT p.pack_id, pod.name AS pack_name "
        "FROM paackage p "
        "INNER JOIN package_on_desk pod ON p.pack_id = pod.id "
        "WHERE p.today_date BETWEEN :start_date AND :end_date";

    QSqlQuery packageQuery;
    packageQuery.prepare(packageQueryStr);
    packageQuery.bindValue(":start_date", startDate);
    packageQuery.bindValue(":end_date", endDate);

    if (!packageQuery.exec()) {
        QMessageBox::critical(this, "SQL Error", packageQuery.lastError().text());
        return;
    }

    int totalRecords = 0;
    double totalNetValue = 0.0;

    while (packageQuery.next()) {
        int packageId = packageQuery.value("pack_id").toInt();
        QString packageName = packageQuery.value("pack_name").toString();

        if (isPDF) {
            result += "<h1>Package: " + packageName + "</h1>";
            result += "<table>"
                      "<tr>"
                      "<th>Customer ID</th>"
                      "<th>Customer Name</th>"
                      "<th>Customer mobile</th>"
                      "<th>Start Date</th>"
                      "<th>End Date</th>"
                      "<th>Pack Net</th>"
                      "</tr>";
        }
        else {
            result += "\nPT Package: " + packageName + "\nCustomer ID,Customer Name,Customer Mob,Start Date,End Date,Net Value\n";
        }

        QString queryString =
            "SELECT "
            "    c.id AS customer_id, "
            "    c.name AS customer_name, "
            "    c.mob_1 AS customer_Mobile,                "
            "    p.start_date AS pack_start, "
            "    p.end_date AS pack_end, "
            "    p.net AS pack_net "
            "FROM "
            "    paackage p "
            "INNER JOIN "
            "    customer c ON p.customer_id = c.id "
            "WHERE "
            "    p.pack_id = :package_id "
            "AND "
            "    p.today_date BETWEEN :start_date AND :end_date "
            "ORDER BY "
            "    p.end_date;";

        QSqlQuery query;
        query.prepare(queryString);
        query.bindValue(":package_id", packageId);
        query.bindValue(":start_date", startDate);
        query.bindValue(":end_date", endDate);

        if (!query.exec()) {
            QMessageBox::critical(this, "SQL Error", query.lastError().text());
            continue;
        }

        int packageRecordCount = 0;
        double packageNetValue = 0.0;

        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerName = query.value("customer_name").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            double packNet = query.value("pack_net").toDouble();
            QString mob = query.value("customer_Mobile").toString();


            if (isPDF) {
                result += "<tr>"
                          "<td>" + QString::number(customerId) + "</td>"
                                                          "<td>" + customerName + "</td>"
                                           "<td>" + mob + "</td>"
                                           "<td>" + packStart.toString("yyyy-MM-dd") + "</td>"
                                                               "<td>" + packEnd.toString("yyyy-MM-dd") + "</td>"
                                                             "<td>" + QString::number(packNet, 'f', 2) + "</td>"
                                                               "</tr>";
            } else {
                result +=  QString::number(customerId) + "," + customerName + ","+mob+ "," + packStart.toString("yyyy-MM-dd") + "," + packEnd.toString("yyyy-MM-dd") + "," + QString::number(packNet, 'f', 2) + "\n";
            }

            packageRecordCount++;
            packageNetValue += packNet;
        }

        if (isPDF) {
            result += "</table>"
                      "<footer>"
                      "<p>Package customers: <b>" + QString::number(packageRecordCount) + "</b></p>"
                                                              "<p>Total Net Value: <b>" + QString::number(packageNetValue, 'f', 2) + "</b></p>"
                                                                   "</footer><br>";
        }

        totalRecords += packageRecordCount;
        totalNetValue += packageNetValue;
    }

    // Adding PT packages section
    QString ptQueryStr =
        "SELECT DISTINCT p.pt_ondesk_id, pod.name AS pt_name "
        "FROM pt p "
        "INNER JOIN pt_ondesk pod ON p.pt_ondesk_id = pod.id "
        "INNER JOIN paackage pk ON p.package_id = pk.id "
        "WHERE pk.today_date BETWEEN :start_date AND :end_date";

    QSqlQuery ptQuery;
    ptQuery.prepare(ptQueryStr);
    ptQuery.bindValue(":start_date", startDate);
    ptQuery.bindValue(":end_date", endDate);

    if (!ptQuery.exec()) {
        QMessageBox::critical(this, "SQL Error", ptQuery.lastError().text());
        return;
    }

    while (ptQuery.next()) {
        int ptOnDeskId = ptQuery.value("pt_ondesk_id").toInt();
        QString ptName = ptQuery.value("pt_name").toString();

        if (isPDF) {
            result += "<h1>PT Package: " + ptName + "</h1>";
            result += "<table>"
                      "<tr>"
                      "<th>Customer ID</th>"
                      "<th>Customer Name</th>"
                      "<th>Customer Mobile</th>"
                      "<th>Registered Date</th>"
                      "<th>Net Value</th>"
                      "</tr>";
        } else {
            result += "\nPT Package: " + ptName + "\nCustomer ID,Customer Name,Customer Mobile,Registered Date,Net Value\n";
        }

        QString ptQueryString =
            "SELECT "
            "    c.id AS customer_id, "
            "    c.name AS customer_name, "
            "    c.mob_1 AS customer_Mobile,                "
            "    p.date AS pt_date, "
            "    p.net AS pt_net "
            "FROM "
            "    pt p "
            "INNER JOIN "
            "    paackage pk ON p.package_id = pk.id "
            "INNER JOIN "
            "    customer c ON pk.customer_id = c.id "
            "WHERE "
            "    p.pt_ondesk_id = :pt_ondesk_id "
            "AND "
            "    pk.today_date BETWEEN :start_date AND :end_date "
            "ORDER BY "
            "    p.date;";

        QSqlQuery ptDetailsQuery;
        ptDetailsQuery.prepare(ptQueryString);
        ptDetailsQuery.bindValue(":pt_ondesk_id", ptOnDeskId);
        ptDetailsQuery.bindValue(":start_date", startDate);
        ptDetailsQuery.bindValue(":end_date", endDate);

        if (!ptDetailsQuery.exec()) {
            QMessageBox::critical(this, "SQL Error", ptDetailsQuery.lastError().text());
            continue;
        }

        int ptRecordCount = 0;
        double ptNetValue = 0.0;

        while (ptDetailsQuery.next()) {
            int customerId = ptDetailsQuery.value("customer_id").toInt();
            QString customerName = ptDetailsQuery.value("customer_name").toString();
            QString mob = ptDetailsQuery.value("customer_Mobile").toString();

            QDate ptDate = ptDetailsQuery.value("pt_date").toDate();
            double ptNet = ptDetailsQuery.value("pt_net").toDouble();

            if (isPDF) {
                result += "<tr>"
                          "<td>" + QString::number(customerId) + "</td>"
                                                          "<td>" + customerName + "</td>"
                                                "<td>" + mob + "</td>"

                                           "<td>" + ptDate.toString("yyyy-MM-dd") + "</td>"
                                                            "<td>" + QString::number(ptNet, 'f', 2) + "</td>"
                                                             "</tr>";
            } else {
                result += QString::number(customerId) + "," + customerName + ","+ mob +"," + ptDate.toString("yyyy-MM-dd") + "," + QString::number(ptNet, 'f', 2) + "\n";
            }

            ptRecordCount++;
            ptNetValue += ptNet;
        }

        if (isPDF) {
            result += "</table>"
                      "<footer>"
                      "<p>PT records: <b>" + QString::number(ptRecordCount) + "</b></p>"
                                                         "<p>Total Net Value: <b>" + QString::number(ptNetValue, 'f', 2) + "</b></p>"
                                                              "</footer><br>";
        }

        totalRecords += ptRecordCount;
        totalNetValue += ptNetValue;
    }

    if (isPDF) {
        result += "<footer>"
                  "<p>Total records: <b>" + QString::number(totalRecords) + "</b></p>"
                                                    "<p>Total Net Value: <b>" + QString::number(totalNetValue, 'f', 2) + "</b></p>"
                                                             "</footer>"
                                                             "</body></html>";
    }
}

void sheets::r5_save_slot() {
    qDebug() << "Radio Button 5 slot executed for save.";

    QDate startDate = ui->start->date();
    QDate endDate = startDate.addDays(15);


    QString queryString = "SELECT "
                          "    c.name AS customer_name, "
                          "    p.start_date AS pack_start, "
                          "    p.end_date AS pack_end, "
                          "    c.mob_1, "
                          "    c.id, "
                          "    0 AS fingerprint_count "
                          "FROM "
                          "    paackage p "
                          "INNER JOIN "
                          "    customer c ON p.customer_id = c.id "
                          "WHERE "
                          "    ("
                          "        (p.start_date <= :end_date AND p.end_date >= :start_date) "
                          "        OR "
                          "        (p.end_date <= :end_date AND p.start_date >= :start_date) "
                          "        OR "
                          "        (p.start_date <= :start_date AND p.end_date >= :start_date) "
                          "        OR "
                          "        (p.start_date >= :start_date AND p.start_date <= :end_date AND p.end_date <= :end_date) "
                          "    ) "
                          "AND NOT EXISTS ("
                          "    SELECT "
                          "        1 "
                          "    FROM "
                          "        finger_print f "
                          "    WHERE "
                          "        f.customer_id = c.id "
                          "        AND f.time BETWEEN :start_date AND :end_date"
                          ") "
                          "ORDER BY "
                          "    p.end_date;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);

    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }
    if (isPDF){
        QString html = "<html><head><style>"
                       "table {"
                       "  width: 100%;"
                       "  border-collapse: collapse;"
                       "}"
                       "th, td {"
                       "  border: 1px solid black;"
                       "  padding: 8px;"
                       "  text-align: left;"
                       "}"
                       "th {"
                       "  background-color: #f2f2f2;"
                       "}"
                       "</style></head><body>"
                       "<h1>All Inactive Packages from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                      "<br>" // Line break for spacing
                                                                                                      "<h2></h2>"
                                                                                                      "<table>"
                                                                                                      "<tr>"
                                                                                                      "<th>Customer ID</th>"
                                                                                                      "<th>Customer Name</th>"
                                                                                                      "<th>Mob1</th>"
                                                                                                      "<th>Start Date</th>"
                                                                                                      "<th>End Date</th>"
                                                                                                      "<th>count</th>"

                                                                                                      "</tr>";
        int totalCount=0;
        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            int count = query.value("fingerprint_count").toInt();  // Corrected variable name

            totalCount++;

            html += "<tr>"
                    "<td>" + QString::number(customerId) + "</td>"
                                                    "<td>" + customerName + "</td>"
                                     "<td>" + mob1 + "</td>"
                             "<td>" + packStart.toString("yyyy-MM-dd") + "</td>"
                                                         "<td>" + packEnd.toString("yyyy-MM-dd") + "</td>"
                                                       "<td>" + QString::number(count) + "</td>"  // Corrected count display
                                               "</tr>";
        }
        html += "</table>"
                "<footer>"
                "<p>Total Records: <b>" + QString::number(totalCount) + "</b></p>"
                                                "</footer>"
                                                "</body>"
                                                "</html>";
        result=html;
    }
    else {
        QString csv = "ID,Customer Name,Mobile,Start Date,End Date\n";

        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();

            csv += QString::number(customerId) + ","
                   + customerName + ","
                   + mob1 + ","
                   + packStart.toString("yyyy-MM-dd") + ","
                   + packEnd.toString("yyyy-MM-dd") + "\n";
        }
        result=csv;


    }
}

void sheets::r6_save_slot() {
    qDebug() << "Radio Button 6 slot executed for save.";
    qDebug() << "Generating Invitation Report.";

    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    QString queryString =
        "SELECT "
        "    c.id AS customer_id, "
        "    c.name AS customer_name, "
        "    c.mob_1 AS customer_mobile, "
        "    i.name AS invited_name, "
        "    i.phone_number AS invited_mobile, "
        "    i.time AS inv_time "
        "FROM "
        "    inv i "
        "INNER JOIN "
        "    paackage p ON i.pack_id = p.id "
        "INNER JOIN "
        "    customer c ON p.customer_id = c.id "
        "WHERE "
        "    i.time BETWEEN :start_date AND :end_date "
        "ORDER BY "
        "    i.time;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);

    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    if (isPDF) {
        QString html = "<html><head><style>"
                       "table {"
                       "  width: 100%;"
                       "  border-collapse: collapse;"
                       "}"
                       "th, td {"
                       "  border: 1px solid black;"
                       "  padding: 8px;"
                       "  text-align: left;"
                       "}"
                       "th {"
                       "  background-color: #f2f2f2;"
                       "}"
                       "</style></head><body>"
                       "<h1>Invitation Records from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                      "<br>"
                                                                                                      "<table>"
                                                                                                      "<tr>"
                                                                                                      "<th>Customer ID</th>"
                                                                                                      "<th>Customer Name</th>"
                                                                                                      "<th>Customer Mobile</th>"
                                                                                                      "<th>Invited Name</th>"
                                                                                                      "<th>Invited Mobile</th>"
                                                                                                      "<th>Invitation Time</th>"
                                                                                                      "</tr>";

        int totalCount = 0;
        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString customerMobile = query.value("customer_mobile").toString();
            QString invitedName = query.value("invited_name").toString();
            QString invitedMobile = query.value("invited_mobile").toString();
            QDateTime invTime = query.value("inv_time").toDateTime();

            totalCount++;

            html += "<tr>"
                    "<td>" + QString::number(customerId) + "</td>"
                                                    "<td>" + customerName + "</td>"
                                     "<td>" + customerMobile + "</td>"
                                       "<td>" + invitedName + "</td>"
                                    "<td>" + invitedMobile + "</td>"
                                      "<td>" + invTime.toString("yyyy-MM-dd hh:mm:ss") + "</td>"
                                                                "</tr>";
        }

        html += "</table>"
                "<footer>"
                "<p>Total Records: <b>" + QString::number(totalCount) + "</b></p>"
                                                "</footer>"
                                                "</body>"
                                                "</html>";

        result = html;
    } else {
        QString csv = "Customer ID,Customer Name,Customer Mobile,Invited Name,Invited Mobile,Invitation Time\n";

        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString customerMobile = query.value("customer_mobile").toString();
            QString invitedName = query.value("invited_name").toString();
            QString invitedMobile = query.value("invited_mobile").toString();
            QDateTime invTime = query.value("inv_time").toDateTime();

            csv += QString::number(customerId) + ","
                   + customerName + ","
                   + customerMobile + ","
                   + invitedName + ","
                   + invitedMobile + ","
                   + invTime.toString("yyyy-MM-dd hh:mm:ss") + "\n";
        }

        result = csv;
    }
}


void sheets::r7_save_slot() {
    qDebug() << "Radio Button 7 slot executed for save.";
    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if(startDate>endDate){
        QMessageBox::critical(this, " Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    QString queryString =
        "SELECT "
        "c.sales_name AS sales_rep, "      // Sales representative's name
        "CAST(p.net AS INTEGER) AS total_net, "    // Net value from the package table
        "c.mob_1 AS mob1, "                // Customer's mobile number 1
        "c.mob_2 AS mob2, "                // Customer's mobile number 2
        "p.end_date, "                     // Package end date
        "p.start_date, "                   // Package start date
        "c.name AS customer_name, "        // Customer's name
        "c.id AS customer_id "             // Customer's ID
        "FROM paackage p "
        "INNER JOIN customer c ON p.customer_id = c.id "
        "WHERE p.end_date >= :start_date AND p.end_date <= :end_date " // Filter by end_date
        "AND NOT EXISTS ("
        "    SELECT 1 "
        "    FROM paackage p2 "
        "    WHERE p2.customer_id = c.id "
        "    AND p2.start_date > p.end_date"
        ") "
        "ORDER BY p.end_date;";
    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);


    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }
    if(isPDF){

        QString htmlContent = "<html><head><style>"
                              "table {"
                              "  width: 100%;"
                              "  border-collapse: collapse;"
                              "}"
                              "th, td {"
                              "  border: 1px solid black;"
                              "  padding: 8px;"  // Decreased padding for smaller cell height
                              "  text-align: left;"
                              "}"
                              "th {"
                              "  background-color: #f2f2f2;"
                              "}"
                              ".sales-column, .count-column, .total-column {"
                              "  padding: 8px;"  // Adjusted padding for consistency
                              "  white-space: nowrap;"  // Prevent wrapping
                              "}"
                              ".sales-column {"
                              "  width: auto; /* Allow column to stretch */"
                              "}"
                              ".count-column, .total-column {"
                              "  min-width: 80px; /* Minimum width, will stretch */"
                              "}"
                              ".footer-row {"
                              "  font-weight: bold;"
                              "}"
                              "</style></head><body>"
                              "<h1>كشف الاشتراكات المنتهيه </h1>"
                              "<h1>" + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                             "<br></br>"
                                                                                                             "<table>"
                                                                                                             "<tr>"
                                                                                                             "<th class='total-column'>Total</th>"
                                                                                                             "<th class='sales-column'>Sales</th>"
                                                                                                             "<th class='count-column'>Mob 1</th>"
                                                                                                             "<th class='count-column'>Mob 2</th>"
                                                                                                             "<th class='count-column'>End Date</th>"
                                                                                                             "<th class='count-column'>Start Date</th>"
                                                                                                             "<th class='count-column'>Customer Name</th>"
                                                                                                             "<th class='count-column'>ID</th>"
                                                                                                             "</tr>";

        int totalNetSum = 0;
        int customerCount = 0;

        // Execute the query and populate HTML table
        while (query.next()) {
            QString totalNet = query.value("total_net").toString();
            QString salesRep = query.value("sales_rep").toString();
            QString mob1 = query.value("mob1").toString();
            QString mob2 = query.value("mob2").toString();
            QString endDate = query.value("end_date").toDate().toString("yyyy-MM-dd");
            QString startDate = query.value("start_date").toDate().toString("yyyy-MM-dd");
            QString customerName = query.value("customer_name").toString();
            QString customerId = query.value("customer_id").toString();

            // Sum up total_net
            totalNetSum += totalNet.toInt();
            customerCount++;

            htmlContent += "<tr>"
                           "<td class='total-column'>" + totalNet + "</td>"
                                        "<td class='sales-column'>" + salesRep + "</td>"
                                        "<td class='count-column'>" + mob1 + "</td>"
                                    "<td class='count-column'>" + mob2 + "</td>"
                                    "<td class='count-column'>" + endDate + "</td>"
                                       "<td class='count-column'>" + startDate + "</td>"
                                         "<td class='count-column'>" + customerName + "</td>"
                                            "<td class='count-column'>" + customerId + "</td>"
                                          "</tr>";
        }

        htmlContent += "<tr class='footer-row'>"
                       "<td class='total-column' colspan='2'>Total Sum: " + QString::number(totalNetSum) + "</td>"
                                                        "<td colspan='5'></td>"
                                                        "<td class='count-column'>Total Count: " + QString::number(customerCount) + "</td>"
                                                          "</tr>";


        htmlContent += "</table>"
                       "</body>"
                       "</html>";

        result = htmlContent;
}
    else {
        // Generate CSV content
        QString csvContent = "Total Net,Sales Rep,Mobile Number 1,Mobile Number 2,Package End Date,Package Start Date,Customer Name,Customer ID\n"; // CSV header

        // Execute the query and populate CSV content
        while (query.next()) {
            QString totalNet = query.value("total_net").toString();
            QString salesRep = query.value("sales_rep").toString();
            QString mob1 = query.value("mob1").toString();
            QString mob2 = query.value("mob2").toString();
            QString endDate = query.value("end_date").toDate().toString("yyyy-MM-dd");
            QString startDate = query.value("start_date").toDate().toString("yyyy-MM-dd");
            QString customerName = query.value("customer_name").toString();
            QString customerId = query.value("customer_id").toString();

            csvContent += totalNet + ","
                          + salesRep + ","
                          + mob1 + ","
                          + mob2 + ","
                          + endDate + ","
                          + startDate + ","
                          + customerName + ","
                          + customerId + "\n";
        }

        result = csvContent;
        }
}

void sheets::r8_save_slot() {
    qDebug() << "Radio Button 8 slot executed for save.";

    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if(startDate>endDate){
        QMessageBox::critical(this, " Error", "انت مشقلب التواريخ تقريبا");
        return;
    }
    int daysBetween = startDate.daysTo(endDate);

    // Calculate 0.25% of the number of days (threshold)
    int threshold = static_cast<int>(std::ceil(daysBetween * 0.4));
    threshold=std::max(threshold,1);

    QString queryString =
        "SELECT "
        "    c.name AS customer_name, "
        "    p.start_date AS pack_start, "
        "    p.end_date AS pack_end, "
        "    c.mob_1, "
        "    c.id, " // Add pack_name column from package_on_desk table if needed
        "    fp.count AS fingerprint_count " // Include count attribute from finger_print table
        "FROM "
        "    paackage p "
        "INNER JOIN "
        "    customer c ON p.customer_id = c.id "
        "INNER JOIN ("
        "    SELECT "
        "        f.customer_id, "
        "        COUNT(*) AS count "
        "    FROM "
        "        finger_print f "
        "    WHERE "
        "        f.time BETWEEN :start_date AND :end_date "
        "    GROUP BY "
        "        f.customer_id "
        "    HAVING "
        "        COUNT(*) < :threshold"
        ") fp ON c.id = fp.customer_id "
        "WHERE "
        "    ("
        "        (p.start_date <= :end_date AND p.end_date >= :start_date) "
        "        OR "
        "        (p.end_date <= :end_date AND p.start_date >= :start_date) "
        "        OR "
        "        (p.start_date <= :start_date AND p.end_date >= :start_date AND p.end_date <= :end_date) "
        "        OR "
        "        (p.start_date >= :start_date AND p.start_date <= :end_date AND p.end_date <= :end_date) "
        "    ) "
        "ORDER BY "
        "    p.end_date;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":end_date", endDate);
    query.bindValue(":start_date", startDate);
    query.bindValue(":threshold", threshold);  // Bind your threshold value


    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    if (isPDF){
        QString html = "<html><head><style>"
                       "table {"
                       "  width: 100%;"
                       "  border-collapse: collapse;"
                       "}"
                       "th, td {"
                       "  border: 1px solid black;"
                       "  padding: 8px;"
                       "  text-align: left;"
                       "}"
                       "th {"
                       "  background-color: #f2f2f2;"
                       "}"
                       "</style></head><body>"
                       "<h1>All Inactive Packages from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                      "<br>" // Line break for spacing
                                                                                                      "<h2></h2>"
                                                                                                      "<table>"
                                                                                                      "<tr>"
                                                                                                      "<th>Customer ID</th>"
                                                                                                      "<th>Customer Name</th>"
                                                                                                      "<th>Mob1</th>"
                                                                                                      "<th>Start Date</th>"
                                                                                                      "<th>End Date</th>"
                                                                                                      "<th>count</th>"

                                                                                                      "</tr>";
        int totalCount=0;
        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            int count = query.value("fingerprint_count").toInt();  // Corrected variable name

            totalCount++;

            html += "<tr>"
                    "<td>" + QString::number(customerId) + "</td>"
                                                    "<td>" + customerName + "</td>"
                                     "<td>" + mob1 + "</td>"
                             "<td>" + packStart.toString("yyyy-MM-dd") + "</td>"
                                                         "<td>" + packEnd.toString("yyyy-MM-dd") + "</td>"
                                                       "<td>" + QString::number(count) + "</td>"  // Corrected count display
                                               "</tr>";
        }
        html += "</table>"
                "<footer>"
                "<p>Total Records: <b>" + QString::number(totalCount) + "</b></p>"
                                                "</footer>"
                                                "</body>"
                                                "</html>";
        result=html;
    }
    else {
        QString csv = "ID,Customer Name,Mobile,Start Date,End Date\n";

        while (query.next()) {
            int customerId = query.value("id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();

            csv += QString::number(customerId) + ","
                   + customerName + ","
                   + mob1 + ","
                   + packStart.toString("yyyy-MM-dd") + ","
                   + packEnd.toString("yyyy-MM-dd") + "\n";
        }
        result=csv;


    }
}

void sheets::r9_save_slot() {
    qDebug() << "Radio Button 9 slot executed for save.";
    r1_save_slot();
}

void sheets::r10_save_slot() {
    qDebug() << "Radio Button 10 slot executed for save.";
    qDebug() << "Generating Package Report.";

    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    // Query to get distinct packages and their names within the specified date range
    QString packageQueryStr =
        "SELECT DISTINCT p.pack_id, pod.name AS pack_name "
        "FROM paackage p "
        "INNER JOIN package_on_desk pod ON p.pack_id = pod.id "
        "WHERE p.today_date BETWEEN :start_date AND :end_date";

    QSqlQuery packageQuery;
    packageQuery.prepare(packageQueryStr);
    packageQuery.bindValue(":start_date", startDate);
    packageQuery.bindValue(":end_date", endDate);

    if (!packageQuery.exec()) {
        QMessageBox::critical(this, "SQL Error", packageQuery.lastError().text());
        return;
    }

    QMap<QString, QPair<int, int>> packageNetSums; // QPair<total_net, record_count>
    QMap<int, QString> packageNames; // Map pack_id to pack_name

    while (packageQuery.next()) {
        int packageId = packageQuery.value("pack_id").toInt();
        QString packageName = packageQuery.value("pack_name").toString();
        packageNames[packageId] = packageName;
    }

    // Aggregate net and count for each package
    foreach (int packageId, packageNames.keys()) {
        QString aggregateQueryStr =
            "SELECT SUM(CAST(p.net AS INTEGER)) AS total_net, COUNT(p.id) AS record_count "
            "FROM paackage p "
            "WHERE p.pack_id = :package_id "
            "GROUP BY p.pack_id";

        QSqlQuery aggregateQuery;
        aggregateQuery.prepare(aggregateQueryStr);
        aggregateQuery.bindValue(":package_id", packageId);

        if (!aggregateQuery.exec()) {
            QMessageBox::critical(this, "SQL Error", aggregateQuery.lastError().text());
            return;
        }

        if (aggregateQuery.next()) {
            int totalNet = aggregateQuery.value("total_net").toInt();
            int recordCount = aggregateQuery.value("record_count").toInt();
            packageNetSums[packageNames[packageId]] = qMakePair(totalNet, recordCount);
        }
    }

    // Query to get PT types and their aggregated data
    QString ptQueryStr =
        "SELECT pt_ondesk.name AS pt_type_name, SUM(pt.net) AS total_net, COUNT(pt.id) AS record_count "
        "FROM pt "
        "INNER JOIN pt_ondesk ON pt.pt_ondesk_id = pt_ondesk.id "
        "WHERE pt.date BETWEEN :start_date AND :end_date "
        "GROUP BY pt_ondesk.name";

    QSqlQuery ptQuery;
    ptQuery.prepare(ptQueryStr);
    ptQuery.bindValue(":start_date", startDate);
    ptQuery.bindValue(":end_date", endDate);

    if (!ptQuery.exec()) {
        QMessageBox::critical(this, "SQL Error", ptQuery.lastError().text());
        return;
    }

    QMap<QString, QPair<int, int>> ptNetSums; // QPair<total_net, record_count>

    while (ptQuery.next()) {
        QString ptTypeName = ptQuery.value("pt_type_name").toString();
        int totalNet = ptQuery.value("total_net").toInt();
        int recordCount = ptQuery.value("record_count").toInt();
        ptNetSums[ptTypeName] = qMakePair(totalNet, recordCount);
    }

    if (isPDF) {
        QString html = "<html><head><style>"
                       "table {"
                       "  width: 100%;"
                       "  border-collapse: collapse;"
                       "}"
                       "th, td {"
                       "  border: 1px solid black;"
                       "  padding: 8px;"
                       "  text-align: left;"
                       "}"
                       "th {"
                       "  background-color: #f2f2f2;"
                       "}"
                       "</style></head><body>"
                       "<h1>كشف باقه إجمالى </h1>"
                       "<h1> from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                      "<br>"
                                                                                                      "<h2>Package Records</h2>"
                                                                                                      "<table>"
                                                                                                      "<tr>"
                                                                                                      "<th>Package Name</th>"
                                                                                                      "<th>Total Net</th>"
                                                                                                      "<th>Record Count</th>"
                                                                                                      "</tr>";

        QMapIterator<QString, QPair<int, int>> it(packageNetSums);
        while (it.hasNext()) {
            it.next();
            QString packageName = it.key();
            int totalNet = it.value().first;
            int recordCount = it.value().second;

            html += "<tr>"
                    "<td>" + packageName + "</td>"
                                    "<td>" + QString::number(totalNet) + "</td>"
                                                  "<td>" + QString::number(recordCount) + "</td>"
                                                     "</tr>";
        }

        html += "</table><br><h2>PT Type Records</h2><table>"
                "<tr>"
                "<th>PT Type Name</th>"
                "<th>Total Net</th>"
                "<th>Record Count</th>"
                "</tr>";

        QMapIterator<QString, QPair<int, int>> ptIt(ptNetSums);
        while (ptIt.hasNext()) {
            ptIt.next();
            QString ptTypeName = ptIt.key();
            int totalNet = ptIt.value().first;
            int recordCount = ptIt.value().second;

            html += "<tr>"
                    "<td>" + ptTypeName + "</td>"
                                   "<td>" + QString::number(totalNet) + "</td>"
                                                  "<td>" + QString::number(recordCount) + "</td>"
                                                     "</tr>";
        }

        html += "</table></body></html>";

        result = html;
    } else {
        QString csv = "Package Name,Total Net,Record Count\n";

        QMapIterator<QString, QPair<int, int>> it(packageNetSums);
        while (it.hasNext()) {
            it.next();
            QString packageName = it.key();
            int totalNet = it.value().first;
            int recordCount = it.value().second;

            csv += packageName + ","
                   + QString::number(totalNet) + ","
                   + QString::number(recordCount) + "\n";
        }

        csv += "\nPT Type Name,Total Net,Record Count\n";

        QMapIterator<QString, QPair<int, int>> ptIt(ptNetSums);
        while (ptIt.hasNext()) {
            ptIt.next();
            QString ptTypeName = ptIt.key();
            int totalNet = ptIt.value().first;
            int recordCount = ptIt.value().second;

            csv += ptTypeName + ","
                   + QString::number(totalNet) + ","
                   + QString::number(recordCount) + "\n";
        }

        result = csv;
    }
}





void sheets::r11_save_slot() {
    qDebug() << "Radio Button 11 slot executed for save.";
    qDebug() << "Generating Inbody Report.";

    QDate startDate = ui->start->date();
    QDate endDate = ui->end->date();

    if (startDate > endDate) {
        QMessageBox::critical(this, "Error", "انت مشقلب التواريخ تقريبا");
        return;
    }

    QString queryString =
        "SELECT "
        "    c.id AS customer_id, "
        "    c.name AS customer_name, "
        "    p.start_date AS pack_start, "
        "    p.end_date AS pack_end, "
        "    c.mob_1, "
        "    ib.time AS inbody_time "
        "FROM "
        "    inbody ib "
        "INNER JOIN "
        "    paackage p ON ib.pack_id = p.id "
        "INNER JOIN "
        "    customer c ON p.customer_id = c.id "
        "WHERE "
        "    ib.time BETWEEN :start_date AND :end_date "
        "ORDER BY "
        "    ib.time;";

    QSqlQuery query;
    query.prepare(queryString);
    query.bindValue(":start_date", startDate);
    query.bindValue(":end_date", endDate);

    if (!query.exec()) {
        QMessageBox::critical(this, "SQL Error", query.lastError().text());
        return;
    }

    if (isPDF) {
        QString html = "<html><head><style>"
                       "table {"
                       "  width: 100%;"
                       "  border-collapse: collapse;"
                       "}"
                       "th, td {"
                       "  border: 1px solid black;"
                       "  padding: 8px;"
                       "  text-align: left;"
                       "}"
                       "th {"
                       "  background-color: #f2f2f2;"
                       "}"
                       "</style></head><body>"
                       "<h1>Inbody Records from " + startDate.toString("yyyy-MM-dd") + " to " + endDate.toString("yyyy-MM-dd") + "</h1>"
                                                                                                      "<br>"
                                                                                                      "<table>"
                                                                                                      "<tr>"
                                                                                                      "<th>Customer ID</th>"
                                                                                                      "<th>Customer Name</th>"
                                                                                                      "<th>Mobile</th>"
                                                                                                      "<th>Package Start Date</th>"
                                                                                                      "<th>Package End Date</th>"
                                                                                                      "<th>Inbody Time</th>"
                                                                                                      "</tr>";

        int totalCount = 0;
        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            QDateTime inbodyTime = query.value("inbody_time").toDateTime();

            totalCount++;

            html += "<tr>"
                    "<td>" + QString::number(customerId) + "</td>"
                                                    "<td>" + customerName + "</td>"
                                     "<td>" + mob1 + "</td>"
                             "<td>" + packStart.toString("yyyy-MM-dd") + "</td>"
                                                         "<td>" + packEnd.toString("yyyy-MM-dd") + "</td>"
                                                       "<td>" + inbodyTime.toString("yyyy-MM-dd hh:mm:ss") + "</td>"
                                                                   "</tr>";
        }

        html += "</table>"
                "<footer>"
                "<p>Total : <b>" + QString::number(totalCount) + "</b></p>"
                                                "</footer>"
                                                "</body>"
                                                "</html>";

        result = html;
    } else {
        QString csv = "Customer ID,Customer Name,Mobile,Package Start Date,Package End Date,Inbody Time\n";

        while (query.next()) {
            int customerId = query.value("customer_id").toInt();
            QString customerName = query.value("customer_name").toString();
            QString mob1 = query.value("mob_1").toString();
            QDate packStart = query.value("pack_start").toDate();
            QDate packEnd = query.value("pack_end").toDate();
            QDateTime inbodyTime = query.value("inbody_time").toDateTime();

            csv += QString::number(customerId) + ","
                   + customerName + ","
                   + mob1 + ","
                   + packStart.toString("yyyy-MM-dd") + ","
                   + packEnd.toString("yyyy-MM-dd") + ","
                   + inbodyTime.toString("yyyy-MM-dd hh:mm:ss") + "\n";
        }

        result = csv;
    }
}

void sheets::updateFileNameExtension(const QString &selectedFilter) {
    // Ensure dialog is initialized
    if (!dialog) {
        qDebug() << "QFileDialog dialog is null or not initialized.";
        return;
    }
    QString defaultFileName = "dsd";  // Default file name
    QString newExtension = "";
    isPDF=false;

    if (selectedFilter == "CSV Files (*.csv)") {
        newExtension = "csv"; // Do not include the dot here
    } else if (selectedFilter == "PDF Files (*.pdf)") {
        newExtension = "pdf"; // Do not include the dot here
        isPDF=true;
    } else {
        newExtension = "csv"; // Default to CSV
    }

    QString defaultFileNameWithExtension = defaultFileName + "." + newExtension;

    // Set the default suffix for the file dialog
    dialog->setDefaultSuffix(newExtension);

    // Set the selected file with the correct extension
    dialog->selectFile(defaultFileNameWithExtension);

    qDebug() << defaultFileNameWithExtension;
}

void sheets::closeEvent(QCloseEvent *event){
    emit closed();  // Emit the signal when the widget is close
    QWidget::closeEvent(event);  // Call the base class implementation
}


sheets::~sheets()
{
    delete ui;
    delete dialog;
}
