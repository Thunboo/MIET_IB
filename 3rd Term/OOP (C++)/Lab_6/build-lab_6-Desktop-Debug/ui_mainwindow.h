/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QLineEdit *lineEdit_filepath;
    QPushButton *Add_from_file_button;
    QPushButton *chooseFileButton;
    QPushButton *Save_Button;
    QPushButton *Alphabetical_sort_Button;
    QPushButton *ID_sort_Button;
    QLabel *label_Sort_by;
    QPushButton *Add_from_search;
    QCheckBox *Search_Mode_Toggle;
    QLineEdit *lineEdit_ID;
    QLabel *label_ID;
    QLabel *label_Model;
    QLineEdit *lineEdit_Model;
    QLabel *label_Type;
    QComboBox *comboBox_Types;
    QLabel *label_Horsepower;
    QLineEdit *lineEdit_Horsepower;
    QLabel *label_Occupied;
    QLabel *label_Type_error;
    QLabel *label_Model_error;
    QLabel *label_Horsepower_error;
    QCheckBox *checkBox;
    QPushButton *horsepower_sort;
    QLabel *label_Horsepower_search;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(877, 683);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(20, 60, 761, 381));
        lineEdit_filepath = new QLineEdit(centralwidget);
        lineEdit_filepath->setObjectName(QString::fromUtf8("lineEdit_filepath"));
        lineEdit_filepath->setGeometry(QRect(71, 20, 571, 24));
        lineEdit_filepath->setReadOnly(true);
        Add_from_file_button = new QPushButton(centralwidget);
        Add_from_file_button->setObjectName(QString::fromUtf8("Add_from_file_button"));
        Add_from_file_button->setGeometry(QRect(21, 20, 41, 24));
        chooseFileButton = new QPushButton(centralwidget);
        chooseFileButton->setObjectName(QString::fromUtf8("chooseFileButton"));
        chooseFileButton->setGeometry(QRect(651, 20, 80, 24));
        Save_Button = new QPushButton(centralwidget);
        Save_Button->setObjectName(QString::fromUtf8("Save_Button"));
        Save_Button->setGeometry(QRect(740, 20, 41, 24));
        Alphabetical_sort_Button = new QPushButton(centralwidget);
        Alphabetical_sort_Button->setObjectName(QString::fromUtf8("Alphabetical_sort_Button"));
        Alphabetical_sort_Button->setGeometry(QRect(60, 460, 51, 24));
        ID_sort_Button = new QPushButton(centralwidget);
        ID_sort_Button->setObjectName(QString::fromUtf8("ID_sort_Button"));
        ID_sort_Button->setGeometry(QRect(20, 460, 31, 24));
        label_Sort_by = new QLabel(centralwidget);
        label_Sort_by->setObjectName(QString::fromUtf8("label_Sort_by"));
        label_Sort_by->setGeometry(QRect(20, 440, 49, 16));
        Add_from_search = new QPushButton(centralwidget);
        Add_from_search->setObjectName(QString::fromUtf8("Add_from_search"));
        Add_from_search->setGeometry(QRect(20, 510, 41, 24));
        Search_Mode_Toggle = new QCheckBox(centralwidget);
        Search_Mode_Toggle->setObjectName(QString::fromUtf8("Search_Mode_Toggle"));
        Search_Mode_Toggle->setGeometry(QRect(70, 510, 81, 21));
        lineEdit_ID = new QLineEdit(centralwidget);
        lineEdit_ID->setObjectName(QString::fromUtf8("lineEdit_ID"));
        lineEdit_ID->setGeometry(QRect(40, 540, 61, 24));
        label_ID = new QLabel(centralwidget);
        label_ID->setObjectName(QString::fromUtf8("label_ID"));
        label_ID->setGeometry(QRect(20, 540, 20, 20));
        label_Model = new QLabel(centralwidget);
        label_Model->setObjectName(QString::fromUtf8("label_Model"));
        label_Model->setGeometry(QRect(110, 540, 51, 21));
        lineEdit_Model = new QLineEdit(centralwidget);
        lineEdit_Model->setObjectName(QString::fromUtf8("lineEdit_Model"));
        lineEdit_Model->setGeometry(QRect(160, 540, 241, 24));
        label_Type = new QLabel(centralwidget);
        label_Type->setObjectName(QString::fromUtf8("label_Type"));
        label_Type->setGeometry(QRect(410, 540, 101, 21));
        comboBox_Types = new QComboBox(centralwidget);
        comboBox_Types->addItem(QString());
        comboBox_Types->addItem(QString());
        comboBox_Types->addItem(QString());
        comboBox_Types->addItem(QString());
        comboBox_Types->addItem(QString());
        comboBox_Types->setObjectName(QString::fromUtf8("comboBox_Types"));
        comboBox_Types->setGeometry(QRect(490, 540, 101, 24));
        label_Horsepower = new QLabel(centralwidget);
        label_Horsepower->setObjectName(QString::fromUtf8("label_Horsepower"));
        label_Horsepower->setGeometry(QRect(610, 540, 31, 21));
        lineEdit_Horsepower = new QLineEdit(centralwidget);
        lineEdit_Horsepower->setObjectName(QString::fromUtf8("lineEdit_Horsepower"));
        lineEdit_Horsepower->setGeometry(QRect(640, 540, 141, 24));
        label_Occupied = new QLabel(centralwidget);
        label_Occupied->setObjectName(QString::fromUtf8("label_Occupied"));
        label_Occupied->setGeometry(QRect(40, 570, 81, 16));
        label_Type_error = new QLabel(centralwidget);
        label_Type_error->setObjectName(QString::fromUtf8("label_Type_error"));
        label_Type_error->setGeometry(QRect(640, 590, 161, 20));
        label_Model_error = new QLabel(centralwidget);
        label_Model_error->setObjectName(QString::fromUtf8("label_Model_error"));
        label_Model_error->setGeometry(QRect(160, 570, 171, 20));
        label_Horsepower_error = new QLabel(centralwidget);
        label_Horsepower_error->setObjectName(QString::fromUtf8("label_Horsepower_error"));
        label_Horsepower_error->setGeometry(QRect(640, 570, 161, 16));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));
        checkBox->setGeometry(QRect(230, 460, 161, 26));
        horsepower_sort = new QPushButton(centralwidget);
        horsepower_sort->setObjectName(QString::fromUtf8("horsepower_sort"));
        horsepower_sort->setGeometry(QRect(120, 460, 91, 21));
        label_Horsepower_search = new QLabel(centralwidget);
        label_Horsepower_search->setObjectName(QString::fromUtf8("label_Horsepower_search"));
        label_Horsepower_search->setGeometry(QRect(640, 520, 151, 20));
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setEnabled(true);
        textBrowser->setGeometry(QRect(410, 451, 371, 61));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 877, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Add_from_file_button->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        chooseFileButton->setText(QCoreApplication::translate("MainWindow", "Choose file", nullptr));
        Save_Button->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        Alphabetical_sort_Button->setText(QCoreApplication::translate("MainWindow", "Model", nullptr));
        ID_sort_Button->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_Sort_by->setText(QCoreApplication::translate("MainWindow", "Sort by:", nullptr));
        Add_from_search->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        Search_Mode_Toggle->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        label_ID->setText(QCoreApplication::translate("MainWindow", "ID", nullptr));
        label_Model->setText(QCoreApplication::translate("MainWindow", "Model", nullptr));
        label_Type->setText(QCoreApplication::translate("MainWindow", "EngineType", nullptr));
        comboBox_Types->setItemText(0, QCoreApplication::translate("MainWindow", "undefined", nullptr));
        comboBox_Types->setItemText(1, QCoreApplication::translate("MainWindow", "petrol", nullptr));
        comboBox_Types->setItemText(2, QCoreApplication::translate("MainWindow", "diesel", nullptr));
        comboBox_Types->setItemText(3, QCoreApplication::translate("MainWindow", "hybrid", nullptr));
        comboBox_Types->setItemText(4, QCoreApplication::translate("MainWindow", "electro", nullptr));

        label_Horsepower->setText(QCoreApplication::translate("MainWindow", "HP", nullptr));
        label_Occupied->setText(QCoreApplication::translate("MainWindow", "ID occupied", nullptr));
        label_Type_error->setText(QCoreApplication::translate("MainWindow", "NOTE: QSpinBox for HP", nullptr));
        label_Model_error->setText(QCoreApplication::translate("MainWindow", "Model can't be blank", nullptr));
        label_Horsepower_error->setText(QCoreApplication::translate("MainWindow", "Wrong input, HP > 0", nullptr));
        checkBox->setText(QCoreApplication::translate("MainWindow", "Descending Order", nullptr));
        horsepower_sort->setText(QCoreApplication::translate("MainWindow", "Horsepower", nullptr));
        label_Horsepower_search->setText(QCoreApplication::translate("MainWindow", "Approxiamtely (+- 10)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
