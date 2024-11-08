#include "mainwindow.h"
#include "CarClass.h"
#include "customtextbrowser.h"
#include "ui_mainwindow.h"

CSVReader Reader;
CSVWriter Writer;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , model(new QStandardItemModel(this))
{

    ui->setupUi(this);
    ui->tableView->setModel(model);
    model->setHorizontalHeaderLabels({"ID", "Model", "Engine Type", "Horsepower"});

    ui->label_Occupied->setStyleSheet("color: red;");
    ui->label_Occupied->hide();
    ui->lineEdit_ID->setValidator(new QIntValidator(0, 999999, this));

    ui->label_Type_error->setStyleSheet("color: red;");
    ui->label_Type_error->hide();

    ui->label_Model_error->setStyleSheet("color: red;");
    ui->label_Model_error->hide();

    ui->label_Horsepower_error->setStyleSheet("color: red;");
    ui->label_Horsepower_error->hide();
    ui->lineEdit_Horsepower->setValidator(new QIntValidator(0, 999999, this));
    ui->label_Horsepower_search->hide();

    ui->textBrowser->setStyleSheet("background-color: #ffffff;");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTableView(){
    model->removeRows(0, model->rowCount());
    for (const auto &v: Collection.Cars){
        QList<QStandardItem *> RowData;
        RowData.append(new QStandardItem(QString::number(v.id)));
        RowData.append(new QStandardItem(QString::fromStdString(v.brand_model)));
        RowData.append(new QStandardItem(QString::fromStdString(engineTypeToStrMap[v.engine])));
        RowData.append(new QStandardItem(QString::number(v.horsepower)));
        model->appendRow(RowData);
    }
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

}

void MainWindow::updateTableView(int id, std::string brand_model, engineType engine, int horsepower){
    model->removeRows(0, model->rowCount());
    for (const auto &v: Collection.Cars){
        if ((id == v.id || id == -1) &&
           (v.brand_model.find(brand_model) != std::string::npos  || brand_model.empty()) &&
           (engine == v.engine || engine == UNDEFINED) &&
           (horsepower == -1 || (horsepower - 10 < v.horsepower && v.horsepower < horsepower + 10) )){ //horsepower == v.horsepower ||
            QList<QStandardItem *> RowData;
            RowData.append(new QStandardItem(QString::number(v.id)));
            RowData.append(new QStandardItem(QString::fromStdString(v.brand_model)));
            RowData.append(new QStandardItem(QString::fromStdString(engineTypeToStrMap[v.engine])));
            RowData.append(new QStandardItem(QString::number(v.horsepower)));
            model->appendRow(RowData);
        }
    }
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

}

void MainWindow::on_Add_from_file_button_clicked()
{
    if (ui->lineEdit_filepath->text().endsWith(".csv")){
        QString filepath = ui->lineEdit_filepath->text();
        std::string stdFilePath = filepath.toStdString();
        Reader.changePath(stdFilePath);

        if (Collection.add_from_file(Reader)){
            ui->lineEdit_filepath->setText("Added");
            updateTableView();
        }
        else
            ui->lineEdit_filepath->setText("Failure");
    }
    this->add_line("Added data from a file");
}

void MainWindow::on_chooseFileButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(0, "Open File", "", "*.csv");
    ui->lineEdit_filepath->setText(filePath);
}

void MainWindow::on_Save_Button_clicked()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("CSV Files (*.csv)"));
    if (!filePath.isEmpty()) {
        Writer.changePath(filePath.toStdString());
        std::cout << "Writing data to:'" << filePath.toStdString() << "'\n";
        if (Collection.save_to_file(Writer))
        {
            ui->lineEdit_filepath->setText("Saved");
            this->add_line("Saved data to a file");
        }
        else
        {
            ui->lineEdit_filepath->setText("Save failure");
            this->add_line("Failed to save data to a file");
        }
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    DescendingOrder = not DescendingOrder;
    this->add_line("CHANGED SORT ORDER");
}

void MainWindow::on_horsepower_sort_clicked()
{
    Collection.sort_by_HP(DescendingOrder);
    updateTableView();
    this->add_line("SORTED BY HP ORDER");
}


void MainWindow::on_Alphabetical_sort_Button_clicked()
{
    Collection.sort_alphabetically(DescendingOrder);
    updateTableView();
    this->add_line("SORTED IN ALPHABETICAL ORDER");
}


void MainWindow::on_ID_sort_Button_clicked()
{
    Collection.sort_by_ID(DescendingOrder);
    updateTableView();
    this->add_line("SORTED BY ID ORDER");
}


void MainWindow::on_Search_Mode_Toggle_clicked()
{
    if (ui->Search_Mode_Toggle->isChecked()){
        ui->Add_from_search->hide();
        ui->label_Horsepower_search->show();
    }
    else {
        ui->Add_from_search->show();
        ui->label_Horsepower_search->hide();
    }
    this->add_line("TOOGLED ON SEARCH MODE");
}

void MainWindow::real_time_search(){
    int ID;
    if (ui->lineEdit_ID->text().toStdString().empty())
        ID = -1;
    else
        ID = ui->lineEdit_ID->text().toInt();
    std::string name = ui->lineEdit_Model->text().toStdString();
    engineType engine = engineTypeMap[ui->comboBox_Types->currentText().toStdString()];
    int horsepower; // = ui->lineEdit_Horsepower->text().toInt();
    if (ui->lineEdit_Horsepower->text().toStdString().empty())
        horsepower = -1;
    else
        horsepower = ui->lineEdit_Horsepower->text().toInt();

    updateTableView(ID, name, engine, horsepower);
}

void MainWindow::on_lineEdit_ID_textChanged(const QString &arg1)
{
    if (ui->Search_Mode_Toggle->isChecked()){
        real_time_search();
        //ui->lineEdit_filepath->setText(arg1);
    }
}


void MainWindow::on_lineEdit_Model_textChanged(const QString &arg1)
{
    if (ui->Search_Mode_Toggle->isChecked()){
        real_time_search();
        //ui->lineEdit_filepath->setText(arg1);
    }
}


void MainWindow::on_lineEdit_Horsepower_textChanged(const QString &arg1)
{
    if (ui->Search_Mode_Toggle->isChecked()){
        real_time_search();
        ///ui->lineEdit_filepath->setText(arg1);
    }
    /*
    if (ui->lineEdit_Horsepower->text().toInt() < 0){
        ui->label_Horsepower_error->show();
    }
    else {
        ui->label_Horsepower_error->hide();
    }
    */
}



void MainWindow::on_comboBox_Types_textActivated(const QString &arg1)
{
    if (ui->Search_Mode_Toggle->isChecked()){
        real_time_search();
       //ui->lineEdit_filepath->setText(arg1);
    }
}


void MainWindow::on_Add_from_search_clicked()
{
    int ID = ui->lineEdit_ID->text().toInt();
    std::string name = ui->lineEdit_Model->text().toStdString();
    engineType type = engineTypeMap[ui->comboBox_Types->currentText().toStdString()];
    int horsepower = ui->lineEdit_Horsepower->text().toInt();
    if (Collection.check_ID(ID)){
        ui->label_Occupied->show();
        QTimer::singleShot(3000, ui->label_Occupied, &QLabel::hide);
    }
    if (name.empty()){
        ui->label_Model_error->show();
        QTimer::singleShot(3000, ui->label_Model_error, &QLabel::hide);
    }
    if (horsepower <= 0){
        ui->label_Horsepower_error->show();
        QTimer::singleShot(3000, ui->label_Horsepower_error, &QLabel::hide);
    }


    if ((!Collection.check_ID(ID)) && !name.empty() && horsepower > 0){
        Car temp = {ID, name, type, horsepower};
        Collection.add_car(temp);
        ui->lineEdit_ID->setText("");
        ui->lineEdit_Model->setText("");
        ui->comboBox_Types->setCurrentIndex(0);
        ui->lineEdit_Horsepower->setText("");
        updateTableView();
    }

}

std::string MainWindow::pick_color(){
    std::srand(std::time(NULL));
    std::string color = colors[std::rand() % 15];
    while (color == prevColor){
        color = colors[std::rand() % 15];
    }
    prevColor = color;
    return color;
}

QString MainWindow::lineConvertion(QString line){
    std::string textColorPref = "<font color='" + pick_color() + "'>";
    std::string textColorSuff = "</font>";
    std::string text = textColorPref + line.toStdString() + textColorSuff;
    return QString::fromStdString(text);
}

void MainWindow::add_line(QString line){
    ui->textBrowser->append(this->lineConvertion(line));
}
