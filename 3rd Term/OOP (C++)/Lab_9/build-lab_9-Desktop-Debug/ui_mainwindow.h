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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "mywidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *generateButton;
    QPushButton *clearButton;
    QLabel *label;
    myWidget *paintingWidget;
    QComboBox *comboBox_figure;
    QComboBox *comboBox_color;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        generateButton = new QPushButton(centralwidget);
        generateButton->setObjectName(QString::fromUtf8("generateButton"));
        generateButton->setGeometry(QRect(10, 10, 83, 29));
        clearButton = new QPushButton(centralwidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));
        clearButton->setGeometry(QRect(700, 10, 83, 29));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(590, 10, 101, 31));
        paintingWidget = new myWidget(centralwidget);
        paintingWidget->setObjectName(QString::fromUtf8("paintingWidget"));
        paintingWidget->setGeometry(QRect(10, 60, 771, 601));
        comboBox_figure = new QComboBox(centralwidget);
        comboBox_figure->addItem(QString());
        comboBox_figure->addItem(QString());
        comboBox_figure->addItem(QString());
        comboBox_figure->setObjectName(QString::fromUtf8("comboBox_figure"));
        comboBox_figure->setGeometry(QRect(100, 10, 101, 28));
        comboBox_color = new QComboBox(centralwidget);
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->addItem(QString());
        comboBox_color->setObjectName(QString::fromUtf8("comboBox_color"));
        comboBox_color->setGeometry(QRect(210, 10, 111, 28));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 25));
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
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        comboBox_figure->setItemText(0, QCoreApplication::translate("MainWindow", "Triangle", nullptr));
        comboBox_figure->setItemText(1, QCoreApplication::translate("MainWindow", "Circle", nullptr));
        comboBox_figure->setItemText(2, QCoreApplication::translate("MainWindow", "Rectangle", nullptr));

        comboBox_color->setItemText(0, QCoreApplication::translate("MainWindow", "Random", nullptr));
        comboBox_color->setItemText(1, QCoreApplication::translate("MainWindow", "Red", nullptr));
        comboBox_color->setItemText(2, QCoreApplication::translate("MainWindow", "Green", nullptr));
        comboBox_color->setItemText(3, QCoreApplication::translate("MainWindow", "Blue", nullptr));
        comboBox_color->setItemText(4, QCoreApplication::translate("MainWindow", "White", nullptr));
        comboBox_color->setItemText(5, QCoreApplication::translate("MainWindow", "Yellow", nullptr));
        comboBox_color->setItemText(6, QCoreApplication::translate("MainWindow", "Magenta", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
