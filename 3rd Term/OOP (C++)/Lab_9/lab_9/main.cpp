#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(800, 700);
    w.setWindowTitle("Figures painter");
    w.show();
    return a.exec();
}
