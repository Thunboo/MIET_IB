#include "CarClass.h"

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtWidgets>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateTableView(void);

    void updateTableView(int id, std::string brand_model, engineType engine, int horsepower);
    void real_time_search();

private slots:

    void on_Add_from_file_button_clicked();

    void on_chooseFileButton_clicked();

    void on_Alphabetical_sort_Button_clicked();

    void on_ID_sort_Button_clicked();

    void on_Save_Button_clicked();

    void on_Search_Mode_Toggle_clicked();

    void on_lineEdit_ID_textChanged(const QString &arg1);

    void on_lineEdit_Model_textChanged(const QString &arg1);

    void on_lineEdit_Horsepower_textChanged(const QString &arg1);

    void on_comboBox_Types_textActivated(const QString &arg1);

    void on_Add_from_search_clicked();

    void on_horsepower_sort_clicked();

    void on_checkBox_stateChanged(int arg1);

    //void on_comboBox_Types_activated(int index);

    //void on_comboBox_Types_currentTextChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    CarsCollection Collection;
    bool DescendingOrder = 0;
};
#endif // MAINWINDOW_H
