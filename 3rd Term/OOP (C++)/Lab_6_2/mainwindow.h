#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <cstdlib>
#include <ctime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_lineEdit_returnPressed();

    void on_pushButton_clicked();

    void add_to_textBrowser();

    void on_checkBox_stateChanged();

private:
    Ui::MainWindow *ui;
    bool randomColor = false;
    QColor color = QColor("#ffffff");
};
#endif // MAINWINDOW_H
