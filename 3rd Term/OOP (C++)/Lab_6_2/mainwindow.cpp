#include "mainwindow.h"
#include "ui_mainwindow.h"

QTextBrowser& operator<<(QTextBrowser& tb, const QString& text) {
    tb.append(text);
    return tb;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(17, 17, 17));
    setPalette(palette);
    palette.setColor(QPalette::Base, QColor(17, 17, 17));
    ui->textBrowser->setPalette(palette);
    ui->lineEdit->setPalette(palette);
    ui->lineEdit->setStyleSheet("color: white;");
    ui->pushButton->setStyleSheet("background-color: #111111; color: white; border: 1px solid; border-color: white;");
    ui->checkBox->setStyleSheet("background-color: #111111; color: white; border: 1px solid; border-color: white;");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_lineEdit_returnPressed()
{
    this->add_to_textBrowser();
}


void MainWindow::on_pushButton_clicked()
{
    ui->textBrowser->clear();
}


void MainWindow::add_to_textBrowser()
{
    QString text = ui->lineEdit->text();
    if (!text.toStdString().empty()){
        if (this->randomColor)  this->color = QColor(rand()%256, rand()%256, rand()%256);

        ui->textBrowser->setTextColor(this->color);
        *(ui->textBrowser) << text;
        ui->lineEdit->setText("");
    }
}

void MainWindow::on_checkBox_stateChanged()
{
    this->randomColor = !randomColor;
    if (!randomColor) this->color = QColor("#ffffff");
}

