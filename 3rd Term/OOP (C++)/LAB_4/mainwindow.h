#include "customtextbrowser.h"
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

    QString lineConvertion(QString line);
    std::string pick_color();
    void add_line(QString line);

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    CarsCollection Collection;
    bool DescendingOrder = 0;
    const std::vector<std::string> colors = {
          "#F07857", "#43A5BE", "#53BDA5",
          "#F5C26B", "#253342", "#CBD6E2",
          "#4FB06D", "#F07857", "#EBB8DD",
          "#5C62D6", "#000000", "#BE398D",
          "#D49137", "#CAE7D3", "#BF2C34"};
    std::string prevColor = "";
};
#endif // MAINWINDOW_H
