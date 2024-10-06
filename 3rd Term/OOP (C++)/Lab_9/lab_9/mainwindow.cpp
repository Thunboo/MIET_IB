#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPalette palette;
    palette.setColor(QPalette::Window, QColor(17, 17, 17));
    setPalette(palette);
    palette.setColor(QPalette::Base, QColor(17, 17, 17));
    ui->paintingWidget->setPalette(palette);

    ui->comboBox_color->setStyleSheet("background-color: #111111; color: white; border: 1px solid; border-color: white;");
    ui->comboBox_figure->setStyleSheet("background-color: #111111; color: white; border: 1px solid; border-color: white;");
    ui->generateButton->setStyleSheet("background-color: #111111; color: white; border: 1px solid; border-color: white;");
    ui->clearButton->setStyleSheet("background-color: #111111; color: #ff1e0c; border: 1px solid; border-color: #ff1e0c;");

    ui->label->setStyleSheet("color: white;");
    ui->label->setText(QString::number(figures.size()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_generateButton_clicked()
{
    QString color = ui->comboBox_color->currentText();
    if (ui->comboBox_figure->currentText() == "Triangle")
    {
        figures.push_back(std::make_unique<triangle>(color));
    }
    else if (ui->comboBox_figure->currentText() == "Circle")
    {
        figures.push_back(std::make_unique<circle>(color));
    }
    else if (ui->comboBox_figure->currentText() == "Rectangle")
    {
        figures.push_back(std::make_unique<rectangle>(color));
    }
    ui->paintingWidget->update();
    ui->label->setText(QString::number(figures.size()));
}


void MainWindow::on_clearButton_clicked()
{
    figures.clear();
    ui->centralwidget->update();
    ui->label->setText(QString::number(figures.size()));
}

